#CFLAGS = -g -Wall -Wextra -pedantic -Wno-unused-parameter
CFLAGS = -g -Wno-unused-parameter
CC = gcc
INCLUDE= ./include/
SRC= ./src/
OBJ=./obj/

PROGRAMS =   tests_ecosys ecosys test2_main

.PHONY:	all clean

OBJS = $(OBJ)ecosys.o $(OBJ)main_tests.o $(OBJ)main_ecosys.o $(OBJ)main_tests.o 


all: $(PROGRAMS)

$(PROGRAMS): $(OBJS)
	$(CC) -o $@ $^ 

$(OBJ)%.o:$(SRC)%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE) 


clean:
	rm -f $(OBJ)*.o *~ $(PROGRAMS)
