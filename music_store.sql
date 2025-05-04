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

IF OBJECT_ID('user_info', 'U') IS NULL
    CREATE TABLE user_info (
        Username VARCHAR(255) NOT NULL,
        Pass VARCHAR(255) NOT NULL,
        UserRole CHAR(1), 
        primary key (Username)
    );
GO

IF OBJECT_ID('orders', 'U') IS NULL
    CREATE TABLE orders (
        OrderCode INT PRIMARY KEY,
        Username VARCHAR(255) NOT NULL,
        TotalPrice INT NOT NULL
   );
GO

IF OBJECT_ID('detail_order', 'U') IS NULL
    CREATE TABLE detail_order (
        OrderCode INT NOT NULL,
        NameSong VARCHAR(255) NOT NULL,
        Artist VARCHAR(255) NOT NULL,
        Genre VARCHAR(100) NOT NULL,
        Price FLOAT NOT NULL,
        Quantity INT NOT NULL,
        PRIMARY KEY (OrderCode, NameSong, Artist),
        FOREIGN KEY (OrderCode) REFERENCES orders(OrderCode)
    ); 
GO



IF OBJECT_ID('vouchers', 'U') IS NULL
    CREATE TABLE vouchers (
        Vouchername VARCHAR(255) NOT NULL,
        PRIMARY KEY (Vouchername)
    );
GO
