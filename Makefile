CC = clang
CFLAGS = -std=c11 -Wall -Wextra -g -fsanitize=address,undefined -MMD -MP

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

build/interp: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build

-include $(OBJ:.o=.d)
.PHONY: clean