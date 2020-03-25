mine_sweeper.out: main_play.o board_setup.o valid_play.o
	
	gcc -g -Wall -Werror -o mine_sweeper.out main_play.o board_setup.o valid_play.o
    
main_play.o: main_play.c board_setup.h valid_play.h
	
	gcc -g -Wall -Werror -c main_play.c
    
valid_play.o: valid_play.c valid_play.h board_setup.h board_struct.h
	
	gcc -g -Wall -Werror -c valid_play.c
    
board_setup.o: board_setup.c board_setup.h valid_play.h board_struct.h
	
	gcc -g -Wall -Werror -c board_setup.c
    
clean:
	
	Rm -fr *.o *.out