IF NOT EXISTS (SELECT name FROM sys.databases WHERE name = N'music_store')
BEGIN
    CREATE DATABASE music_store;
END
GO

USE music_store;
GO

IF OBJECT_ID('music_info', 'U') IS NULL
BEGIN
    CREATE TABLE music_info (
        ID INT NOT NULL PRIMARY KEY, 
        NameSong VARCHAR(255) NOT NULL,
        Artist VARCHAR(255) NOT NULL,
        Genre VARCHAR(100) NOT NULL,
        Price FLOAT NOT NULL,
        Quantity INT NOT NULL,
        UNIQUE(NameSong, Artist)
    );

    INSERT INTO music_info (ID, NameSong, Artist, Genre, Price, Quantity) VALUES
    (1, 'APT', 'Rose & Brunor Mars', 'KPop', 15.5, 14),
    (2, 'Drama', 'Aespa', 'Kpop', 20, 11),
    (3, 'How you like that', 'Blackpink', 'Kpop', 20, 10),
    (4, 'Xin dung lang im', 'Soobin', 'Vpop', 10, 10),
    (5, 'Neu ngay ay', 'Soobin Hoang Son', 'Vpop', 10, 10),
    (6, 'Chung ta cua hien tai', 'Son Tung MTP', 'Vpop', 10, 15),
    (7, 'Hop on da show', 'LowG & Tlinh', 'Vpop', 15, 20),
    (8, 'Waiting for you', 'Mono', 'Vpop', 20, 20),
    (9, 'Tung quen', 'Wren Evans', 'Vpop', 15, 10),
    (10, 'Mat ket noi', 'Duong Domic', 'Vpop', 10, 10),
    (11, 'Dai lo mat troi', 'Chillies', 'Vpop', 20, 10),
    (12, 'Vung Ky Uc', 'Chillies', 'Vpop', 10, 10),
    (13, 'Dat trai tim len ban', 'Tung', 'Vpop', 20, 20),
    (14, 'Cau Vinh Tuy', 'Wren Evans', 'Vpop', 10, 25),
    (15, 'Truoc khi em ton tai', 'Thang', 'Vpop', 10, 15),
    (16, 'Nang tho', 'Hoang Dung', 'Vpop', 15, 16);
END
GO

IF OBJECT_ID('user_info', 'U') IS NULL
BEGIN
    CREATE TABLE user_info (
        ID INT NOT NULL PRIMARY KEY,
        Username VARCHAR(255) NOT NULL UNIQUE,
        Pass VARCHAR(255) NOT NULL,
        UserRole CHAR(1)
    );

    INSERT INTO user_info (ID, Username, Pass, UserRole) VALUES
    (1, 'NhatAnh', '123', 'A'),
    (2, 'VanSy', '123', 'A'),
    (3, 'TamChinh', '111', 'C'),
    (4, 'HungThinh', '222', 'C');
END
GO

IF OBJECT_ID('orders', 'U') IS NULL
BEGIN
    CREATE TABLE orders (
        ID INT PRIMARY KEY,
        Username VARCHAR(255) NOT NULL,
        TotalPrice FLOAT NOT NULL
    );

    INSERT INTO orders (ID, Username, TotalPrice) VALUES
    (1, 'TamChinh', 91),
    (2, 'HungThinh', 30),
    (3, 'TamChinh', 40),
    (4, 'HungThinh', 45);
END
GO

IF OBJECT_ID('detail_order', 'U') IS NULL
BEGIN
    CREATE TABLE detail_order (
        ID INT FOREIGN KEY REFERENCES orders(ID) ON DELETE CASCADE,
        NameSong VARCHAR(255) NOT NULL,
        Artist VARCHAR(255) NOT NULL,
        Genre VARCHAR(100) NOT NULL,
        Price FLOAT NOT NULL,
        Quantity INT NOT NULL
        PRIMARY KEY (ID, NameSong, Artist)
    );

    INSERT INTO detail_order (ID, NameSong, Artist, Genre, Price, Quantity) VALUES
    (1, 'APT', 'Rose & Brunor Mars', 'KPop', 15.5, 2),
    (1, 'Drama', 'Aespa', 'Kpop', 20, 3),
    (2, 'Xin dung lang im', 'Soobin', 'Vpop', 10, 1),
    (2, 'Neu ngay ay', 'Soobin Hoang Son', 'Vpop', 10, 2),
    (3, 'Chung ta cua hien tai', 'Son Tung MTP', 'Vpop', 10, 3),
    (3, 'Hop on da show', 'LowG & Tlinh', 'Vpop', 15, 1),
    (4, 'Waiting for you', 'Mono', 'Vpop', 20, 2),
    (4, 'Tung quen', 'Wren Evans', 'Vpop', 15, 1);
END
GO

IF OBJECT_ID('vouchers', 'U') IS NULL
BEGIN
    CREATE TABLE vouchers (
        ID INT NOT NULL PRIMARY KEY,
        Vouchername VARCHAR(255) NOT NULL UNIQUE
    );

END
GO




