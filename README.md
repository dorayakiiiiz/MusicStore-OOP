# Project Proposal
## Thông tin nhóm

### Môn học: Phương pháp lập trình hướng đối tượng

### Giảng viên hướng dẫn: Trần Duy Quang

### Lớp: 23CTT3

### Sinh viên thực hiện đồ án
- 23120197 - Trà Văn Sỹ
- 23120209 - Lê Hoàng Nhật Anh


## Đồ án
### Giới thiệu chung
- Tên đồ án: Music Store – Hệ thống quản lý cửa hàng âm nhạc
- Mục tiêu: xây dựng một phần mềm giả lập hệ thống bán hàng cho một cửa hàng âm nhạc trực tuyến dành cho khách hàng và quản trị viên cửa hàng.

### Chương trình
- Ngôn ngữ lập trình: C++
- Cơ sở dữ liệu: Văn bản (.txt), SQLServer (nâng cao).
- Giao diện: Giao diện console (hoặc giao diện đồ họa nâng cao với các thư viện như SFML, SDL, ncurses,…)
- Áp dụng: Nguyên lý OOP + Design Pattern + Mô hình kiến trúc phần mềm MVC

### Mã nguồn tham khảo: 
https://www.codewithc.com/music-store-management-system-c-program-with-mysql-database/

### Các tính năng đã có
- Tạo đơn hàng.
- Tìm nhạc.
- Hiện thị số bài hát trong kho.
- Mua/bán các bài hát.
- Thêm, xóa, chỉnh sửa các bài hát.
- Thoát chương trình.

### Các chức năng cải tiến thêm.
#### Tính năng cho người dùng (Customer)
- Đăng ký tài khoản mới.
- Đăng nhập hệ thống dịch vụ mua bán của cửa hàng.
- Xem danh sách tất cả các bài hát/các sản phẩm âm nhạc.
- Tìm kiếm sản phẩm theo tên, thể loại, nghệ sĩ,...
- Tạo đơn hàng và thanh toán.
- Áp dụng giảm giá (theo % hoặc số tiền cố định).
- Xem lịch sử mua hàng.
- Đánh giá sản phẩm (tùy chọn mở rộng, sẽ hoàn thành sau)
- Đăng xuất tài khoản.

#### Tính năng dành cho quản trị viên (Admin)
- Đăng ký tài khoản tương tự như customer nhưng kèm theo một mã bảo mật riêng (admin-key).
- Đăng nhập hệ thống quản lí cửa hàng dành cho admin.
- Quản lý sản phẩm âm nhạc (thêm, xóa, sửa, cập nhật giá/số lượng).
- Quản lý tài khoản khách hàng (xem thông tin, xóa tài khoản, xem lịch sử mua hàng).
- Thống kê doanh thu theo ngày, tuần, tháng (đã thống kê doanh thu chung, sẽ hoàn thành thống kê theo các tiêu chí sau).
- Xem thống kê người dùng tích cực nhất (tuỳ chọn nâng cao, sẽ hoàn thành sau).
- Đăng xuất tài khoản.