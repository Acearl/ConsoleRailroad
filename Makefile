CXX = g++
CXXFLAGS = -Iinclude -Wall
TARGET = main

all: $(TARGET)

$(TARGET): src/main.cpp
    $(CXX) $(CXXFLAGS) -o build/$(TARGET) src/main.cpp

clean:
    rm -f build/$(TARGET)
