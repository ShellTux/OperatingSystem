OBJ_DIR = obj
SRC_DIR = src

.PHONY: clean, mrproper
CC = gcc
CFLAGS = -g -Wall -Wextra

all: processes

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir --parents "$(shell dirname "$@")"
	$(CC) $(CFLAGS) -c -o $@ $<

processes: $(OBJ_DIR)/processes.o
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f *.o core.*

mrproper: clean
	rm -f processes
