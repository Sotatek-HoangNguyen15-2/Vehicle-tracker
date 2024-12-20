#ifndef DATABASE_H
#define DATABASE_H
#include <sqlite3.h>
#include <memory>
#include "Student.h"

class UserRepository {
private:
    sqlite3* connection; // Pointer Sqlite database

public:
    UserRepository(const std::string& database);

    ~UserRepository();

    void addUser(int id, const std::string& name);

    void deleteById(int id);

    Student findOneById(int id);

    void readUsers();

    void updateUser(int id, const std::string& newName);
};

#endif