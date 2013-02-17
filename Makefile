CC=clang
CFLAGS=-c -Weverything

BIN=./bin
SRC=./src
OBJ=./obj

all: $(BIN)/warp

run: all
	$(BIN)/warp $(ARGS)

$(BIN)/warp: $(OBJ)/warp.o
	$(CC) $(OBJ)/warp.o -lm -o $(BIN)/warp

$(OBJ)/warp.o: $(SRC)/warp.c
	$(CC) $(CFLAGS) $(SRC)/warp.c -o $(OBJ)/warp.o

clean:
	rm -rvf $(OBJ)/*.o $(BIN)/warp
