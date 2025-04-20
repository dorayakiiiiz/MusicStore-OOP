-- Tạo database nếu chưa có
IF NOT EXISTS (SELECT name FROM sys.databases WHERE name = N'cpp_musicstore_db')
BEGIN
    CREATE DATABASE cpp_musicstore_db;
END
GO

USE cpp_musicstore_db;
GO

-- Xoá bảng nếu đã tồn tại để tránh lỗi
IF OBJECT_ID('musicinfo_tb', 'U') IS NOT NULL
    DROP TABLE musicinfo_tb;
GO

CREATE TABLE musicinfo_tb (
    m_id INT IDENTITY(1,1) PRIMARY KEY,
    m_category NVARCHAR(100) DEFAULT N'0',
    m_type NVARCHAR(100) DEFAULT N'0',
    m_name NVARCHAR(100) NOT NULL DEFAULT N'0',
    m_artist NVARCHAR(100) NOT NULL DEFAULT N'0',
    m_price NVARCHAR(100) NOT NULL DEFAULT N'0',
    m_quantity NVARCHAR(100) NOT NULL DEFAULT N'0'
);
GO

-- Dữ liệu mẫu
INSERT INTO musicinfo_tb (m_category, m_type, m_name, m_artist, m_price, m_quantity) VALUES
(N'Popular', N'Jazz', N'WU-TANG CLAN – DON’T STOP', N'WU-TANG CLAN', N'10', N'14'),
(N'Old', N'Remix', N'Ak Teri Yaad', N'Bilal Sayeed', N'200', N'0'),
(N'Old', N'Pop', N'O Bondhu Lal Golapi', N'Shahabuddin', N'100', N'2'),
(N'New', N'Chill', N'Chasma Kala', N'Nil Mitin', N'20.22', N'20');
GO
