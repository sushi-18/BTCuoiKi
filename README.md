# Bài tập cuối kì
<strong><small>Đề tài: Phát triển hệ thống theo dõi môi trường và điều khiển hướng sáng</strong></small>

<strong><small> 1. Đặt vấn đề</strong></small>
- Trong bối cảnh biến đổi khí hậu và sự gia tăng nhu cầu sử dụng năng lượng tái tạo, việc theo dõi và khai thác hiệu quả các yếu tố môi trường như nhiệt độ, độ ẩm, và cường độ ánh sáng trở nên quan trọng hơn bao giờ hết. Các hệ thống hiện nay thường chỉ đo lường một số chỉ số cơ bản mà không kết hợp được khả năng điều chỉnh thiết bị để tối ưu hóa nguồn sáng, dẫn đến hiệu suất không tối đa.
- Dự án "Hệ thống theo dõi môi trường và điều khiển hướng sáng" được phát triển nhằm giải quyết vấn đề này. Hệ thống cho phép giám sát các thông số môi trường (nhiệt độ, độ ẩm, cường độ ánh sáng) theo thời gian thực, đồng thời sử dụng các giá trị thu thập được để điều khiển servo tự động hướng thiết bị về phía nguồn sáng tối ưu. Ngoài ra, hệ thống tích hợp công nghệ IoT, giúp người dùng giám sát và điều khiển thiết bị từ xa thông qua một giao diện trực quan.
- Mục tiêu chính của dự án:
  + Thu thập dữ liệu môi trường (nhiệt độ, độ ẩm, cường độ ánh sáng) thông qua các cảm biến.
  + Điều chỉnh vị trí servo để hướng thiết bị về phía nguồn sáng tối ưu.
  + Tích hợp công nghệ IoT (MQTT, Node-RED) để giám sát và điều khiển từ xa.
- Dự án không chỉ có ý nghĩa trong việc tối ưu hóa năng lượng mà còn mang lại giá trị ứng dụng thực tiễn cao trong các lĩnh vực như nông nghiệp thông minh, hệ thống năng lượng mặt trời, và quản lý môi trường.

 <strong><small>2. Sơ đồ khối:</strong></small>
  ![Hình_1](https://github.com/sushi-18/BTCuoiKi/blob/main/Images/Sodokhoi.png?raw=true)

<strong><small>3. Một số ảnh chụp về dự án</strong></small>
   ![Hình_2](https://github.com/sushi-18/BTCuoiKi/blob/main/Images/Screenshot%20(422).png?raw=true)
   ![Hình_3](https://github.com/sushi-18/BTCuoiKi/blob/main/Images/Screenshot%20(423).png?raw=true)
   ![Hình_4](https://github.com/sushi-18/BTCuoiKi/blob/main/Images/Screenshot%20(421).png?raw=true)
   ![Hình_5](https://github.com/sushi-18/BTCuoiKi/blob/main/Images/Screenshot%20(420).png?raw=true)

 
 <strong><small>3.Tổng kết</strong></small>
- Dự án "Hệ thống theo dõi môi trường và điều khiển hướng sáng" đã được hoàn thiện thành công, đáp ứng các mục tiêu đề ra.
- Các kết quả nổi bật của dự án bao gồm:

  + Giám sát môi trường chính xác: Hệ thống thu thập và hiển thị dữ liệu nhiệt độ, độ ẩm và cường độ ánh sáng theo thời gian thực, giúp người dùng dễ dàng theo dõi các yếu tố môi trường.
  + Tự động điều chỉnh hướng sáng: Servo được điều khiển dựa trên dữ liệu từ cảm biến ánh sáng, đảm bảo thiết bị luôn hướng về phía nguồn sáng tối ưu.
  + Tích hợp IoT hiệu quả: Sử dụng giao thức MQTT và Node-RED, hệ thống cho phép giám sát và điều khiển từ xa thông qua giao diện người dùng trên điện thoại hoặc máy tính.
- Hạn chế và hướng phát triển:
Trong quá trình thực hiện, nhận thấy một số hạn chế:

  + Độ chính xác của cảm biến ánh sáng có thể bị ảnh hưởng bởi điều kiện thời tiết (mây, bóng râm).
  + Hệ thống hiện chỉ hoạt động trong một môi trường nhỏ và chưa được tối ưu cho quy mô lớn.
Để cải thiện, hệ thống có thể được nâng cấp với các hướng sau:

  + Tăng độ chính xác bằng cách sử dụng cảm biến chất lượng cao hơn và thuật toán lọc dữ liệu.
  + Mở rộng khả năng giám sát đa khu vực thông qua mạng lưới cảm biến.
  + Phát triển giao diện điều khiển đa nền tảng với nhiều tính năng nâng cao hơn.
- Dự án không chỉ mang lại giải pháp tối ưu cho việc quản lý môi trường mà còn giúp nhóm thực hiện tích lũy nhiều kiến thức và kinh nghiệm trong các lĩnh vực IoT, lập trình nhúng và tự động hóa. Đây là tiền đề quan trọng để phát triển các ứng dụng thực tiễn trong tương lai.
