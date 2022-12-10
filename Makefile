CC=zig cc
CFLAGS=-c -pedantic -Werror -std=c99

BIN=./bin
SRC=./src
OBJ=./obj
INC=./inc

all: $(BIN)/warp

run: all
	$(BIN)/warp $(ARGS)

$(BIN)/warp: $(OBJ)/main.o $(OBJ)/warp.o
ifeq ($(OS),Windows_NT)
	$(CC) $(OBJ)/main.o $(OBJ)/warp.o -lm -o $(BIN)/warp.exe
else
	$(CC) $(OBJ)/main.o $(OBJ)/warp.o -lm -o $(BIN)/warp
endif

$(OBJ)/main.o: $(SRC)/main.c
	$(CC) $(CFLAGS) $(SRC)/main.c -I$(INC) -o $(OBJ)/main.o

$(OBJ)/warp.o: $(SRC)/warp.c $(INC)/warp.h
	$(CC) $(CFLAGS) $(SRC)/warp.c -I$(INC) -o $(OBJ)/warp.o

clean:
	rm -rvf $(OBJ)/*.o $(BIN)/*
