TARGET = myclient
SRC_FILE = $(TARGET).cpp

CC = g++
CFLAGS = -lm -std=c++14

all: clean build run

build:
	g++ $(SRC_FILE) -o $(TARGET).o

run:
	./$(TARGET).o

clean:
	rm -f $(TARGET) *.o
