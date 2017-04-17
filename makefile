.PHONY: test clean

CFLAGS = -Wall -Wextra -Wno-format -std=c11 -lpthread -I include

all: main

main: src/*.c
	$(CC) $(CFLAGS) $^ -o $@

test: main
	./main test/input_grid_correto.txt 4
	@echo
	./main test/input_grid_errado.txt 4

clean:
	rm main
