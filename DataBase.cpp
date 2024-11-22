#include "DataBase.h"

UserRepository :: UserRepository(const std::string& host, const std::string& user, const std::string& password, const std::string& database)
{
    driver = sql::mysql::get_mysql_driver_instance();
    connection.reset(driver->connect(host, user, password));
    connection->setSchema(database);
}

 Student UserRepository :: findOneById(int id)
 {
    std::unique_ptr<sql::PreparedStatement> stmt(
    connection->prepareStatement("SELECT id, name FROM users WHERE id = ?"));
    stmt->setInt(1, id);
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());

    if (res->next()) 
    {
        int userId = res->getInt("id");
        std::string userName = res->getString("name");
        return Student(userId, userName);
    }

    return Student(-1, ""); // Not found
}

void UserRepository :: deleteById(int id) 
{
    std::unique_ptr<sql::PreparedStatement> stmt(connection->prepareStatement("DELETE FROM users WHERE id = ?"));
    stmt->setInt(1, id);
    stmt->execute();
}

void UserRepository :: readUsers()
{
    try 
    {
        // Create query SQL
        std::unique_ptr<sql::Statement> stmt(connection->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT id, name FROM users"));

        // Browse through the query results and show the data
        while (res->next()) 
        {
            int id = res->getInt("id");
            std::string name = res->getString("name");
                
            std::cout << "ID: " << id << ", Name: " << name << std::endl;
        }
    } 
    catch (sql::SQLException& e) 
    {
        std::cerr << "Error reading users: " << e.what() << std::endl;
    }
}

void UserRepository::addUser(int id, const std::string& name) 
{
    try {
        std::unique_ptr<sql::PreparedStatement> stmt(
            connection->prepareStatement("INSERT INTO users (id, name) VALUES (?, ?)")
        );
        stmt->setInt(1, id);
        stmt->setString(2, name);
        stmt->execute();
        std::cout << "Student added: ID = " << id << ", Name = " << name << std::endl;
    } catch (sql::SQLException& e) {
        std::cerr << "Error adding user: " << e.what() << std::endl;
    }
}

void UserRepository::updateUser(int id, const std::string& newName)
{
    try {
        std::unique_ptr<sql::PreparedStatement> stmt(
            connection->prepareStatement("UPDATE users SET name = ? WHERE id = ?")
        );
        stmt->setString(1, newName); // Giá trị mới cho cột 'name'
        stmt->setInt(2, id);         // Điều kiện cập nhật (id)

        int rowsAffected = stmt->executeUpdate();
        if (rowsAffected > 0) {
            std::cout << "Student updated: ID = " << id << ", New Name = " << newName << std::endl;
        } else {
            std::cout << "No user found with ID = " << id << std::endl;
        }
    } catch (sql::SQLException& e) {
        std::cerr << "Error updating user: " << e.what() << std::endl;
    }
}
