#include "DataBase.h"

UserRepository::UserRepository(const std::string& database)
{
    if (sqlite3_open(database.c_str(), &connection) != SQLITE_OK) {
        throw std::runtime_error("Cannot open database: " + std::string(sqlite3_errmsg(connection)));
    }

    // SQL to create a table if it does not already exist
    const char* createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL
        );
    )";

    char* errorMessage = nullptr;
    if (sqlite3_exec(connection, createTableSQL, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::string error = "Failed to create table: " + std::string(errorMessage);
        sqlite3_free(errorMessage); // free memmory for error
        throw std::runtime_error(error);
    }
}

UserRepository::~UserRepository()
{
    sqlite3_close(connection);
}

Student UserRepository::findOneById(int id)
{
    const char* sql = "SELECT id, name FROM users WHERE id = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
    }

    sqlite3_bind_int(stmt, 1, id);

    Student student(-1, ""); // Not found
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int userId = sqlite3_column_int(stmt, 0);
        std::string userName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        student = Student(userId, userName);
    }

    sqlite3_finalize(stmt);
    return student;
}

void UserRepository::deleteById(int id)
{
    const char* sql = "DELETE FROM users WHERE id = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
    }

    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void UserRepository::readUsers()
{
    const char* sql = "SELECT id, name FROM users";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::cout << "ID: " << id << ", Name: " << name << std::endl;
    }

    sqlite3_finalize(stmt);
}

void UserRepository::addUser(int id, const std::string& name)
{
    const char* sql = "INSERT INTO users (id, name) VALUES (?, ?)";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
    }

    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw std::runtime_error("Failed to execute statement: " + std::string(sqlite3_errmsg(connection)));
    }

    sqlite3_finalize(stmt);
    std::cout << "User added: ID = " << id << ", Name = " << name << std::endl;
}

void UserRepository::updateUser(int id, const std::string& newName)
{
    const char* sql = "UPDATE users SET name = ? WHERE id = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
    }

    sqlite3_bind_text(stmt, 1, newName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);

    int rowsAffected = sqlite3_step(stmt);
    if (rowsAffected == SQLITE_DONE) {
        std::cout << "Student updated: ID = " << id << ", New Name = " << newName << std::endl;
    } else {
        std::cout << "No user found with ID = " << id << std::endl;
    }

    sqlite3_finalize(stmt);
}
