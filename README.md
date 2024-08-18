# Game 2048
- ![2048logo](https://github.com/user-attachments/assets/bad9bd41-eb55-4998-a7b6-9e28885ee010)

# Giới Thiệu Game
- Dự án được lấy cảm hứng từ 2048 ([play2048.co](https://play2048.co/)) từ hình ảnh đồ hoạ cho tới cơ chế game.
- Game được viết bằng ngôn ngữ C++ và sử dụng thư viện SDL2.

## Cách chơi
**Với game 2048, chơi trên lưới 4x4 và mục tiêu của bạn là kết hợp các ô phù hợp để đạt được ô 2048 khó nắm bắt. Bằng các phím điều hướng đơn giản**

+ Nhấn UP để dồn các ô lên phía trên
+ Nhấn DOWN để dồn các ô xuống phía dưới
+ Nhấn LEFT để dồn các ô sang bên trái
+ Nhấn RIGHT để dồn các ô sang bên phải
+ Nhấn M để bật/tắt nhạc

**Mỗi khi 2 ô cùng giá trị và được sát nhập điểm của người chơi sẽ được công thêm bằng đúng giá trị của ô mới được tạo ra từ việc sát nhập**

## MÔ TẢ CHỨC NĂNG

+ Có nút Newgame để bắt đầu/ chơi lại ván game:
+ Có hệ thống âm thanh sinh động:
+ Lưu điểm cao  mỗi lần chơi
+ Có nút M để tắt bật âm
+ Có bảng thông báo mỗi khi thắng hoặc thua
+ Có bảng Score cập nhập điểm liên tục và Best cập nhập điểm cao kể cả khi tắt chương trình

 ### Với dạng game 2048basic
 - Là phiên bản cơ bản nhất của game
 - ![image](https://github.com/user-attachments/assets/910a05fa-559c-4680-885f-288d99b3479d)

#### Với dạng game 2048x÷ (Update)
- Là phiên bản nâng cấp thêm của tựa game cơ bản 2048
- Có sinh thêm ô X và ô ÷ tương ứng với từng tác vụ của nó
  + Khi nhập với ô X sẽ được x2 giá trị của ô nhập
  + ![image](https://github.com/user-attachments/assets/54472a6e-43d3-4c5c-9f08-769b252ca8a3)

  + Ngược lại với ô ÷ sẽ bị /2 giá trị của ô nhập
  + ![image](https://github.com/user-attachments/assets/dd2ea471-ca16-45ce-a035-4070e3f0113b)

  + Với 2048x÷ có khả năng dễ chiến thắng hơn vì chỉ cần tạo được ô 1024 và x2 là win
  + ![image](https://github.com/user-attachments/assets/a18ca3b1-8c8e-4912-9b98-e03de43e0173)


 # **DỰ KIẾN BỔ SUNG THÊM CÁC CHỨC NĂNG KHÁC**
 + Có thể thêm menu chọn trực tiếp thay đổi chế độ của game
 + Thêm các chức năng đặc biệt trong game nhằm thay đổi yếu tố tiền sử của game, ví dụ tạo bảng 8x8 cho game
 + v.v...
