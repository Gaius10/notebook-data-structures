
CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -O3
LDFLAGS :=
LDLIBS  := -lm
TARGET  := main
OBJS    := build/main.o \
		   build/invert.o \
		   build/sequential_search.o \
		   build/binary_search.o \
		   build/recursive_binary_search.o

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

build/%.o: src/%.c lib/actions.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

bundle:
	rm $(TARGET).zip
	zip -r $(TARGET).zip Makefile src lib build

