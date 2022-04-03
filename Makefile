CPP_FLAGS = -c
COMPILER = g++

main: chess_board.o utils.o main.o
		$(COMPILER) -o CHESS.o chess_board.o utils.o main.o
main.o: main.cpp
		$(COMPILER) $(CPP_FLAGS) main.cpp
chess_board.o: chess_board.cpp
		$(COMPILER) $(CPP_FLAGS) chess_board.cpp
utils.o: utils.cpp
		$(COMPILER) $(CPP_FLAGS) utils.cpp
clean: 
	rm -f *.o
