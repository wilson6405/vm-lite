SRC_FILES = main.c
CFLAGS = -Wall -Wextra -g -std=c11
CC = clang

all:
	@$(CC) $(SRC_FILES) $(CFLAGS) -o vm
