# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = twixt

# Source files
SRCS = main.c game.c

# Object files
OBJS = main.o game.o

# Default target
all: $(TARGET)

# Link object files
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	@echo Build complete! Run with: ./$(TARGET)

# Compile source files
main.o: main.c game.h
	$(CC) $(CFLAGS) -c main.c

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

# Clean
clean:
	del /Q *.o $(TARGET).exe 2>nul || rm -f *.o $(TARGET)
	@echo Cleaned build files

# Run
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run