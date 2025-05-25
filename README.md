## ĐỒ ÁN MÔN HỌC
## MUSIC STORE MANAGEMENT - HỆ THỐNG QUẢN LÍ CỬA HÀNG ÂM NHẠC

### Học phần: Phương pháp lập trình hướng đối tượng
### Lớp: 23CTT3
### GVHD: Trần Duy Quang

## THÀNH VIÊN NHÓM
- 23120197 - Trà Văn Sỹ (Nhóm trưởng)
- 23120209 - Lê Hoàng Nhật Anh

## CÁC CÔNG VIỆC MÀ TỪNG THÀNH VIÊN ĐÃ THỰC HIỆN
### Trà Văn Sỹ
- Xây dựng các class Model (Music, Order, User,...)

- Xây dựng các class liên quan đến Service cho các đối tượng (MusicService, OrderService,...) và các Controller cho từng role của User (admin/customer)

- Thiết kế các phần liên quan đến design pattern (Factory Pattern, Strategy Pattern) cho các đối tượng (Factory Pattern lựa chọn Controller phù hợp với role của user khi đăng nhập vào hệ thống, Strategy Pattern xử lí nhiều loại mã giảm giá khác nhau...)

- Soạn tài liệu với doxygen

### Lê Hoàng Nhật Anh
- Xây dựng các phương thức đọc/ghi dữ liệu trên database áp dụng MSSQL cho các kiểu dữ liệu khác nhau (Music, Order, User, Voucher...). Thiết kế class Factory cho ReadData và SaveData.

- Thiết kế các phần liên quan đến UI của toàn bộ chương trình (AdminUI, CustomerUI,...)

- Xây dựng các class xử lí bắt lỗi nhập liệu (InputValidator)

- Quay video demo

## TỈ LỆ ĐÓNG GÓP
- Trà Văn Sỹ: 100%
- Lê Hoàng Nhật Anh: 100%

## TỈ LỆ ĐIỂM
Chia đều

## MÔ TẢ CỤ THỂ CÁC YÊU CẦU TRONG PHẦN "CÁCH THỨC ĐÁNH GIÁ"

### TEAMWORK
[Báo cáo tiến độ hàng tuần](https://drive.google.com/file/d/1j_GBYkdf_Ny6QiK6zzkkofdpHIZHNRND/view?usp=sharing)

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
- Quản lý giỏ hàng: Thêm, xóa các bài hát trong giỏ hàng
- Thanh toán đơn hàng: Hoàn tất quá trình mua nhạc
- Sử dụng mã giảm giá: Áp dụng các voucher giảm giá vào đơn hàng
- Xem lịch sử mua hàng: Kiểm tra các đơn hàng đã mua trước đó
- Nhận voucher khuyến mãi: Nhận mã giảm giá khi mua hàng với giá trị lớn
- Đăng xuất: Kết thúc phiên làm việc

#### Tính năng dành cho quản trị viên cửa hàng (Admin)
- Quản lý kho nhạc: Thêm, xóa, chỉnh sửa thông tin và giá bài hát
- Xem danh sách người dùng: Quản lý thông tin tài khoản khách hàng
- Quản lý tài khoản: Có quyền xóa tài khoản người dùng vi phạm
- Xem lịch sử đơn hàng: Kiểm tra toàn bộ đơn hàng trong hệ thống
- Thống kê doanh thu: Xem báo cáo doanh thu và số lượng bài hát đã bán
- Đăng xuất: Kết thúc phiên làm việc

#### Database: Truy xuất và lưu trữ dữ liệu từ database với SQL Server thay vì đọc file thông thường

### HƯỚNG DẪN BIÊN DỊCH CHƯƠNG TRÌNH
- Nhập lệnh sau ở terminal:  ```g++ ...```  để biên dịch chương trình

- Nếu đã điều chỉnh trong .vscode/task.json thì chỉ cần gõ lệnh sau để biên dịch:
    ```g++ *.cpp -lole32 -lodbc32 -o out/program```

- Nhập lệnh: ```./out/program``` để chạy chương trình.

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

#### Single Responsibility Principle (SRP) - Nguyên tắc đơn trách nhiệm
- **Model (Music, User, Order, Cart, Discount, SalesRecord):** Chỉ quản lý dữ liệu, thuộc tính và các thao tác getter/setter, không chứa logic nghiệp vụ.
- **Service (MusicService, UserService, OrderService, CartService, DiscountService, AuthService, SalesRecordService):** Mỗi service chỉ xử lý logic nghiệp vụ liên quan đến một miền chức năng duy nhất (quản lý nhạc, người dùng, đơn hàng, giỏ hàng, voucher, xác thực, thống kê).
- **Controller (AdminController, CustomerController):** Điều phối luồng xử lý giữa UI và Service, không xử lý logic nghiệp vụ hay hiển thị.
- **UI (AdminUI, CustomerUI, ConsoleUI):** Chỉ chịu trách nhiệm hiển thị dữ liệu, lấy input từ người dùng, không xử lý logic nghiệp vụ.
- **Repository (SqlMusicRepository, SqlUserRepository, SqlOrderRepository, SqlDiscountRepository, SqlSalesRecordRepository):** Chỉ thực hiện truy xuất, lưu trữ dữ liệu với database, không xử lý nghiệp vụ.
- **Command (SignUpCommand, LoginCommand, ExitCommand, ViewMusicListCommand, AddToCartCommand, CheckoutCommand, ...):** Mỗi command đóng gói một hành động duy nhất trong menu, không kiêm nhiệm nhiều chức năng.
- **Factory (ControllerFactory, SearchFactory, DiscountFactory):** Chỉ chịu trách nhiệm khởi tạo đối tượng phù hợp với tham số đầu vào.
- **Tiện ích (InputChecker, DatabaseConnector):** Chỉ kiểm tra dữ liệu đầu vào hoặc quản lý kết nối database.

#### Open/Closed Principle (OCP) - Nguyên tắc đóng/mở
- **Các interface/abstract class (IRepository, ISearch, DiscountStrategy, Command, IController):** Cho phép mở rộng thêm các chức năng mới (repository mới, chiến lược tìm kiếm mới, loại giảm giá mới, command mới, controller mới) mà không cần sửa code cũ.
- **Strategy Pattern:** Thêm chiến lược tìm kiếm mới (NameSearch, ArtistSearch, GenreSearch) hoặc loại giảm giá mới (PercentageDiscountStrategy, FixedDiscountStrategy) chỉ cần kế thừa interface và đăng ký với Factory, không phải sửa code Service hay Discount.
- **Command Pattern:** Thêm chức năng mới cho menu chỉ cần tạo class command mới, không phải sửa code Controller hay Invoker.
- **Factory Pattern:** Khi có loại controller, search, discount mới, chỉ cần mở rộng Factory, không phải sửa code gọi Factory.
- **Repository Pattern:** Thay đổi nguồn dữ liệu (ví dụ từ SQL sang file) chỉ cần tạo repository mới, không phải sửa code Service.
- **UI:** Có thể mở rộng thêm UI mới (AdminUI, CustomerUI, ConsoleUI) mà không ảnh hưởng đến các lớp khác.

#### Liskov Substitution Principle (LSP) - Nguyên tắc thay thế Liskov
- **User:** Admin và Customer đều kế thừa User, có thể sử dụng thay thế ở mọi nơi yêu cầu User (ví dụ: currentUser trong AuthService, các Command, Service).
- **DiscountStrategy:** PercentageDiscountStrategy và FixedDiscountStrategy đều kế thừa DiscountStrategy, được sử dụng thay thế trong Discount, DiscountService, không cần biết cụ thể loại giảm giá.
- **ISearch:** NameSearch, ArtistSearch, GenreSearch đều kế thừa ISearch, có thể thay thế lẫn nhau trong MusicService, SearchFactory.
- **IController:** AdminController và CustomerController đều kế thừa IController, ControllerFactory trả về IController, các luồng xử lý không cần biết cụ thể loại controller.
- **IRepository:** Các repository cụ thể đều kế thừa IRepository<T>, Service chỉ làm việc với IRepository<T> mà không quan tâm đến triển khai cụ thể.

#### Interface Segregation Principle (ISP) - Nguyên tắc phân tách giao diện
- **Các interface nhỏ, chuyên biệt:** IRepository chỉ cho CRUD, ISearch chỉ cho tìm kiếm, DiscountStrategy chỉ cho tính giảm giá, Command chỉ cho execute và getName, IController chỉ cho menu.
- **Các Service, Controller, UI chỉ phụ thuộc vào interface cần thiết:** Ví dụ, MusicService chỉ cần IRepository<Music>, không cần biết đến repository của User hay Order.
- **Các Factory (ControllerFactory, SearchFactory, DiscountFactory):** Chỉ trả về interface hoặc abstract class, không ép các client phụ thuộc vào các phương thức không cần thiết.

#### Dependency Inversion Principle (DIP) - Nguyên tắc đảo ngược phụ thuộc
- **Service phụ thuộc abstraction:** Các Service (MusicService, UserService, ...) chỉ phụ thuộc vào IDataProvider/IRepository, không phụ thuộc vào SqlDao hay repository cụ thể.
- **Controller phụ thuộc abstraction:** Controller chỉ làm việc với Service thông qua singleton, không khởi tạo trực tiếp Service cụ thể.
- **Discount phụ thuộc abstraction:** Discount chỉ lưu trữ DiscountStrategy (abstraction), không phụ thuộc vào loại chiến lược cụ thể.
- **CommandInvoker phụ thuộc abstraction:** Chỉ làm việc với Command (interface), không quan tâm đến command cụ thể.
- **Factory trả về abstraction:** ControllerFactory trả về IController, SearchFactory trả về ISearch, DiscountFactory trả về DiscountStrategy.
- **Khởi tạo phụ thuộc qua constructor hoặc singleton:** Các Service, Controller, Factory đều nhận hoặc khởi tạo phụ thuộc thông qua constructor hoặc phương thức getInstance, không khởi tạo cứng các đối tượng phụ thuộc bên trong.

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

### Đảm bảo chất lượng (sẽ hoàn thành ở đợt nộp chính thức)

### Tài liệu mô tả kiến trúc phần mềm + Coding Convention
- Class Diagram (cài đặt Extension Markdown Preview Mermaid Support để hiển thị)
```mermaid
classDiagram
    %% Abstract Classes and Interfaces
    class IUser {
        <<abstract>>
        -id: int
        -username: string
        -password: string
        +IUser(username, password)
        +getRole(): string
        +getUsername(): string
        +getPassword(): string
        +toString(): string
        +~IUser()
    }
    
    class IController {
        <<abstract>>
        +menu(vector~Music~, vector~shared_ptr~IUser~~, vector~Order~, vector~shared_ptr~Discount~~, shared_ptr~IUser~): void
    }
    
    class ISearch {
        <<interface>>
        +search(vector~Music~, string): vector~Music~
    }
    
    class IReadData~T~ {
        <<interface>>
        +readData(): vector~T~
    }
    
    class ISaveData~T~ {
        <<interface>>
        +saveData(vector~T~): void
    }
    
    class DiscountStrategy {
        <<interface>>
        +calculateDiscount(float): float
    }
    
    %% Model Classes
    class Music {
        -id: int
        -name: string
        -artist: string
        -genre: string
        -price: float
        -quantity: int
        +Music(id, name, artist, genre, price, quantity)
        +getId(): int
        +getName(): string
        +getArtist(): string
        +getGenre(): string
        +getPrice(): float
        +getQuantity(): int
        +setName(string): void
        +setArtist(string): void
        +setGenre(string): void
        +setPrice(float): void
        +setQuantity(int): void
    }
    
    class Order {
        -username: string
        -purchasedItems: vector~Music~
        -total: float
        +Order(username, items, total)
        +getUsername(): string
        +getPurchasedItems(): vector~Music~
        +getTotal(): float
    }
    
    class Admin {
        +Admin(username, password)
        +getRole(): string
    }
    
    class Customer {
        +Customer(username, password)
        +getRole(): string
    }
    
    class Cart {
        -items: vector~Music~
        +addItem(Music): void
        +removeItem(int): void
        +getItems(): vector~Music~
        +clear(): void
        +calculateTotal(): float
    }
    
    class Discount {
        -code: string
        -username: string
        -strategy: shared_ptr~DiscountStrategy~
        +Discount(code, username, strategy)
        +apply(float): float
        +getCode(): string
        +getUsername(): string
    }
    
    %% Service Classes
    class MusicService {
        +addMusic(Music): void
        +getMusic(int): Music
        +updateMusic(Music): void
        +deleteMusic(int): void
        +getAllMusic(): vector~Music~
        +searchMusic(string, string): vector~Music~
    }
    
    class OrderService {
        +createOrder(string, vector~Music~, float): void
        +getUserOrders(vector~Order~, string): vector~Order~
        +getAllOrders(): vector~Order~
    }
    
    class UserService {
        +addUser(shared_ptr~IUser~): void
        +getUser(string): shared_ptr~IUser~
        +deleteUser(string): void
        +getAllUsers(): vector~shared_ptr~IUser~~
    }
    
    class DiscountService {
        +addDiscount(shared_ptr~Discount~): void
        +getUserDiscounts(vector~shared_ptr~Discount~~, string): vector~shared_ptr~Discount~~
        +applyDiscount(string, float): float
    }
    
    class CartService {
        -cart: Cart
        +addToCart(Music): void
        +removeFromCart(int): void
        +getCartItems(): vector~Music~
        +clearCart(): void
        +calculateTotal(): float
    }
    
    class Authentication {
        +register(string, string, string): bool
        +login(string, string): shared_ptr~IUser~
    }
    
    %% Controllers
    class AdminController {
        -musicService: MusicService&
        -userService: UserService&
        -orderService: OrderService&
        +AdminController(MusicService&, UserService&, OrderService&)
        +menu(vector~Music~, vector~shared_ptr~IUser~~, vector~Order~, vector~shared_ptr~Discount~~, shared_ptr~IUser~): void
        -handleMusicManagement(vector~Music~): void
        -handleUserManagement(vector~shared_ptr~IUser~~): void
        -handleOrderHistory(vector~Order~): void
        -handleSalesStatistics(vector~Order~): void
    }
    
    class CustomerController {
        -musicService: MusicService&
        -cartService: CartService&
        -orderService: OrderService&
        -discountService: DiscountService&
        +CustomerController(MusicService&, CartService&, OrderService&, DiscountService&)
        +menu(vector~Music~, vector~shared_ptr~IUser~~, vector~Order~, vector~shared_ptr~Discount~~, shared_ptr~IUser~): void
        -handlePurchaseHistory(vector~Order~, Customer*&): void
        -handleMusicList(vector~Music~): void
        -handleSearch(vector~Music~): void
        -handleAddToCart(vector~Music~, Cart&): void
        -handleRemoveFromCart(Cart&, vector~Music~): void
        -handleCheckout(vector~Order~, vector~Music~, Cart&, vector~shared_ptr~Discount~~, Customer*&): void
        -handleLogout(Cart&, shared_ptr~IUser~&): bool
    }
    
    class ControllerFactory {
        -musicService: MusicService&
        -cartService: CartService&
        -orderService: OrderService&
        -discountService: DiscountService&
        -userService: UserService&
        +ControllerFactory(MusicService&, CartService&, OrderService&, DiscountService&, UserService&)
        +createController(string): shared_ptr~IController~
    }
    
    %% UI Classes
    class AdminUI {
        +displayWelcomeMessage(string): void
        +displayMenu(): void
        +displayMusicList(vector~Music~&): void
        +displayUserList(vector~shared_ptr~IUser~~&): void
        +displayPurchasedHistory(Order&, int): void
        +displaySaleStatistics(vector~pair~string,pair~int,float~~~&): void
        +getNewMusicDetails(): Music
    }
    
    class CustomerUI {
        +displayWelcomeMessage(string): void
        +displayMenu(): void
        +displayMusicList(vector~Music~&): void
        +displayCart(vector~Music~&): void
        +displayPurchasedHistory(vector~Order~&, string): void
        +getMusicSearchType(): int
        +getMusicSearchQuery(): string
    }
    
    %% Utility Classes
    class SearchFactory {
        +createSearchStrategy(string): shared_ptr~ISearch~
    }
    
    class NameSearch {
        +search(vector~Music~, string): vector~Music~
    }
    
    class ArtistSearch {
        +search(vector~Music~, string): vector~Music~
    }
    
    class GenreSearch {
        +search(vector~Music~, string): vector~Music~
    }
    
    class ReadDataFactory~T~ {
        +createReader(string): shared_ptr~IReadData~T~~
    }
    
    class SaveDataFactory~T~ {
        +createSaver(string): shared_ptr~ISaveData~T~~
    }
    
    class DatabaseConnector {
        -connection: SQLHDBC
        -environment: SQLHENV
        -connectionString: string
        +connect(): bool
        +disconnect(): void
        +executeQuery(string): bool
        +fetchResults(): vector~vector~string~~
    }
    
    class PercentageDiscountStrategy {
        -percentage: float
        +PercentageDiscountStrategy(float)
        +calculateDiscount(float): float
    }
    
    class FixedDiscountStrategy {
        -amount: float
        +FixedDiscountStrategy(float)
        +calculateDiscount(float): float
    }
    
    class InputValidator {
        +validateInt(string): pair~bool,int~
        +validateFloat(string): pair~bool,float~
        +validateString(string): pair~bool,string~
    }
    
    class StoreApp {
        -items: vector~Music~
        -users: vector~shared_ptr~IUser~~
        -orders: vector~Order~
        -vouchers: vector~shared_ptr~Discount~~
        -auth: Authentication
        -musicService: MusicService
        -userService: UserService
        -orderService: OrderService
        -cartService: CartService
        -discountService: DiscountService
        -controllerFactory: ControllerFactory
        +StoreApp()
        +run(): void
        -handleSignUp(): void
        -handleLogin(shared_ptr~IUser~&): bool
        -loadData(): void
        -saveData(): void
    }
    
    %% Relationships
    IUser <|-- Admin
    IUser <|-- Customer
    IController <|-- AdminController
    IController <|-- CustomerController
    ISearch <|-- NameSearch
    ISearch <|-- ArtistSearch
    ISearch <|-- GenreSearch
    DiscountStrategy <|-- PercentageDiscountStrategy
    DiscountStrategy <|-- FixedDiscountStrategy
    
    AdminController --> AdminUI 
    CustomerController --> CustomerUI 
    
    ControllerFactory --> AdminController
    ControllerFactory --> CustomerController 
    
    SearchFactory --> NameSearch 
    SearchFactory --> ArtistSearch 
    SearchFactory --> GenreSearch 
    
    StoreApp --> ControllerFactory 
    StoreApp --> Authentication 
    StoreApp --> MusicService 
    StoreApp --> UserService 
    StoreApp --> OrderService 
    StoreApp --> CartService 
    StoreApp --> DiscountService 
    
    Discount --> DiscountStrategy 
    
    AdminController --> MusicService 
    AdminController --> UserService 
    AdminController --> OrderService 
    
    CustomerController --> MusicService 
    CustomerController --> CartService 
    CustomerController --> OrderService 
    CustomerController --> DiscountService 
    
    MusicService --> Music 
    OrderService --> Order 
    UserService --> IUser 
    CartService --> Cart 
    DiscountService --> Discount 
```
    
- [Tài liệu mô tả (tạo bằng Doxygen, chứa trong thư mục references)](references/html/index.html)

- [Tài liệu Coding Convention](https://docs.google.com/document/d/10KNVaHAwrnSvY9fQ1v7uBX2IVxCTLYYALBpOFh5hXmo/edit?tab=t.0)


### Video demo mô tả:
https://youtu.be/7A5fEKxOeRI?si=2_lJkSKKqz_AJuZ-

