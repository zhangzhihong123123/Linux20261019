CC ?= cc
CFLAGS ?= -std=c99 -Wall -Wextra -Werror -pedantic
TARGET := arithmetic_tests
SOURCES := add.c subtract.c multiply.c divide.c test.c
OBJECTS := $(SOURCES:.c=.o)

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)
