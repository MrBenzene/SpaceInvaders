CC = gcc
OBJ = buffer.o main.o astro.o alieni.o menu.o matt.o
EXE = spaceinvaders

$(EXE) : $(OBJ)
	gcc  $(OBJ) -o $(EXE) -lncurses -lpthread

buffer.o : buffer.c buffer.h
	gcc -c buffer.c -lncurses -lpthread

main.o : main.c
	gcc -c main.c -lncurses -lpthread
	
astro.o : astro.c astro.h
	gcc -c astro.c -lncurses -lpthread

alieni.o : alieni.c alieni.h
	gcc -c alieni.c -lncurses -lpthread
	
matt.o : matt.c matt.h
	gcc -c matt.c -lncurses -lpthread
	
menu.o : menu.c menu.h
	gcc -c menu.c -lncurses -lpthread	

clean :
	rm $(OBJ) $(EXE)
	

