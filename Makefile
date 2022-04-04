CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

TARGET = interpreter

.PHONY: all clean

all: $(TARGET)

$(TARGET): % : %.o
	$(CC) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<
