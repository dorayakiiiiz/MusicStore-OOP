// Music Store Management System for SQL Server (Unicode ODBC)
#include <iostream>
#include <string>
#include <windows.h>
#include <sqlext.h>

using namespace std;

// Global ODBC handles
SQLHENV env = NULL;
SQLHDBC dbc = NULL;
SQLHSTMT stmt = NULL;
SQLRETURN ret;

class db_response {
public:
    static void Connect() {
        // Allocate environment handle
        if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env) != SQL_SUCCESS ||
            SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0) != SQL_SUCCESS ||
            SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc) != SQL_SUCCESS) {
            cout << "ODBC initialization failed.\n";
            exit(1);
        }

        // Connection string for NHAT-ANH\SQLEXPRESS
        SQLWCHAR connStr[] = L"DRIVER={SQL Server};SERVER=localhost\\SQLEXPRESS;DATABASE=cpp_musicstore_db;Trusted_Connection=Yes;";
        SQLWCHAR outStr[1024];
        SQLSMALLINT outStrLen;

        ret = SQLDriverConnectW(dbc, NULL, connStr, SQL_NTS, outStr, 1024, &outStrLen, SQL_DRIVER_COMPLETE);
        if (SQL_SUCCEEDED(ret)) {
            cout << "Connected to SQL Server successfully.\n";
            SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
        } else {
            SQLWCHAR state[1024], message[1024];
            SQLGetDiagRecW(SQL_HANDLE_DBC, dbc, 1, state, NULL, message, 1024, NULL);
            wcout << L"Connection failed. SQL State: " << state << L"\nMessage: " << message << endl;
            exit(1);
        }
    }
};

void ShowAllItems() {
    system("cls");
    wcout << L"All Music Items\n\n";

    SQLWCHAR query[] = L"SELECT m_id, m_category, m_type, m_name, m_artist, m_price, m_quantity FROM musicinfo_tb";
    ret = SQLExecDirectW(stmt, query, SQL_NTS);

    if (SQL_SUCCEEDED(ret)) {
        SQLINTEGER m_id;
        SQLWCHAR category[100], type[100], name[100], artist[100], price[100], quantity[100];

        // Sử dụng kích thước đúng cho buffer wchar_t
        SQLBindCol(stmt, 1, SQL_C_LONG, &m_id, 0, NULL);
        SQLBindCol(stmt, 2, SQL_C_WCHAR, category, sizeof(category), NULL);
        SQLBindCol(stmt, 3, SQL_C_WCHAR, type, sizeof(type), NULL);
        SQLBindCol(stmt, 4, SQL_C_WCHAR, name, sizeof(name), NULL);
        SQLBindCol(stmt, 5, SQL_C_WCHAR, artist, sizeof(artist), NULL);
        SQLBindCol(stmt, 6, SQL_C_WCHAR, price, sizeof(price), NULL);
        SQLBindCol(stmt, 7, SQL_C_WCHAR, quantity, sizeof(quantity), NULL);

        int row = 0;
        SQLRETURN fetchResult;
        while ((fetchResult = SQLFetch(stmt)) == SQL_SUCCESS) {
            row++;
            wcout << L"ID: " << m_id
                  << L"\nCategory: " << category
                  << L"\nType: " << type
                  << L"\nName: " << name
                  << L"\nArtist: " << artist
                  << L"\nPrice: " << price
                  << L"\nQuantity: " << quantity << L"\n\n";
        }

        if (fetchResult != SQL_NO_DATA) {
            SQLWCHAR state[1024], message[1024];
            SQLGetDiagRecW(SQL_HANDLE_STMT, stmt, 1, state, NULL, message, 1024, NULL);
            wcout << L"[ERROR] Fetch failed. SQL State: " << state << L" Message: " << message << endl;
        }
    } else {
        wcout << L"[ERROR] Query execution failed.\n";
    }

    SQLCloseCursor(stmt);
}


void AddNewItem() {
    system("cls");
    wstring category, type, name, artist, price, quantity;

    wcin.ignore();
    wcout << L"Enter Category: "; getline(wcin, category);
    wcout << L"Enter Type: "; getline(wcin, type);
    wcout << L"Enter Name: "; getline(wcin, name);
    wcout << L"Enter Artist: "; getline(wcin, artist);
    wcout << L"Enter Price: "; getline(wcin, price);
    wcout << L"Enter Quantity: "; getline(wcin, quantity);

    SQLWCHAR insertSQL[] = L"INSERT INTO musicinfo_tb (m_category, m_type, m_name, m_artist, m_price, m_quantity) VALUES (?, ?, ?, ?, ?, ?)";
    SQLPrepareW(stmt, insertSQL, SQL_NTS);

    SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLWCHAR*)category.c_str(), 0, NULL);
    SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLWCHAR*)type.c_str(), 0, NULL);
    SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLWCHAR*)name.c_str(), 0, NULL);
    SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLWCHAR*)artist.c_str(), 0, NULL);
    SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLWCHAR*)price.c_str(), 0, NULL);
    SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 100, 0, (SQLWCHAR*)quantity.c_str(), 0, NULL);

    if (SQLExecute(stmt) == SQL_SUCCESS) {
        wcout << L"\nItem added successfully!\n";
    } else {
        wcout << L"\nFailed to add item.\n";
    }

    SQLCloseCursor(stmt);
}

int main() {
    // Connect to database
    db_response::Connect();

    int choice;
    do {
        system("cls");
        cout << "Music Store Management System\n";
        cout << "1. Show All Items\n";
        cout << "2. Add New Item\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: ShowAllItems(); break;
            case 2: AddNewItem(); break;
            case 3: break;
            default: cout << "Invalid choice!\n"; break;
        }

        if (choice != 3) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 3);

    // Cleanup
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);

    return 0;
}
