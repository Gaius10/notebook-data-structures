CC       := clang
CFLAGS   := -std=c2x -Wall -Wextra -pedantic -O3
LDFLAGS  :=
LDLIBS   :=
TARGET   := main
TARGET_OBJS := build/main.o build/bigint.o

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(TARGET_OBJS)
	$(CC) $(LDFLAGS) $(TARGET_OBJS) -o $@ $(LDLIBS)

build/%.o: src/%.c lib/bigint.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f build/* $(TARGET)
	rm -f $(TARGET).zip

bundle: clean
	zip -r $(TARGET).zip Makefile src lib build
