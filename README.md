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
- Tên đồ án: Music store – Hệ thống quản lý cửa hàng âm nhạc
- Mục tiêu: Xây dựng một phần mềm giả lập hệ thống bán hàng cho một cửa hàng âm nhạc, cho phép người dùng thực hiện các hoạt động như: đăng nhập/đăng ký, chọn role, quản lý tài khoản, mua sản phẩm, thống kê doanh thu, tìm kiếm nhạc phẩm, và quản lý dữ liệu âm nhạc. Hệ thống có giao diện đồ họa trực quan và được xây dựng theo mô hình lập trình hướng đối tượng chuẩn.

### Chương trình
- Ngôn ngữ lập trinh: C++
- Cơ sở dữ liệu: File sql, văn bản(.txt) hoặc nhị phân
- Giao diện: Giao diện đồ họa (console nâng cao hoặc thư viện SFML, SDL, ncurses,…)
- Áp dụng: Nguyên lý OOP + Design Pattern + Mô hình kiến trúc phần mềm

### Các tính năng đã có
- Tạo đơn hàng
- Tìm nhạc
- Hiện thị số bài hát còn lại
- Mua và bám bài hát
- Thêm, xóa, chỉnh sửa các bài hát
- Thoát

### Các chức năng sẽ cải tiến
#### Tính năng cho người dùng (Customer)
- Đăng ký tài khoản mới
- Đăng nhập hệ thống
- Xem danh sách tất cả các bài hát/các sản phẩm âm nhạc
- Tìm kiếm sản phẩm theo tên, thể loại, nghệ sĩ,...
- Tạo đơn hàng và thanh toán
- Áp dụng giảm giá (theo % hoặc số tiền cố định)
- Xem lịch sử mua hàng (hóa đơn)
- Đánh giá sản phẩm (tùy chọn mở rộng)
- Đăng xuất tài khoản

#### Tính năng dành cho quản trị viên (Admin)
- Đăng nhập với mã bảo mật riêng (admin-key)
- Quản lý sản phẩm âm nhạc (thêm, xóa, sửa, cập nhật giá/số lượng)
- Quản lý tài khoản khách hàng (xem thông tin, xóa tài khoản, xem lịch sử mua hàng)
- Thống kê doanh thu theo ngày, tuần, tháng
- Xem thống kê người dùng tích cực nhất (tuỳ chọn nâng cao)
- Gửi khuyến mãi cho từng người dùng (nâng cao)
- Đăng xuất tài khoản