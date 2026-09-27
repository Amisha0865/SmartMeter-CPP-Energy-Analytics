CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
TARGET = smartmeter

all: $(TARGET)

$(TARGET): src/main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

run: all
	./$(TARGET)

test: all
	bash tests/smoke_test.sh

clean:
	rm -f $(TARGET)
.PHONY: all run test clean
