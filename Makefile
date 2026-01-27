CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = CyanChemistry
SRC = CyanChemistry.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)


