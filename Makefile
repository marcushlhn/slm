CXX = g++
CXXFLAGS = -std=c++20
SOURCES = $(wildcard src/*.cpp)
TARGET = slm

.PHONY: all clean

all:
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)