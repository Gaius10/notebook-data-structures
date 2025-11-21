
CC       := clang
CFLAGS   := -std=c23 -Wall -Wextra -O3
LDFLAGS  :=
LDLIBS   := -lm
TARGET   := main
ANALYZER := ally

TARGET_OBJS := \
	build/app/main.o \
	build/app/invert.o \
	build/app/sequential_search.o \
	build/app/binary_search.o \
	build/app/recursive_binary_search.o

ANALYZER_OBJS := \
	build/app/invert.o \
	build/app/sequential_search.o \
	build/app/sequential_search_ordered.o \
	build/app/binary_search.o \
	build/app/recursive_binary_search.o \
	build/analyzer/main.o \
	build/analyzer/merge_sort.o

.PHONY: all clean run

all: $(TARGET) $(ANALYZER)

$(TARGET): $(TARGET_OBJS)
	$(CC) $(LDFLAGS) $(TARGET_OBJS) -o $@ $(LDLIBS)

$(ANALYZER): $(ANALYZER_OBJS)
	$(CC) $(LDFLAGS) $(ANALYZER_OBJS) -o $@ $(LDLIBS)

build/app/%.o: src/%.c lib/algorithms.h
	$(CC) $(CFLAGS) -c $< -o $@

build/analyzer/%.o: analyzer/%.c lib/algorithms.h lib/analysis.h lib/merge_sort.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f build/app/* build/analyzer/* $(TARGET)
	rm -f $(TARGET).zip

bundle: clean
	zip -r $(TARGET).zip Makefile src lib build
