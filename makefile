.PHONY: test clean

CFLAGS = -march=native -Wall -Wextra -std=c11 -lpthread -I include

all: main

main: src/*.c
	$(CC) $(CFLAGS) $^ -o $@

debug: CFLAGS += -g
debug: main

test: main
	./main test/input_grid_correto.txt 4
	@echo
	./main test/input_grid_errado.txt 4

clean:
	rm main
