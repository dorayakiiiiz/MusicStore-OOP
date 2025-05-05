IF NOT EXISTS (SELECT name FROM sys.databases WHERE name = N'music_store')
BEGIN
    CREATE DATABASE music_store;
END
GO

USE music_store;
GO

IF OBJECT_ID('music_info', 'U') IS NULL
    CREATE TABLE music_info (
        NameSong VARCHAR(255) NOT NULL,
        Artist VARCHAR(255) NOT NULL,
        Genre VARCHAR(100) NOT NULL,
        Price FLOAT NOT NULL,
        Quantity INT NOT NULL,
        primary key (NameSong, Artist)
    );
    GO

    INSERT INTO music_info (NameSong, Artist, Genre, Price, Quantity) VALUES
    ('APT', 'Rose & Brunor Mars', 'KPop', 15.5, 14),
    ('Drama', 'Aespa', 'Kpop', 20, 11),
    ('How you like that', 'Blackpink', 'Kpop', 20, 10),
    ('Xin dung lang im', 'Soobin', 'Vpop', 10, 10),
    ('Neu ngay ay', 'Soobin Hoang Son', 'Vpop', 10, 10),
    ('Chung ta cua hien tai', 'Son Tung MTP', 'Vpop', 10, 15),
    ('Hop on da show', 'LowG & Tlinh', 'Vpop', 15, 20),
    ('Waiting for you', 'Mono', 'Vpop', 20, 20),
    ('Tung quen', 'Wren Evans', 'Vpop', 15, 10),
    ('Mat ket noi', 'Duong Domic', 'Vpop', 10, 10),
    ('Dai lo mat troi', 'Chillies', 'Vpop', 20, 10),
    ('Vung Ky Uc', 'Chillies', 'Vpop', 10, 10),
    ('Dat trai tim len ban', 'Tung', 'Vpop', 20, 20),
    ('Cau Vinh Tuy', 'Wren Evans', 'Vpop', 10, 25),
    ('Truoc khi em ton tai', 'Thang', 'Vpop', 10, 15),
    ('Nang tho', 'Hoang Dung', 'Vpop', 15, 16);
GO

IF OBJECT_ID('user_info', 'U') IS NULL
    CREATE TABLE user_info (
        Username VARCHAR(255) NOT NULL,
        Pass VARCHAR(255) NOT NULL,
        UserRole CHAR(1), 
        primary key (Username)
    );
    GO

    INSERT INTO user_info (Username, Pass, UserRole) VALUES
    ('NhatAnh', '123', 'A'),
    ('VanSy', '123', 'A'),
    ('TamChinh', '111', 'C'),
    ('HungThinh', '222', 'C');
GO

-- Sửa bảng orders để không có IDENTITY
IF OBJECT_ID('orders', 'U') IS NULL
    CREATE TABLE orders (
        OrderCode INT PRIMARY KEY,  -- Không phải tự động tăng
        Username NVARCHAR(255) NOT NULL,
        TotalPrice FLOAT NOT NULL
    );
    GO

    INSERT INTO orders (OrderCode, Username, TotalPrice) VALUES
    (1, 'TamChinh', 91),
    (2, 'HungThinh', 30),
    (3, 'TamChinh', 40),
    (4, 'HungThinh', 45);
GO

IF OBJECT_ID('detail_order', 'U') IS NULL
    CREATE TABLE detail_order (
        OrderCode INT FOREIGN KEY REFERENCES orders(OrderCode) ON DELETE CASCADE,
        NameSong NVARCHAR(255) NOT NULL,
        Artist NVARCHAR(255) NOT NULL,
        Genre NVARCHAR(100) NOT NULL,
        Price FLOAT NOT NULL,
        Quantity INT NOT NULL
   );
   GO
    
    INSERT INTO detail_order (OrderCode, NameSong, Artist, Genre, Price, Quantity) VALUES
    (1, 'APT', 'Rose & Brunor Mars', 'KPop', 15.5, 2),
    (1, 'Drama', 'Aespa', 'Kpop', 20, 3),
    (2, 'Xin dung lang im', 'Soobin', 'Vpop', 10, 1),
    (2, 'Neu ngay ay', 'Soobin Hoang Son', 'Vpop', 10, 2),
    (3, 'Chung ta cua hien tai', 'Son Tung MTP', 'Vpop', 10, 3),
    (3, 'Hop on da show', 'LowG & Tlinh', 'Vpop', 15, 1),
    (4, 'Waiting for you', 'Mono', 'Vpop', 20, 2),
    (4, 'Tung quen', 'Wren Evans', 'Vpop', 15, 1);
GO

IF OBJECT_ID('vouchers', 'U') IS NULL
    CREATE TABLE vouchers (
        Vouchername VARCHAR(255) NOT NULL,
        PRIMARY KEY (Vouchername)
    );
GO


