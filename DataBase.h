#ifndef DATABASE_H
#define DATABASE_H
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "Student.h"

class UserRepository {
private:
    sql::mysql::MySQL_Driver* driver;
    std::unique_ptr<sql::Connection> connection;

public:
    UserRepository(const std::string& host, const std::string& user, const std::string& password, const std::string& database);

    void addUser(int id, const std::string& name);

    void deleteById(int id);

    Student findOneById(int id);

    void readUsers();

    void updateUser(int id, const std::string& newName);
};

#endif