# Project name and source file
PROJECT_NAME = DatabaseExample
SRC = main.cpp DataBase.cpp
# Path to mySQL library
MYSQL_INCLUDE = /usr/include/cppconn
MYSQL_LIB = /usr/lib/x86_64-linux-gnu

# Setting flags for compiler
CXX = g++
CXXFLAGS = -std=c++14 -Wall -I$(MYSQL_INCLUDE)

# Link to Sqlite library
LDFLAGS = -L$(MYSQL_LIB) -lsqlite3

# Name execute file
TARGET = $(PROJECT_NAME)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Clean: Delete compiler file and execute file
clean:
	rm -f $(TARGET)

.PHONY: all clean
