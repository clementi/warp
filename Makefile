CC=cc
CFLAGS=-c -pedantic -Werror -std=c99

NAME=warp

BIN=./bin
SRC=./src
OBJ=./obj
INC=./inc

ifeq ($(OS),Windows_NT)
	EXT=.exe
else
	EXT=
endif

all: $(BIN)/$(NAME)

run: all
	$(BIN)/$(NAME) $(ARGS)

$(BIN)/$(NAME): $(OBJ)/main.o $(OBJ)/warp.o
	$(CC) $(OBJ)/main.o $(OBJ)/warp.o -lm -o $(BIN)/$(NAME)$(EXT)

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) $(SRC)/main.c -I$(INC) -o $(OBJ)/main.o

$(OBJ)/warp.o: $(SRC)/warp.c $(INC)/warp.h
	$(CC) $(CFLAGS) $(SRC)/warp.c -I$(INC) -o $(OBJ)/warp.o

clean:
	rm -rvf $(OBJ)/*.o $(BIN)/*
