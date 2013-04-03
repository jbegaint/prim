# DIRSDL=/home/jean/Documents/Cours/Info/C/S2/TD7/SDLPHELMA
# CFLAGS=-c -g -O2 -I$(DIRSDL)/include/SDL -I$(DIRSDL)/include
CFLAGS=-c -g -O2
# LFLAGS=-L$(DIRSDL)/lib -lSDL -lSDL_ttf -lSDL_image  -lSDL_sound -lSDL_phelma -lSDL_draw -lm


tests : tests.o liste.o 
	gcc -o tests liste.o tests.o 

liste.o : liste.c
	gcc $(CFLAGS) liste.c

