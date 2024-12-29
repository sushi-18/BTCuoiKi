#include <Arduino.h>
#include <ESP32Servo.h>
#include "secrets/wifi.h"
#include "wifi_connect.h"
#include <WiFiClientSecure.h>
#include "ca_cert.h"
#include "secrets/mqtt.h"
#include <PubSubClient.h>
#include <Ticker.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
// Define pins
#define LDR1_PIN 36
#define LDR2_PIN 34
#define SERVO_PIN 19
#define DHT_PIN 18  // Chân kết nối DHT11

// DHT sensor type
#define DHT_TYPE DHT11
unsigned long lastPublishTime = 0;
const unsigned long publishInterval = 5000;  // 5 seconds
namespace
{
    const char *ssid = WiFiSecrets::ssid;
    const char *password = WiFiSecrets::pass;
    const char *ldr_topic1 = "esp32/ldr";    // MQTT topic for left LDR
    const char *ldr_topic2 = "esp32/ldr2";   // MQTT topic for right LDR
    const char *servo_topic = "esp32/servo"; // MQTT topic for servo slider
    const char *switch_topic = "esp32/switch"; // MQTT topic for manual/auto mode switch
    const char *temperature_topic = "esp32/temperature"; // MQTT topic for temperature
    const char *humidity_topic = "esp32/humidity";       // MQTT topic for humidity
    unsigned int publish_count = 0;
    uint16_t keepAlive = 15;    // MQTT keep-alive time in seconds
    uint16_t socketTimeout = 5; // MQTT timeout in seconds
}

WiFiClientSecure tlsClient;
PubSubClient mqttClient(tlsClient);
Servo myServo;
Ticker mqttLDRTicker;

// DHT sensor object
DHT dht(DHT_PIN, DHT_TYPE);

// Variables for servo control
int currentServoAngle = 90; // Default servo angle
const int stepSize = 2;
const int delayTime = 20;
const int angleLimitLeft = 0;
const int angleLimitRight = 180;

// Mode control
bool isManualMode = true; // Default is automatic mode

// Function to adjust servo to track the light source
void trackLightSource()
{
    if (isManualMode) return; // Skip automatic control if in manual mode

    int leftLight = analogRead(LDR1_PIN);
    int rightLight = analogRead(LDR2_PIN);

    if (leftLight > rightLight && currentServoAngle > angleLimitLeft)
    {
        currentServoAngle -= stepSize;
        myServo.write(currentServoAngle);
        delay(delayTime);
    }
    else if (rightLight > leftLight && currentServoAngle < angleLimitRight)
    {
        currentServoAngle += stepSize;
        myServo.write(currentServoAngle);
        delay(delayTime);
    }

    Serial.print("Automatic Mode - Current Angle: ");
    Serial.print(currentServoAngle);
    Serial.print(" | Left Light: ");
    Serial.print(leftLight);
    Serial.print(" | Right Light: ");
    Serial.println(rightLight);
}

// MQTT callback to handle incoming messages
void mqttCallback(char *topic, byte *payload, unsigned int length)
{
    // Convert payload to String
    String payloadStr = "";
    for (unsigned int i = 0; i < length; i++)
    {
        payloadStr += (char)payload[i];
    }

    String topicStr = String(topic);

    // Handle switch topic
    if (topicStr == switch_topic)
    {
        if (payloadStr.equalsIgnoreCase("on"))
        {
            isManualMode = true;
            Serial.println("Switch ON: Manual mode activated.");
        }
        else if (payloadStr.equalsIgnoreCase("off"))
        {
            isManualMode = false;
            Serial.println("Switch OFF: Automatic mode activated.");
        }
        else
        {
            Serial.println("Invalid Switch Payload");
        }
    }

    // Handle servo topic
    if (topicStr == servo_topic)
    {
        if (isManualMode)
        {
            int servoValue = payloadStr.toInt(); // Convert payload to integer
            myServo.write(servoValue);          // Move servo to specified position
            Serial.print("Manual Servo Position: ");
            Serial.println(servoValue);
        }
        else
        {
            Serial.println("Ignoring Servo Command: Auto Mode is active.");
        }
    }
}

// Publish LDR values to MQTT
void publishLDR()
{
    int ldrValue1 = analogRead(LDR1_PIN);
    int ldrValue2 = analogRead(LDR2_PIN);

    mqttClient.publish(ldr_topic1, String(ldrValue1).c_str(), false);
    mqttClient.publish(ldr_topic2, String(ldrValue2).c_str(), false);

    Serial.print("LDR 1 Value: ");
    Serial.println(ldrValue1);
    Serial.print("LDR 2 Value: ");
    Serial.println(ldrValue2);
}

// Publish Temperature and Humidity to MQTT
void publishTemperatureAndHumidity()
{
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (!isnan(temperature) && !isnan(humidity)) // Check if readings are valid
    {
        mqttClient.publish(temperature_topic, String(temperature).c_str(), false);
        mqttClient.publish(humidity_topic, String(humidity).c_str(), false);

        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C | Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }
    else
    {
        Serial.println("Failed to read from DHT sensor!");
    }
}

// Reconnect to MQTT broker
void mqttReconnect()
{
    while (!mqttClient.connected())
    {
        Serial.println("Attempting MQTT connection...");
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        if (mqttClient.connect(client_id.c_str(), MQTT::username, MQTT::password))
        {
            Serial.println("MQTT connected");

            // Subscribe to topics
            mqttClient.subscribe(switch_topic);
            mqttClient.subscribe(servo_topic);
        }
        else
        {
            Serial.print("MQTT connect failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 1 second");
            delay(1000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    delay(10);

    // Connect to WiFi
    setup_wifi(ssid, password);
    tlsClient.setCACert(ca_cert);

    mqttClient.setCallback(mqttCallback);
    mqttClient.setServer(MQTT::broker, MQTT::port);

    mqttLDRTicker.attach(1, publishLDR); // Publish LDR values every 1 second

    myServo.attach(SERVO_PIN);
    myServo.write(currentServoAngle);

    pinMode(LDR1_PIN, INPUT);
    pinMode(LDR2_PIN, INPUT);

    dht.begin(); // Initialize the DHT sensor

    Serial.println("Setup complete.");
}

void loop()
{
    unsigned long currentMillis = millis();
    if (!mqttClient.connected())
    {
        mqttReconnect();
    }
    mqttClient.loop();
    // Publish Temperature and Humidity data
    if (currentMillis - lastPublishTime >= publishInterval) {
        publishTemperatureAndHumidity();
        lastPublishTime = currentMillis;
    }

    // Run light tracking only in automatic mode
    if (!isManualMode)
    {
        trackLightSource();
    }


}
