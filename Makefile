# Project name and source file
PROJECT_NAME = DatabaseExample
SRC = main.cpp DataBase.cpp Student.cpp
# Path to mySQL library
MYSQL_INCLUDE = /usr/include/cppconn
MYSQL_LIB = /usr/lib/x86_64-linux-gnu

# Setting flags for compiler
CXX = g++
CXXFLAGS = -std=c++14 -Wall -I$(MYSQL_INCLUDE)

# Liên kết với thư viện MySQL
LDFLAGS = -L$(MYSQL_LIB) -lmysqlcppconn

# Tên file thực thi
TARGET = $(PROJECT_NAME)

# Quy trình biên dịch
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Clean: Xóa file biên dịch và file thực thi
clean:
	rm -f $(TARGET)

.PHONY: all clean
