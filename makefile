CFLAGS = -Wall -Wno-format -std=c11 -lpthread -I include/

all: main

main: src/main.c src/utils.c
	$(CC) $(CFLAGS) $^ -o main

test: main
	@./main test/input_grid_correto.txt
	@./main test/input_grid_errado.txt

clean:
	rm main
