## ĐỒ ÁN MÔN HỌC
## MUSIC STORE MANAGEMENT - HỆ THỐNG QUẢN LÍ CỬA HÀNG ÂM NHẠC

### Học phần: Phương pháp lập trình hướng đối tượng
### Lớp: 23CTT3
### GVHD: Trần Duy Quang

## THÀNH VIÊN NHÓM
- **23120197 - Trà Văn Sỹ (Nhóm trưởng)**
- **23120209 - Lê Hoàng Nhật Anh**

## CẤU TRÚC THƯ MỤC DỰ ÁN
```
MusicStore-OOP/
├── release/                # Chứa file thực thi sau khi biên dịch (program.exe)
├── references/             # Tài liệu tham khảo, class diagram
│   ├── ClassDiagram.png
│   └── html/               # Tài liệu tham khảo (Doxygen), Class Diagram
├── source/                 # Toàn bộ mã nguồn của dự án
│   ├── app/                # Lớp ứng dụng chính và cấu hình (StoreApp, ConsoleConfig)
│   ├── commands/           # Các lớp Command (AdminCommands, CustomerCommands, StoreCommands, CommandInvoker)
│   ├── controllers/        # Các lớp Controller (AdminController, CustomerController, IController)
│   ├── database/           # Logic truy cập cơ sở dữ liệu (DatabaseConnector, Repositories, SQLDao, IDataProvider)
│   ├── factories/          # Các lớp Factory (ControllerFactory, DiscountFactory, SearchFactory)
│   ├── models/             # Các lớp Model (User, Music, Order, Cart, Discount, SalesRecord)
│   ├── services/           # Các lớp Service xử lý logic nghiệp vụ (AuthService, MusicService, OrderService, v.v.)
│   ├── strategies/         # Các lớp Strategy (DiscountStrategy, SearchStrategy)
│   ├── ui/                 # Các lớp giao diện người dùng (AdminUI, CustomerUI, ConsoleUI, utils, InputChecker)
│   └── main.cpp            # Điểm vào chính của chương trình
├── Makefile                # Makefile để biên dịch dự án
└── README.md               # Tài liệu mô tả dự án (file này)
```

## CÁC CÔNG VIỆC MÀ TỪNG THÀNH VIÊN ĐÃ THỰC HIỆN
### Trà Văn Sỹ
- Xây dựng các class Model (Music, Order, User, Cart...)

- Xây dựng các class liên quan đến Service xử lí các chức năng cho các đối tượng (MusicService, OrderService,...) và các Controller cho từng role của User (admin/customer)

- Thiết kế các design pattern (Factory Pattern, Strategy Pattern, Command Pattern, Strategy Pattern) cho các đối tượng (Factory Pattern lựa chọn Controller phù hợp với role của user khi đăng nhập vào hệ thống, Strategy Pattern xử lí nhiều loại mã giảm giá khác nhau...). SearchStrategy giúp tìm kiếm bài hát...

- Soạn tài liệu với doxygen

- Thực hiện unit test chương trình

### Lê Hoàng Nhật Anh
- Xây dựng các phương thức đọc/ghi dữ liệu trên database áp dụng MSSQL cho các kiểu dữ liệu khác nhau (Music, Order, User, Voucher...). Thiết kế class Factory cho ReadData và SaveData.

- Thiết kế Repository Pattern truy xuất data cho chương trình

- Thiết kế các phần liên quan đến giao diện (UI) của toàn bộ chương trình (ConsoleUI, AdminUI, CustomerUI,...)

- Xây dựng các class xử lí bắt lỗi nhập liệu (Input Checker)

- Thực hiện unit test chương trình

- Quay video demo

## TỈ LỆ ĐÓNG GÓP
- Trà Văn Sỹ: 100%
- Lê Hoàng Nhật Anh: 100%

## TỈ LỆ ĐIỂM
Chia đều

## MÔ TẢ CỤ THỂ CÁC YÊU CẦU TRONG PHẦN "CÁCH THỨC ĐÁNH GIÁ"

### TEAMWORK
[Báo cáo tiến độ hàng tuần](https://drive.google.com/file/d/1mnFjyH33ut1f5T2QyBRa-PQFx-P5k0ru/view?usp=sharing)

### UI/UX
### CÁC CHỨC NĂNG ĐÃ CÓ TRONG CHƯƠNG TRÌNH BAN ĐẦU
- Thêm, xóa, chỉnh sửa các bài hát trong kho.
- Tìm nhạc theo các tiêu chí như tên, thể loại, ca sĩ...
- Tạo đơn hàng mua/bán các bài hát.
- Hiển thị số bài hát trong kho và các bài hát đã bán hết.  
[Mã nguồn tham khảo](https://www.codewithc.com/music-store-management-system-c-program-with-mysql-database/)

### CÁC CHỨC NĂNG ĐƯỢC CẢI TIẾN THÊM
Chương trình được phân tách ra 2 vai trò riêng biệt với 2 loại đối tượng người dùng riêng so với chương trình gốc chỉ đơn giản là mua/bán trên chung 1 giao diện

#### Tính năng dành cho người dùng (Customer)
- Đăng ký tài khoản mới: Người dùng có thể tạo tài khoản để sử dụng dịch vụ
- Đăng nhập: Truy cập vào hệ thống với tài khoản đã đăng ký
- Xem danh sách nhạc: Duyệt qua toàn bộ kho âm nhạc
- Tìm kiếm nhạc: Tìm kiếm bài hát theo tên, nghệ sĩ hoặc thể loại
- Quản lý giỏ hàng: Xem danh sách các sản phẩm hiện có, thêm, xóa các bài hát trong giỏ hàng
- Thanh toán đơn hàng: Hoàn tất quá trình mua nhạc
- Sử dụng mã giảm giá: Áp dụng các voucher giảm giá vào đơn hàng (cho đơn hàng trên 50$)
- Xem lịch sử mua hàng: Kiểm tra các đơn hàng đã mua trước đó
- Nhận voucher khuyến mãi: Nhận mã giảm giá khi mua hàng với giá trị lớn
- Đăng xuất: Kết thúc phiên làm việc

#### Tính năng dành cho quản trị viên cửa hàng (Admin)
- Xem danh sách nhạc: Duyệt qua toàn bộ kho âm nhạc
- Quản lý kho nhạc: Thêm, xóa, chỉnh sửa thông tin và giá bài hát
- Xem danh sách người dùng: Quản lý thông tin tài khoản khách hàng
- Quản lý tài khoản: Có quyền xóa tài khoản người dùng vi phạm
- Xem lịch sử đơn hàng: Kiểm tra toàn bộ đơn hàng trong hệ thống
- Thống kê doanh thu: Xem báo cáo doanh thu và số lượng bài hát đã bán
- Đăng xuất: Kết thúc phiên làm việc

#### Database: Truy xuất và lưu trữ dữ liệu từ database với SQL Server thay vì đọc file thông thường

### HƯỚNG DẪN BIÊN DỊCH CHƯƠNG TRÌNH

- Bước 1: Cài đặt ODBC Driver for SQL Server 17 (Đây là driver cần thiết để C++ có thể giao tiếp với SQL Server thông qua ODBC)
    + Tải từ trang chính thức của Microsoft: https://learn.microsoft.com/en-us/sql/connect/odbc/download-odbc-driver-for-sql-server
    + Chọn phiên bản tương ứng hệ điều hành của máy bạn (Windows 64-bit) và cài đặt.
- Bước 2: Cài đặt MSYS2 & UnixODBC
    + Mở MSYS2 UCRT64 Terminal và nhập lệnh: ```pacman -S mingw-w64-ucrt-x86_64-unixodbc```
    + Sau đó nhấn ```Y``` để cài đặt

**Yêu cầu:**
```
-  Trình biên dịch g++ version 13 trở lên.

-  Cài đặt ODBC Driver for SQL Server 17 (hoặc phiên bản mới nhất) để có thể kết nối với SQL Server.

- Link download: https://learn.microsoft.com/en-us/sql/connect/odbc/download-odbc-driver-for-sql-server

- Hệ điều hành: Windows
```

Nhập lệnh sau ở terminal (bash) để biên dịch chương trình:  
```bash
g++ source/main.cpp source/app/*.cpp source/controllers/*.cpp source/services/*.cpp source/models/*.cpp source/database/*.cpp source/factories/*.cpp source/strategies/*.cpp source/commands/*.cpp source/ui/*.cpp -I source -std=c++17 -lole32 -lodbc32 -o release/program
```

hoặc
```bash
g++ $(find source -type f -name "*.cpp") -I source -std=c++17 -lole32 -lodbc32 -o release/program
```

Hoặc sử dụng Makefile (trên Windows, có cài đặt MingGW hoặc MSYS2) có sẵn trong thư mục `source`:
- Chạy lệnh: 
```bash
  mingw32-make
```
  - Lệnh này sẽ tự động biên dịch tất cả các file `.cpp` trong thư mục `source` và tạo ra file thực thi `program` trong thư mục `release`.

Nhập lệnh sau để chạy chương trình: 
```bash
./release/program
``` 

### KIẾN TRÚC PHẦN MỀM
Dự án được xây dựng theo mô hình kiến trúc nhiều lớp (Layered Architecture)

#### Domain Layer (Model)
- Bao gồm các lớp Model như User, Music, Order, Cart, Discount, SalesRecord.
- Đây là các đối tượng biểu diễn dữ liệu cốt lõi của hệ thống.

#### Presentation Layer (UI)
- Bao gồm các lớp UI (AdminUI, CustomerUI, ConsoleUI), các Controller (AdminController, CustomerController), và các Command. 
- Lớp này chịu trách nhiệm tương tác với người dùng và hiển thị dữ liệu.

#### Service Layer / Business Logic Layer
- Chứa các classs Service (MusicService, UserService, OrderService, CartService, DiscountService, AuthService) để xử lý logic nghiệp vụ.
- Các lớp này thực hiện các thao tác trên dữ liệu từ Domain Layer và cung cấp các phương thức cho Presentation Layer.

#### Data Access Layer
- Bao gồm IDataProvider, SqlDao, IRepository và các triển khai Repository cụ thể, cùng với DatabaseConnector. Lớp này chịu trách nhiệm giao tiếp với cơ sở dữ liệu.

### NGUYÊN LÍ OOP ĐƯỢC ÁP DỤNG
#### Tính đóng gói (Encapsulation)
- Tất cả các thuộc tính của các class Model như `Music`, `User`, `Order`, `Cart`, `Discount`, `SalesRecord` đều được khai báo private, chỉ cho phép truy cập thông qua các phương thức getter/setter công khai.
- Các thao tác thay đổi dữ liệu (ví dụ: cập nhật giá, số lượng) đều phải thông qua các phương thức setter, đảm bảo kiểm soát truy cập và bảo vệ tính nhất quán của dữ liệu.
- Các class Service (như `MusicService`, `OrderService`, `UserService`, v.v.) cũng đóng gói logic nghiệp vụ, chỉ cung cấp các phương thức công khai để thao tác với dữ liệu, không để lộ chi tiết xử lý bên trong.

#### Tính kế thừa (Inheritance)
- Sử dụng kế thừa để mở rộng chức năng và tái sử dụng mã nguồn:
    - `User` là lớp cơ sở trừu tượng, các lớp `Admin` và `Customer` kế thừa và triển khai phương thức `getRole()`, cho phép xử lý phân quyền linh hoạt.
    - `IController` là interface, các lớp `AdminController` và `CustomerController` kế thừa và triển khai menu riêng cho từng loại người dùng.
    - `ISearch` là interface cho các chiến lược tìm kiếm (`NameSearch`, `ArtistSearch`, `GenreSearch`), cho phép mở rộng thêm tiêu chí tìm kiếm mới dễ dàng.
    - `Command` là interface cho các lệnh trong menu, các lệnh cụ thể như `SignUpCommand`, `LoginCommand`, `ViewMusicListCommand`, v.v. đều kế thừa và triển khai phương thức `execute()`.
    - `IRepository<T>` là interface cho các repository, các lớp như `SqlMusicRepository`, `SqlUserRepository`, v.v. kế thừa và triển khai thao tác với từng loại dữ liệu.

#### Tính đa hình (Polymorphism)
- Được áp dụng xuyên suốt hệ thống thông qua việc sử dụng interface và lớp trừu tượng:
    - Các đối tượng `User` có thể là `Admin` hoặc `Customer` nhưng đều được xử lý thông qua con trỏ hoặc tham chiếu tới lớp cơ sở `User`.
    - Các controller, command, search strategy, discount strategy đều được sử dụng thông qua interface (`IController`, `Command`, `ISearch`, `DiscountStrategy`), cho phép thay thế linh hoạt các đối tượng cụ thể tại runtime mà không cần thay đổi code phía client.
    - Các repository được thao tác thông qua interface `IRepository<T>`, cho phép thay đổi nguồn dữ liệu mà không ảnh hưởng đến các tầng khác.

#### Tính trừu tượng (Abstraction)
- Các interface và lớp trừu tượng như `IController`, `ISearch`, `DiscountStrategy`, `Command`, `IRepository`, `IDataProvider` định nghĩa các "hợp đồng" rõ ràng cho từng nhóm chức năng, che giấu chi tiết triển khai phía sau.
- Các tầng Service, Controller, UI chỉ làm việc với abstraction, không quan tâm đến chi tiết cụ thể của các class phía dưới (ví dụ: Service chỉ biết đến `IRepository`, không quan tâm đó là SQL hay file).
- Các factory (`ControllerFactory`, `SearchFactory`, `DiscountFactory`) trả về abstraction, giúp code dễ mở rộng và bảo trì.


### TUÂN THỦ CÁC NGUYÊN TẮC SOLID

Dự án Music Store được thiết kế và triển khai tuân thủ đầy đủ 5 nguyên tắc SOLID, đảm bảo mã nguồn dễ mở rộng, bảo trì, kiểm thử và phát triển lâu dài.

#### Single Responsibility Principle (SRP)
- **Model (`Music`, `User`, `Order`, `Cart`, `Discount`, `SalesRecord`):** Chỉ quản lý dữ liệu, thuộc tính và các thao tác getter/setter, không chứa logic nghiệp vụ.
- **Service (`MusicService`, `UserService`, `OrderService`, `CartService`, `DiscountService`, `AuthService`, `SalesRecordService`):** Mỗi service chỉ xử lý logic nghiệp vụ liên quan đến một miền chức năng duy nhất (quản lý nhạc, người dùng, đơn hàng, giỏ hàng, voucher, xác thực, thống kê).
- **Controller (`AdminController`, `CustomerController`):** Điều phối luồng xử lý giữa UI và Service, không xử lý logic nghiệp vụ hay hiển thị.
- **UI (`AdminUI`, `CustomerUI`, `ConsoleUI`):** Chỉ chịu trách nhiệm hiển thị dữ liệu, lấy input từ người dùng, không xử lý logic nghiệp vụ.
- **Repository (`SqlMusicRepository`, `SqlUserRepository`, `SqlOrderRepository`, `SqlDiscountRepository`, `SqlSalesRecordRepository`):** Chỉ thực hiện truy xuất, lưu trữ dữ liệu với database, không xử lý nghiệp vụ.
- **Command (`SignUpCommand`, `LoginCommand`, `ExitCommand`, `ViewMusicListCommand`, `AddToCartCommand`, `CheckoutCommand`, ...):** Mỗi command đóng gói một hành động duy nhất trong menu, không kiêm nhiệm nhiều chức năng.
- **Factory (`ControllerFactory`, `SearchFactory`, `DiscountFactory`):** Chỉ chịu trách nhiệm khởi tạo đối tượng phù hợp với tham số đầu vào.
- **Tiện ích (`InputChecker`, `DatabaseConnector`):** Chỉ kiểm tra dữ liệu đầu vào hoặc quản lý kết nối database.

#### Open/Closed Principle (OCP)
- **Các interface/abstract class (`IRepository`, `ISearch`, `DiscountStrategy`, `Command`, `IController`):** Cho phép mở rộng thêm các chức năng mới (repository mới, chiến lược tìm kiếm mới, loại giảm giá mới, command mới, controller mới) mà không cần sửa code cũ.
- **Strategy Pattern:** Thêm chiến lược tìm kiếm mới (NameSearch, ArtistSearch, GenreSearch) hoặc loại giảm giá mới (PercentageDiscountStrategy, FixedDiscountStrategy) chỉ cần kế thừa interface và đăng ký với Factory, không phải sửa code Service hay Discount.
- **Command Pattern:** Thêm chức năng mới cho menu chỉ cần tạo class command mới, không phải sửa code Controller hay Invoker.
- **Factory Pattern:** Khi có loại controller, search, discount mới, chỉ cần mở rộng Factory, không phải sửa code gọi Factory.
- **Repository Pattern:** Thay đổi nguồn dữ liệu (ví dụ từ SQL sang file) chỉ cần tạo repository mới, không phải sửa code Service.
- **UI:** Có thể mở rộng thêm UI mới (AdminUI, CustomerUI, ConsoleUI) mà không ảnh hưởng đến các lớp khác.

#### Liskov Substitution Principle (LSP) 
- **`User`:** `Admin` và `Customer` đều kế thừa `User`, có thể sử dụng thay thế ở mọi nơi yêu cầu User (ví dụ: currentUser trong `AuthService`, các Command, Service).
- **`DiscountStrategy`:** `PercentageDiscountStrategy` và `FixedDiscountStrategy` đều kế thừa `DiscountStrategy`, được sử dụng thay thế trong `Discount`, `DiscountService`, không cần biết cụ thể loại giảm giá.
- **`ISearch`:** `NameSearch`, `ArtistSearch`, `GenreSearch` đều kế thừa `ISearch`, có thể thay thế lẫn nhau trong `MusicService`, `SearchFactory`.
- **`IController`:** `AdminController` và `CustomerController` đều kế thừa `IController`, `ControllerFactory` trả về `IController`, các luồng xử lý không cần biết cụ thể loại controller.
- **`IRepository`:** Các repository cụ thể đều kế thừa `IRepository<T>`, Service chỉ làm việc với `IRepository<T>` mà không quan tâm đến triển khai cụ thể.

#### Interface Segregation Principle (ISP)
- **Các interface nhỏ, chuyên biệt:** `IRepository` chỉ cho CRUD, `ISearch` chỉ cho tìm kiếm, `DiscountStrategy` chỉ cho tính giảm giá, Command chỉ cho execute và getName, `IController` chỉ cho menu.
- **Các Factory (`ControllerFactory`, `SearchFactory`, `DiscountFactory`):** Chỉ trả về interface hoặc abstract class, không ép các client phụ thuộc vào các phương thức không cần thiết.

#### Dependency Inversion Principle (DIP)
- **Service phụ thuộc abstraction:** Các Service (`MusicService`, `UserService`, ...) chỉ phụ thuộc vào `IDataProvider`/`IRepository`, không phụ thuộc vào `SqlDao` hay repository cụ thể.
- **Controller phụ thuộc abstraction:** Controller chỉ làm việc với Service thông qua singleton, không khởi tạo trực tiếp Service cụ thể.
- **Discount phụ thuộc abstraction:** `Discount` chỉ lưu trữ `DiscountStrategy` (abstraction), không phụ thuộc vào loại chiến lược cụ thể.
- **CommandInvoker phụ thuộc abstraction:** Chỉ làm việc với `Command` (interface), không quan tâm đến command cụ thể.
- **Factory trả về abstraction:** `ControllerFactory` trả về `IController`, `SearchFactory` trả về `ISearch`, `DiscountFactory` trả về `DiscountStrategy`.

Nhờ tuân thủ chặt chẽ các nguyên tắc SOLID ở mọi tầng (Model, Service, Controller, UI, Repository, Command, Factory), hệ thống dễ dàng mở rộng, bảo trì, kiểm thử và phát triển thêm các tính năng mới mà không ảnh hưởng đến các thành phần đã ổn định.

### DESIGN PATTERN ĐƯỢC SỬ DỤNG
#### Factory Pattern
Factory Pattern được sử dụng để tách biệt logic khởi tạo đối tượng khỏi phần sử dụng, giúp dễ dàng mở rộng và thay đổi các loại đối tượng mà không ảnh hưởng đến code sử dụng chúng.
- `ControllerFactory`: Được sử dụng trong quá trình đăng nhập để tạo ra controller phù hợp với vai trò người dùng (`Admin` hoặc `Customer`). Khi người dùng đăng nhập thành công, `ControllerFactory` sẽ trả về đối tượng `AdminController` hoặc `CustomerController` tương ứng, sau đó gọi menu phù hợp.
- `SearchFactory`: Được sử dụng trong các chức năng tìm kiếm nhạc (ở `MusicService` và các command liên quan đến tìm kiếm). Khi người dùng chọn tiêu chí tìm kiếm (theo tên, nghệ sĩ, thể loại), `SearchFactory` sẽ tạo ra chiến lược tìm kiếm tương ứng (`NameSearch`, `ArtistSearch`, `GenreSearch`) để thực hiện tìm kiếm.
- `DiscountFactory`: Được sử dụng trong `DiscountService` khi tạo mới voucher giảm giá cho người dùng (sau khi mua hàng lớn hoặc khi admin tạo voucher). Factory này sinh ra chiến lược giảm giá phù hợp (`PercentageDiscountStrategy` hoặc `FixedDiscountStrategy`) dựa trên loại voucher mà người dùng chọn. Ngoài ra, DiscountFactory còn được sử dụng khi load dữ liệu voucher từ database để khởi tạo đúng loại chiến lược giảm giá cho từng voucher.

#### Strategy Pattern
Strategy Pattern cho phép định nghĩa nhiều thuật toán (hoặc cách xử lý) khác nhau và lựa chọn thuật toán phù hợp tại runtime, giúp mở rộng dễ dàng mà không cần sửa đổi code cũ.
- **`ISearch` và các lớp con (`NameSearch`, `ArtistSearch`, `GenreSearch`)**: Được sử dụng trong toàn bộ chức năng tìm kiếm nhạc (MusicService, SearchMusicCommand, các UI liên quan). Khi người dùng chọn tiêu chí tìm kiếm, chương trình sẽ khởi tạo chiến lược tìm kiếm phù hợp và thực hiện tìm kiếm với thuật toán tương ứng.
- **`DiscountStrategy` và các lớp con (`PercentageDiscountStrategy`, `FixedDiscountStrategy`)**: Được sử dụng trong `Discount`, `DiscountService`, `CheckoutCommand`, và các chức năng áp dụng voucher. Mỗi voucher sẽ chứa một chiến lược giảm giá cụ thể, khi áp dụng sẽ gọi đúng thuật toán tính giảm giá (theo phần trăm hoặc số tiền cố định). Khi tạo mới voucher hoặc khi load từ database, chương trình sẽ khởi tạo đúng chiến lược và gán vào đối tượng `Discount`.


#### Command Pattern
Command Pattern giúp đóng gói các hành động trong menu thành các đối tượng riêng biệt, tách biệt phần gọi lệnh khỏi phần thực thi, dễ dàng mở rộng, thêm mới, hoặc quản lý các thao tác undo/redo.
- **`Interface Command` và các lớp kế thừa**: Toàn bộ các chức năng thao tác trên menu đều được đóng gói thành các class command riêng biệt. 
    - Ở menu chính (`StoreApp`): `SignUpCommand`, `LoginCommand`, `ExitCommand`.
    - Ở menu admin (`AdminController`): `ViewMusicListCommand`, `AddNewItemsCommand`, `RemoveItemsCommand`, `UpdatePriceCommand`, `ViewUsersCommand`, `ViewAllPurchaseHistoriesCommand`, `DeleteUserCommand`, `ViewSalesStatisticsCommand`, `AdminLogoutCommand`.
    - Ở menu customer (CustomerController): `ViewPurchaseHistoryCommand`, `ViewMusicCommand`, `SearchMusicCommand`, `AddToCartCommand`, `RemoveFromCartCommand`, `CheckoutCommand`, `CustomerLogoutCommand`.
- **`CommandInvoker`**: Được sử dụng ở tất cả các menu (`StoreApp`, `AdminController`, `CustomerController`) để quản lý danh sách các command, hiển thị menu, nhận lựa chọn từ người dùng và thực thi command tương ứng. Nhờ đó, các controller chỉ cần khai báo các command và chuyển việc điều phối menu cho CommandInvoker, giúp code controller gọn gàng, dễ mở rộng.
- **Các command này sử dụng các service (`MusicService`, `UserService`, `OrderService`, `DiscountService`, `CartService`, `AuthService`) để thực hiện logic nghiệp vụ, đảm bảo tách biệt rõ ràng giữa UI, controller và business logic.**

#### Repository Pattern
Repository Pattern giúp tách biệt logic truy xuất dữ liệu khỏi logic nghiệp vụ, cho phép thay đổi nguồn dữ liệu (database, file, v.v.) mà không ảnh hưởng đến các tầng khác.
- **`IRepository<T>`**: Interface tổng quát định nghĩa các thao tác CRUD (`getAll`, `getById`, `add`, `updateById`, `deleteById`) cho mọi loại dữ liệu.
- **Các lớp triển khai repository cụ thể**:
    - `SqlUserRepository`: Quản lý dữ liệu người dùng.
    - `SqlMusicRepository`: Quản lý dữ liệu bài hát.
    - `SqlOrderRepository`: Quản lý dữ liệu đơn hàng.
    - `SqlDiscountRepository`: Quản lý dữ liệu voucher giảm giá.
    - `SqlSalesRecordRepository`: Quản lý dữ liệu thống kê doanh thu.
- **`IDataProvider` và `SqlDao`**: Đóng vai trò là lớp trung gian (facade) cung cấp các repository cho các service. Tất cả các service (`MusicService`, `UserService`, `OrderService`, `DiscountService`, `SalesRecordService`, `CartService`, `AuthService`) đều chỉ làm việc với abstraction (`IDataProvider`/`IRepository`), không phụ thuộc vào chi tiết nguồn dữ liệu.
- **Các service sử dụng repository pattern ở mọi thao tác lấy, thêm, sửa, xóa dữ liệu từ database, đảm bảo code nghiệp vụ không phụ thuộc vào chi tiết truy xuất dữ liệu.**

#### Singleton Pattern
Singleton Pattern đảm bảo mỗi service hoặc resource quan trọng chỉ có một instance duy nhất trong toàn bộ chương trình, giúp quản lý tài nguyên hiệu quả và tránh xung đột.
- **Các service singleton**:
    - `MusicService`: Quản lý toàn bộ logic liên quan đến kho nhạc.
    - `UserService`: Quản lý người dùng.
    - `OrderService`: Quản lý đơn hàng.
    - `DiscountServic`e: Quản lý voucher giảm giá.
    - `CartService`: Quản lý giỏ hàng.
    - `AuthService`: Quản lý xác thực đăng nhập/đăng ký.
    - `SalesRecordService`: Quản lý thống kê doanh thu.
  Các service này đều sử dụng singleton để đảm bảo chỉ có một đối tượng duy nhất, được truy cập thông qua phương thức getInstance(). Tất cả các command, controller, UI đều sử dụng các service này thông qua singleton.
- **`DatabaseConnector`**: Được thiết kế singleton để đảm bảo chỉ có một kết nối tới database SQL Server xuyên suốt chương trình. Tất cả các repository đều sử dụng `DatabaseConnector::getInstance()` để truy cập kết nối database, đảm bảo quản lý tài nguyên hiệu quả và tránh lỗi kết nối trùng lặp.

### ĐẢM BẢO CHẤT LƯỢNG
**Unit testing:** Chương trình đã được kiểm thử với 110 test cases, đạt tỷ lệ pass 100%. 
- [Chi tiết báo cáo kiểm thử](https://docs.google.com/spreadsheets/d/1h8u22Et0P12cnSNpjwmj6Vc233AFX60R/edit?usp=sharing&ouid=111498391809847142303&rtpof=true&sd=true)  


**Coding convention:** Chương trình tuân thủ theo đúng các quy định về coding convention của C++.
- [Tài liệu Coding Convention](https://docs.google.com/document/d/10KNVaHAwrnSvY9fQ1v7uBX2IVxCTLYYALBpOFh5hXmo/edit?tab=t.0)


### Tài liệu mô tả kiến trúc phần mềm
- [Class Diagram](references/ClassDiagram.png)
    
- [Tài liệu mô tả](references/html/index.html)

### CÁC CHỦ ĐỀ NÂNG CAO
#### 1. Kết nối và truy xuất Database SQL Server trên Cloud với ODBC
Dự án sử dụng kết nối trực tiếp đến SQL Server trên Azure Cloud thông qua ODBC API, mang lại khả năng truy cập dữ liệu mạnh mẽ và linh hoạt hơn so với việc đọc/ghi file text đơn thuần.

*   **Quản lý kết nối tập trung với Singleton Pattern:**
    *   Lớp [`DatabaseConnector`](source/database/DatabaseConnector.h) (`source/database/DatabaseConnector.cpp`) được thiết kế theo Singleton Pattern, đảm bảo chỉ có một đối tượng quản lý kết nối duy nhất trong toàn bộ ứng dụng.
    *   Phương thức `DatabaseConnector::getInstance()` cung cấp điểm truy cập toàn cục đến đối tượng này.
    *   `ensureConnected()` và `testConnection()` giúp kiểm tra và duy trì trạng thái kết nối, tự động cố gắng kết nối lại nếu cần.
    *   Lớp [`ConnectionStatusDisplay`](source/database/ConnectionStatusDisplay.cpp) cung cấp phản hồi trực quan cho người dùng trong quá trình kết nối đến database khi khởi động ứng dụng.

*   **Chuỗi kết nối (Connection String) được cấu hình sẵn:**
    *   Chuỗi kết nối ODBC được định nghĩa trực tiếp trong phương thức `DatabaseConnector::connect()`, trỏ đến instance SQL Server trên Azure (`musicstoredb.database.windows.net`).
    *   Bao gồm các thông tin xác thực (Uid, Pwd) và các tùy chọn quan trọng như `Encrypt=yes` và `TrustServerCertificate=no` để đảm bảo kết nối an toàn.

*   **Quản lý Transaction để đảm bảo tính toàn vẹn dữ liệu:**
    *   Trong các thao tác quan trọng như thêm đơn hàng mới (`SqlOrderRepository::add` trong [`SQLOrderRepository.cpp`](source/database/SQLOrderRepository.cpp)), transaction được sử dụng một cách rõ ràng.
    *   `SQLSetConnectAttr(hDbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, 0);` được gọi để tắt chế độ tự động commit.
    *   Sau khi thực hiện thành công một loạt các thao tác chèn dữ liệu (vào bảng `orders` và `detail_order`), `SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_COMMIT);` được gọi để xác nhận tất cả các thay đổi.
    *   Nếu có lỗi xảy ra trong quá trình (mặc dù logic rollback chi tiết có thể cần xem xét thêm), cơ chế transaction này là nền tảng để đảm bảo dữ liệu không bị rơi vào trạng thái không nhất quán.

*   **Sử dụng Prepared Statements để tăng cường bảo mật và hiệu suất:**
    *   Hầu hết các thao tác truy vấn SQL trong các lớp Repository (ví dụ: `SqlUserRepository::add`, `SqlMusicRepository::add`, `SqlOrderRepository::add`, [`SQLDiscountRepository.cpp`](source/database/SQLDiscountRepository.cpp)) đều sử dụng prepared statements.
    *   Các bước bao gồm:
        1.  `SQLPrepare()`: Chuẩn bị một câu lệnh SQL với các tham số giữ chỗ (ví dụ: `?`).
        2.  `SQLBindParameter()`: Liên kết các biến C++ với các tham số giữ chỗ này, chỉ định kiểu dữ liệu và kích thước.
        3.  `SQLExecute()`: Thực thi câu lệnh đã chuẩn bị.
    *   Cách tiếp cận này giúp ngăn chặn hiệu quả các cuộc tấn công SQL Injection bằng cách tách biệt mã SQL khỏi dữ liệu người dùng. Đồng thời, nó cũng có thể cải thiện hiệu suất cho các truy vấn được thực thi nhiều lần với các giá trị tham số khác nhau.

```cpp
// Ví dụ về việc sử dụng Transaction và Prepared Statement trong SqlOrderRepository::add
// Tắt auto-commit để bắt đầu transaction
SQLSetConnectAttr(hDbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, 0);

// ... (Lấy ID mới cho đơn hàng) ...

// Thêm vào bảng orders (sử dụng prepared statement)
string orderQuery = "INSERT INTO orders (ID, Username, TotalPrice) VALUES (?, ?, ?)";
SQLPrepare(hStmt, (SQLCHAR*)orderQuery.c_str(), SQL_NTS);
SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &newOrderId, 0, nullptr);
// ... (Bind các tham số khác cho Username, TotalPrice) ...
SQLExecute(hStmt);

// ... (Thêm vào bảng detail_order cho từng sản phẩm, cũng sử dụng prepared statement) ...
// ... (SQLPrepare, SQLBindParameter, SQLExecute cho mỗi item) ...

// Commit transaction nếu tất cả thành công
SQLEndTran(SQL_HANDLE_DBC, hDbc, SQL_COMMIT); 
```

### 2. Command Pattern với Command Invoker

Dự án áp dụng **Command Pattern** một cách hiệu quả để quản lý các thao tác người dùng và cấu trúc menu. Pattern này đóng gói mỗi yêu cầu (ví dụ: đăng nhập, xem danh sách nhạc, thêm vào giỏ hàng) thành một đối tượng `Command` riêng biệt. Cách tiếp cận này mang lại nhiều lợi ích thiết thực cho dự án:

*   **Tách biệt rõ ràng giữa các thành phần (Decoupling):**
    *   Logic nghiệp vụ của mỗi chức năng được chứa trong phương thức `execute()` của từng `Command` cụ thể (thường gọi đến các `Service` tương ứng như `AuthService`, `MusicService`).
    *   `CommandInvoker` là lớp chịu trách nhiệm điều phối: nó hiển thị menu cho người dùng và gọi `execute()` trên `Command` được chọn, mà không cần biết chi tiết về cách `Command` đó được thực thi.
    *   Giao diện người dùng (ví dụ: `ConsoleUI` trong `ConsoleUI.cpp`) được tách biệt, chỉ đảm nhận việc hiển thị và nhận input.
    *   Nhờ sự tách biệt này, việc thay đổi logic một chức năng, giao diện người dùng, hoặc cách menu được gọi không ảnh hưởng lớn đến các phần khác của hệ thống.

*   **Tổ chức Code Mạch lạc và Dễ Mở Rộng:**
    *   **Interface `Command` (`source/commands/Command.h`):** Định nghĩa một "hợp đồng" chung cho tất cả các lệnh với phương thức ảo `execute()` (thực thi lệnh) và `getName()` (lấy tên hiển thị trên menu).
    *   **Các lớp `Command` cụ thể:** Được phân chia logic theo vai trò và chức năng, giúp dễ quản lý:
        *   `StoreCommands` (`source/commands/StoreCommands.h`): Các lệnh cho màn hình chính như `LoginCommand`, `SignUpCommand`, `ExitCommand`.
        *   `AdminCommands` (`source/commands/AdminCommands.h`): Các lệnh quản trị như `ViewMusicListCommand`, `AddNewItemsCommand`, `DeleteUserCommand`.
        *   `CustomerCommands` (`source/commands/CustomerCommands.h`): Các lệnh cho khách hàng như `ViewPurchaseHistoryCommand`, `AddToCartCommand`, `CheckoutCommand`.
    *   Việc thêm một chức năng mới vào menu trở nên đơn giản: chỉ cần tạo một lớp `Command` mới kế thừa từ `Command`, triển khai logic trong `execute()` và `getName()`, sau đó đăng ký nó với `CommandInvoker` trong controller tương ứng (ví dụ `AdminController.cpp`, `CustomerController.cpp`).

*   **`CommandInvoker` thông minh (`source/commands/CommandInvoker.h`, `source/commands/CommandInvoker.cpp`):**
    *   Quản lý một danh sách các đối tượng `Command` (thông qua `std::vector<std::shared_ptr<Command>>`).
    *   Tự động tạo menu động: `CommandInvoker` lấy tên của từng `Command` (qua `command->getName()`) để xây dựng các lựa chọn menu. Sau đó, nó sử dụng `ConsoleUI::selectMenu()` để hiển thị menu tương tác, cho phép người dùng điều hướng bằng phím W/S và chọn bằng Enter.
    *   Khi người dùng chọn một mục, `CommandInvoker` sẽ gọi phương thức `execute()` của đối tượng `Command` tương ứng.

*   **Tăng tính linh hoạt và tái sử dụng với Dependency Injection:**
    *   Nhiều `Command` được thiết kế để nhận các đối tượng phụ thuộc cần thiết (ví dụ: `shared_ptr<User>& currentUser` để biết người dùng hiện tại, hoặc `Cart& cart` để thao tác với giỏ hàng) thông qua constructor.
    *   Cách làm này (một dạng Dependency Injection) giúp các `Command` không bị phụ thuộc cứng vào việc tự tạo ra hay tìm kiếm các đối tượng này, làm tăng khả năng tái sử dụng và giúp việc viết unit test cho từng `Command` trở nên dễ dàng hơn.

```cpp
// Ví dụ sử dụng CommandInvoker trong AdminController.cpp
void AdminController::menu(shared_ptr<User>& currentUser) {
    // ...
    CommandInvoker invoker("ADMIN MENU"); // Khởi tạo Invoker với tiêu đề menu

    // Đăng ký các command cụ thể cho menu Admin
    invoker.addCommand(std::make_shared<ViewMusicListCommand>());
    invoker.addCommand(std::make_shared<AddNewItemsCommand>());
    // ... thêm các command khác ...
    invoker.addCommand(std::make_shared<AdminLogoutCommand>(currentUser));
    
    // Hiển thị menu và bắt đầu vòng lặp xử lý lựa chọn của người dùng
    invoker.executeMenu();
}
```

### 3. Xây dựng Giao diện Người dùng Console Nâng cao (TUI)
Dự án không chỉ dừng lại ở việc xuất/nhập liệu cơ bản với `std::cout` và `std::cin`, mà còn triển khai một Giao diện Người dùng dạng Text (Text-based User Interface - TUI) phức tạp và thân thiện hơn bằng cách tương tác trực tiếp với Windows API và tích hợp ASCII art.
*   **Sử dụng Windows API cho Console:**
    *   Các lớp `ConsoleUI` ([`source/ui/ConsoleUI.h`](source/ui/ConsoleUI.h), [`source/ui/ConsoleUI.cpp`](source/ui/ConsoleUI.cpp)) và `ConsoleConfig` ([`source/app/ConsoleConfig.h`](source/app/ConsoleConfig.h), [`source/app/ConsoleConfig.cpp`](source/app/ConsoleConfig.cpp)) đóng gói các lệnh gọi Windows API.
    *   Các hàm như `gotoXY()` để di chuyển con trỏ, `setColor()` để đổi màu chữ/nền, `SetWindowsSize()`, `DisableResizeWindow()`, và `DisableCursor()` được dùng để tùy biến môi trường console.
    *   Việc nhập liệu được xử lý bằng `_getch()` (trong `ConsoleUI::selectMenu`) để bắt phím không cần đệm, cho phép điều hướng menu tương tác bằng phím W/S và chọn bằng Enter.
*   **Tạo Menu Động và Tương tác:**
    *   `ConsoleUI::selectMenu()` tự động hiển thị các tùy chọn menu, làm nổi bật lựa chọn hiện tại và xử lý việc điều hướng.
    *   Các hàm tiện ích trong [`source/ui/utils.cpp`](source/ui/utils.cpp) như `printFrame()` và `printFrameOptions()` vẽ các khung viền và cấu trúc hóa các thành phần UI.
*   **Tích hợp ASCII Art:**
    *   Các hàm như `printHeader()` và `printMenu()` trong [`source/ui/utils.cpp`](source/ui/utils.cpp) tải và hiển thị ASCII art từ các file text (ví dụ: trong thư mục `ascii/`), tạo phong cách trực quan riêng biệt cho các phần khác nhau của ứng dụng (ví dụ: màn hình chào mừng, menu admin).

### 4. Xây dựng Repository Pattern với Template C++
Dự án tận dụng sức mạnh của template trong C++ để xây dựng một **Repository Pattern** linh hoạt và có khả năng tái sử dụng cao, giúp trừu tượng hóa việc truy cập dữ liệu cho nhiều loại thực thể khác nhau.

**Cách thức triển khai trong dự án:**
*   **Interface `IRepository<T>` ([`source/database/IRepository.h`](source/database/IRepository.h)):**
    *   Được định nghĩa là một template class: `template<class T> class IRepository { ... };`.
    *   Khai báo các phương thức ảo thuần túy (pure virtual functions) như `getAll()`, `getById(int id)`, `add(const T& entity)`, `updateById(int id, const T& entity)`, và `deleteById(int id)`.
*   **Các lớp Repository cụ thể kế thừa `IRepository<T>`:**
    *   Ví dụ: `SqlMusicRepository` kế thừa `IRepository<Music>` ([`source/database/SQLMusicRepository.h`](source/database/SQLMusicRepository.h)).
    *   `SqlUserRepository` kế thừa `IRepository<shared_ptr<User>>` ([`source/database/SQLUserRepository.h`](source/database/SQLUserRepository.h)).
    *   `SqlOrderRepository` kế thừa `IRepository<Order>` ([`source/database/SQLOrderRepository.h`](source/database/SQLOrderRepository.h)).
    *   Mỗi lớp này triển khai các phương thức của `IRepository` với logic truy vấn SQL cụ thể cho kiểu dữ liệu tương ứng.
*   **`IDataProvider` ([`source/database/IDataProvider.h`](source/database/IDataProvider.h)) và `SqlDao` ([`source/database/SQLDao.h`](source/database/SQLDao.h)):**
    *   `IDataProvider` định nghĩa các phương thức trả về `shared_ptr` đến các `IRepository<T>` (ví dụ: `virtual shared_ptr<IRepository<Music>> music() = 0;`).
    *   `SqlDao` triển khai `IDataProvider` và tạo ra các instance cụ thể của các `Sql*Repository` (ví dụ: `return make_shared<SqlMusicRepository>();`).
*   **Sử dụng trong Services:**
    *   Các lớp Service (ví dụ: [`MusicService.cpp`](source/services/MusicService.cpp), [`UserService.cpp`](source/services/UserService.cpp)) tương tác với dữ liệu thông qua interface `IRepository<T>` được cung cấp bởi `IDataProvider`, giúp chúng không phụ thuộc vào cách triển khai cụ thể của repository.


### Video demo mô tả:
```bash
https://www.youtube.com/watch?v=ED6AO7MpQig
```
