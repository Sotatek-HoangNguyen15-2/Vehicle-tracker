#ifndef USER_H
#define USER_H
#include <string>

class Student {
public:
    int id;
    std::string name;

    Student(int id, const std::string& name) : id(id), name(name) {}
};

#endif