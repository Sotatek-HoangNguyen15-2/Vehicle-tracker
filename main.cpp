#include <iostream>
#include <string>
#include "DataBase.h"

int main() {
    try {
        UserRepository repo("tcp://127.0.0.1:3306", "root", "1", "test_db");

        // // Save a new user
        // Student user1(1, "John Doe");
        // repo.save(user1);

        // // Find a user by ID
        // Student user = repo.findOneById(1);
        // if (user.id != -1) {
        //     std::cout << "Found user: " << user.id << ", " << user.name << std::endl;
        // } else {
        //     std::cout << "Student not found." << std::endl;
        // }
        // repo.addUser(2, "Viet Hoang");

        // repo.readUsers();

        // repo.updateUser(2, "Viet");
        repo.readUsers();

        // Delete a user
        // repo.deleteById(1);
        // std::cout << "Student deleted." << std::endl;
    } 
    catch (sql::SQLException& e) 
    {
        std::cerr << "SQLException: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
