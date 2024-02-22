TARGET = ah
SRC_FILE = $(TARGET).cpp

CC = g++
CFLAGS = -lm -std=c++14

all: clean build

build:
	g++ $(SRC_FILE) -o $(TARGET).o

run:
	./$(TARGET).o

clean:
	rm -f $(TARGET) *.o
	
push:
	git add .
	git commit -a -m "Sleep"
	git push
