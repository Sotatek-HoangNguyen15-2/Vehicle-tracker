#include <iostream>
#include <string>
#include "DataBase.h"

int main() {
    try {
        // Initialize UserRepository SQLite, use path file database
        UserRepository repo("test_db.sqlite");

        repo.updateUser(2, "Hoang Tran");

        // Perform users
        std::cout << "\nUsers list:" << std::endl;
        repo.readUsers();

        // Find user by ID
        Student user = repo.findOneById(1);
        if (user.id != -1) {
            std::cout << "\nFounded user: ID = " << user.id << ", Name = " << user.name << std::endl;
        } else {
            std::cout << "\nNot founded user ID = 1." << std::endl;
        }

        repo.deleteById(1);
        std::cout << "\nUser ID = 1 was deleted." << std::endl;

        repo.readUsers();
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
