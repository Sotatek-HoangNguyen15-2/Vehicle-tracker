find_package(MySQL REQUIRED)
include_directories(${MYSQL_INCLUDE_DIR})
link_directories(${MYSQL_LIB_DIR})

add_executable(my_program main.cpp)
target_link_libraries(my_program mysqlcppconn)
