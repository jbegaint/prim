# DIRSDL=/home/jean/Documents/Cours/Info/C/S2/TD7/SDLPHELMA
# CFLAGS=-c -g -O2 -I$(DIRSDL)/include/SDL -I$(DIRSDL)/include
CFLAGS=-c -g -O2 -Wall -Wextra -ansi
#-Wall 
#-Wextra -pedantic 
# -ansi
# LFLAGS=-L$(DIRSDL)/lib -lSDL -lSDL_ttf -lSDL_image  -lSDL_sound -lSDL_phelma -lSDL_draw -lm
LFLAGS=-lSDL -lSDL_ttf

all: programme1 programme2 tests lecture view

programme2: programme2.o liste.o file.o sommet.o utils.o algo.o arbre.o

programme1: programme1.o liste.o file.o sommet.o utils.o algo.o arbre.o

tests: tests.o liste.o file.o arbre.o 
	gcc  -o $@ $^ $(LFLAGS)

lecture: lecture.o liste.o file.o utils.o 
	gcc  -o $@ $^ $(LFLAGS)

view:  mainview.o view.o utils.o liste.o file.o sommet.o algo.o arbre.o
	gcc  -o $@ $^ $(LFLAGS)

%.o: %.c
	gcc $(CFLAGS) $< 

clean:
	rm *.o

