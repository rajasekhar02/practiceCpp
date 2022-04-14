CPP_FLAGS = -c
COMPILER = g++

main: chess_board.o utils.o main.o
	$(COMPILER) -o CHESS_BOARD.o chess_board.o utils.o main.o
main.o: 
	$(COMPILER) $(CPP_FLAGS) main.cpp
chess_board.o: 
	$(COMPILER) $(CPP_FLAGS) chess_board.cpp
utils.o: 
	$(COMPILER) $(CPP_FLAGS) utils.cpp
clean: 
	rm -f *.o
