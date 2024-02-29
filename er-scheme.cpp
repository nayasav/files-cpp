#include <iostream>
#include <sqlite3.h>

sqlite3* create_connection() {
    sqlite3* connection;
    int rc = sqlite3_open("my_database.db", &connection);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(connection) << std::endl;
        return nullptr;
    }
    return connection;
}

void execute_query(sqlite3* connection, const char* query) {
    char* errMsg;
    int rc = sqlite3_exec(connection, query, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Query executed successfully." << std::endl;
    }
}

int main() {
    const char* create_tables_query = R(
        CREATE TABLE IF NOT EXISTS Спiвробiтники(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            iм'я TEXT NOT NULL,
            прiзвище TEXT NOT NULL,
            посада TEXT NOT NULL,
            вiддiл INTEGER NOT NULL
        );

        CREATE TABLE IF NOT EXISTS Контракти(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            сумма INTEGER NOT NULL,
            дата заключення TEXT NOT NULL,
            проєкт INTEGER NOT NULL
        );

        CREATE TABLE IF NOT EXISTS Вiддiли(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            назва TEXT NOT NULL
        );

        CREATE TABLE IF NOT EXISTS Клієнти(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            контактнi данi TEXT NOT NULL,
            iм'я TEXT NOT NULL,
            контракт INTEGER NOT NULL
        );

        CREATE TABLE IF NOT EXISTS Задачi(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            опис TEXT NOT NULL,
            проєкт INTEGER NOT NULL,
            cпiвробiтник INTEGER NOT NULL
        );

        CREATE TABLE IF NOT EXISTS Проєкт(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            назва TEXT NOT NULL,
            дата початку TEXT NOT NULL,
            дата завершення TEXT NOT NULL
        );
    );

    const char* insert_data_query = R(
        INSERT INTO Спiвробiтники (iм'я, прiзвище, посада, вiддiл) VALUES
            ('Анна', 'Колько', 'Розробник', 1),
            ('Борис', 'Ватаманюк', 'Mенеджер', 2);

        INSERT INTO Контракти (сумма, дата заключення, проєкт) VALUES
            (15000, '2024-02-29', 1),
            (8000, '2024-02-28', 2);

        INSERT INTO Вiддiли (назва) VALUES
            ('IT вiддiл'),
            ('Вiддiл продажу');

        INSERT INTO Клієнти (контактнi данi, iм'я, контракт) VALUES
            ('client1@email.com', 'Клієнт 1', 1),
            ('client2@email.com', 'Клієнт 2', 2);

        INSERT INTO Задачi (опис, проєкт, cпiвробiтник) VALUES
            ('Подзвонити клієнту', 1, 1),
            ('Виставлення рахунків', 2, 2);

        INSERT INTO Проєкт (назва, дата початку, дата завершення) VALUES
            ('Проєкт A', '2024-01-01', '2024-03-01'),
            ('Проєкт B', '2024-02-01', '2024-04-01');
    );

    sqlite3* connection = create_connection();
    if (connection) {
        execute_query(connection, create_tables_query);
        execute_query(connection, insert_data_query);

        // Close connection
        sqlite3_close(connection);
    }

    return 0;
}
