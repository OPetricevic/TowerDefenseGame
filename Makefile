CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsqlite3

SRC = src/main.cpp \
      src/game/Game.cpp \
      src/game/Enemy.cpp \
      src/game/Tower.cpp \
      src/database/Database.cpp \
      src/database/Migration.cpp \
      src/database/Seeder.cpp

TARGET = p1_game

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
