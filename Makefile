CC = tcc
CFLAGS = -pedantic -Wall -Wextra -O2 -march=native

TARGET = build/666
SRC = src/main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

run:
	$(TARGET)

clean:
	rm $(TARGET)
