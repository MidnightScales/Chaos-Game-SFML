# Optimized for Mac Terminal (Homebrew paths)
TARGET := ChaosGame.out
SRC := ChaosGame.cpp

# CXX and Flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -I/opt/homebrew/include
LDFLAGS := -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
