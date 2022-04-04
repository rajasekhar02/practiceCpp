CPP_FLAGS = -c -o
COMPILER = g++

OBJS =  chess_board.o\
		utils.o\
		main.o\
		board_representation.o
main: $(OBJS)
		$(COMPILER) -o CHESS.o $(OBJS)
		
chess_board.o: chess_board.cpp
		$(COMPILER) $(CPP_FLAGS) $@ $<

utils.o: utils.cpp
		$(COMPILER) $(CPP_FLAGS) $@ $<
		
main.o: main.cpp
		$(COMPILER) $(CPP_FLAGS) $@ $<

clean: 
	rm -f *.o
