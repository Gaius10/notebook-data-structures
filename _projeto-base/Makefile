
CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -O3
LDFLAGS :=
LDLIBS  := -lm
TARGET  := main
OBJS    := build/main.o build/Ponto.o

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

build/%.o: src/%.c lib/Ponto.h
	$(CC) $(CFLAGS) -c $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

