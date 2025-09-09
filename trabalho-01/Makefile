
CC       := gcc
CFLAGS   := -std=c11 -Wall -Wextra -Wpedantic -O3
LDFLAGS  :=
LDLIBS   := -lm
TARGET   := main
ANALYZER := analyzer

TARGET_OBJS := build/app/main.o \
	build/app/invert.o \
	build/app/sequential_search.o \
	build/app/binary_search.o \
	build/app/recursive_binary_search.o

ANALYZER_OBJS := build/analyzer/invert.o \
	build/analyzer/sequential_search.o \
	build/analyzer/binary_search.o \
	build/analyzer/recursive_binary_search.o

.PHONY: all clean run

all: $(TARGET) $(ANALYZER)

$(TARGET): $(TARGET_OBJS)
	$(CC) $(LDFLAGS) $(TARGET_OBJS) -o $@ $(LDLIBS)

$(ANALYZER): $(ANALYZER_OBJS)
	$(CC) $(LDFLAGS) $(ANALYZER_OBJS) -o $@ $(LDLIBS)

build/app/%.o: src/%.c lib/%.h
	$(CC) $(CFLAGS) -c $< -o $@
	
build/analyzer/%.o: analyzer/%.c lib/%.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

bundle:
	rm $(TARGET).zip
	zip -r $(TARGET).zip Makefile src lib build

