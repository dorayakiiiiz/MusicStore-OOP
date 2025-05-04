## Đồ án môn học: Music Store Management - Hệ thống quản lí cửa hàng âm nhạc

### Lớp: 23CTT3
### GVHD: Trần Duy Quang

## Thành viên nhóm
- 23120197 - Trà Văn Sỹ (Nhóm trưởng)
- 23120209 - Lê Hoàng Nhật Anh

## Các công việc mà từng thành viên đã thực hiện cho đến hiện tại
### Trà Văn Sỹ
- Xây dựng các class Model (Music, Order, User,...)

- Xây dựng các class liên quan đến Service cho các đối tượng (MusicService, OrderService,...) và các Controller cho từng role của User (admin/customer)

- Thiết kế các phần liên quan đến design pattern (Factory Pattern, Strategy Pattern) cho các đối tượng (Factory Pattern lựa chọn Controller phù hợp với role của user khi đăng nhập vào hệ thống, Strategy Pattern xử lí nhiều loại mã giảm giá khác nhau...)

### Lê Hoàng Nhật Anh
- Xây dựng các phương thức đọc/ghi dữ liệu trên database áp dụng MySQL cho các kiểu dữ liệu khác nhau (Music, Order, User, Voucher...)

- Thiết kế các phần liên quan đến UI của toàn bộ chương trình (AdminUI, CustomerUI,...)

## Tỉ lệ đóng góp
- Trà Văn Sỹ: 100%
- Lê Hoàng Nhật Anh: 100%

## Tỉ lệ điểm: Chia đều

## Các mô tả cụ thể cho các yêu cầu trong phần "Cách thức đánh giá"

### Teamwork

### UI/UX
### Các chức năng đã có của chương trình ban đầu:
- Thêm, xóa, chỉnh sửa các bài hát trong kho.
- Tìm nhạc theo các tiêu chí như tên, thể loại, ca sĩ...
- Tạo đơn hàng mua/bán các bài hát.
- Hiển thị số bài hát trong kho và các bài hát đã bán hết.

### Các chức năng mà nhóm đã cải tiến thêm
Nhóm đã phân tách ra 2 vai trò riêng biệt với 2 loại đối tượng người dùng riêng so với chương trình gốc chỉ đơn giản là mua/bán trên chung 1 giao diện

#### Tính năng dành cho người dùng (Customer)
- Đăng ký tài khoản mới: Người dùng có thể tạo tài khoản để sử dụng dịch vụ
- Đăng nhập: Truy cập vào hệ thống với tài khoản đã đăng ký
- Xem danh sách nhạc: Duyệt qua toàn bộ kho âm nhạc
- Tìm kiếm nhạc: Tìm kiếm bài hát theo tên, nghệ sĩ hoặc thể loại
- Quản lý giỏ hàng: Thêm, xóa các bài hát trong giỏ hàng
- Thanh toán đơn hàng: Hoàn tất quá trình mua nhạc
- Sử dụng mã giảm giá: Áp dụng các voucher giảm giá vào đơn hàng
- Xem lịch sử mua hàng: Kiểm tra các đơn hàng đã mua trước đó
- Nhận voucher khuyến mãi: Nhận mã giảm giá khi mua hàng với giá trị lớn
- Đăng xuất: Kết thúc phiên làm việc

#### Tính năng dành cho quản trị viên cửa hàng (Admin)
- Quản lý kho nhạc: Thêm, xóa, chỉnh sửa thông tin và giá bài hát
- Cập nhật số lượng: Điều chỉnh số lượng sản phẩm có sẵn trong kho
- Xem danh sách người dùng: Quản lý thông tin tài khoản khách hàng
- Quản lý tài khoản: Có quyền xóa tài khoản người dùng vi phạm
- Xem lịch sử đơn hàng: Kiểm tra toàn bộ đơn hàng trong hệ thống
- Thống kê doanh thu: Xem báo cáo doanh thu và số lượng bài hát đã bán
- Phân tích mặt hàng: Xác định các bài hát bán chạy nhất và doanh thu cao nhất
- Đăng xuất: Kết thúc phiên quản trị

#### Nâng cao: Áp dụng load/save data từ database với MySQL thay vì từ file text hay file nhị phân thông thường
#### Hướng dẫn cài đặt

### Kiến trúc phần mềm được áp dụng (cho đến thời điểm báo cáo tiến độ)
Dự án được xây dựng theo mô hình kiến trúc MVC (Model-View-Controller) nhằm phân tách rõ ràng các thành phần của ứng dụng:

#### Model: Đại diện cho dữ liệu và logic nghiệp vụ của ứng dụng
- Các class như Music, Order, User, Voucher đại diện cho các đối tượng dữ liệu
- Logic nghiệp vụ được đóng gói trong các class Service như MusicService, OrderService, UserService

#### View: Xử lí giao diện người dùng
- Được tách biệt thành các class UI riêng biệt (AdminUI, CustomerUI)
- Hiển thị thông tin và tương tác với người dùng mà không chứa logic nghiệp vụ
#### Controller: Xử lý các tương tác từ người dùng
- Các class Controller riêng biệt cho từng vai trò (AdminController, CustomerController)
- Điều phối luồng dữ liệu giữa Model và View

### Các Design Pattern được sử dụng (cho đến hiện tại)
#### Factory Pattern
- ControllerFactory: Tạo ra các Controller phù hợp dựa trên vai trò của người dùng (Admin/Customer)
- ReadDataFactory và SaveDataFactory: Tạo ra các đối tượng xử lý đọc/ghi dữ liệu phù hợp với loại dữ liệu
#### Strategy Pattern
- Áp dụng cho việc xử lý các loại mã giảm giá khác nhau (giảm theo phần trăm, giảm theo số tiền cố định)
- Cho phép linh hoạt thêm các chiến lược giảm giá mới mà không ảnh hưởng đến code hiện có

### Nguyên lí OOP được áp dụng
#### Tính đóng gói (Encapsulation)
- Các thuộc tính của class được khai báo private
- Cung cấp các phương thức getter/setter để truy cập và thay đổi dữ liệu
#### Tính kế thừa (Inheritance)
- Các class con kế thừa từ class cha để tái sử dụng code
- Ví dụ: AdminController và CustomerController kế thừa từ IController
#### Tính đa hình (Polymorphism)
- Sử dụng giao diện và lớp trừu tượng để triển khai các hành vi khác nhau
- Ví dụ: Các chiến lược giảm giá khác nhau đều triển khai từ interface DiscountStrategy
#### Tính trừu tượng (Abstraction)
- Sử dụng các lớp trừu tượng và interface để định nghĩa các hành vi
- Giúp code dễ mở rộng và bảo trì

### Tuân thủ các nguyên tắc SOLID
#### Single Responsibility Principle (SRP)
- Mỗi class có một trách nhiệm duy nhất
- Ví dụ: MusicService chỉ xử lý các thao tác liên quan đến Music, DiscountService chỉ xử lý các thao tác liên quan đến Discount, các loại Service khác cũng tương tưk
#### Open/Closed Principle (OCP)
- Code được thiết kế để mở rộng mà không cần sửa đổi
- Ví dụ: Thêm chiến lược giảm giá mới mà không cần sửa đổi class Discount hoặc các lớp hiện có, thêm loại Controller mới không cần sửa đổi ControllerFactory
#### Liskov Substitution Principle (LSP)
- Các lớp con có thể thay thế lớp cha mà không ảnh hưởng đến tính đúng đắn
- Ví dụ: PercentageDiscountStrategy và FixedDiscountStrategy có thể thay thế cho DiscountStrategy
#### Interface Segregation Principle (ISP)
- Sử dụng nhiều interface nhỏ, chuyên biệt thay vì interface lớn, phức tạp
- Ví dụ: Interface ISearch, ISaveData, IReadData phục vụ cho các mục đích cụ thể
#### Dependency Inversion Principle (DIP)
- Các module cấp cao không phụ thuộc vào module cấp thấp, cả hai phụ thuộc vào abstraction
- Ví dụ: sử dụng dependency injection trong các constructor của Controller và Service, lớp Discount phụ thuộc vào interface DiscountStrategy thay vì các lớp cụ thể

###