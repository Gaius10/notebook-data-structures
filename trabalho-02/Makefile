CC       := gcc
CFLAGS   := -std=c2x -Wall -Wextra -pedantic -O3
LDFLAGS  :=
LDLIBS   :=
TARGET   := main
TARGET_OBJS := bigint.o

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(TARGET_OBJS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET_OBJS) $(TARGET)
	rm -f $(TARGET).zip

bundle: clean
	zip -r $(TARGET).zip Makefile *.c *.h
