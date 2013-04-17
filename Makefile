# DIRSDL=/home/jean/Documents/Cours/Info/C/S2/TD7/SDLPHELMA
# CFLAGS=-c -g -O2 -I$(DIRSDL)/include/SDL -I$(DIRSDL)/include
<<<<<<< HEAD
CFLAGS=-c -g -O2
# LFLAGS=-L$(DIRSDL)/lib -lSDL  -lSDL_image  -lSDL_sound -lSDL_phelma -lSDL_draw -lm
LFLAGS=-lSDL -lSDL_ttf
=======
CFLAGS=-c -g -O2 
#-Wall 
#-Wextra -pedantic 
# -ansi
# LFLAGS=-L$(DIRSDL)/lib -lSDL -lSDL_ttf -lSDL_image  -lSDL_sound -lSDL_phelma -lSDL_draw -lm
LFLAGS=-lSDL
>>>>>>> 44b25c1dc7eccb8f4627c43df522552d0b98f6bf

all: programme1 tests lecture view

programme1: programme1.o liste.o file.o sommet.o utils.o

tests: tests.o liste.o file.o arbre.o 
	gcc  -o $@ $^ $(LFLAGS)

lecture: lecture.o liste.o file.o utils.o 
	gcc  -o $@ $^ $(LFLAGS)

view:  mainview.o view.o utils.o liste.o file.o sommet.o
	gcc  -o $@ $^ $(LFLAGS)

%.o: %.c
	gcc $(CFLAGS) $< 

clean:
	rm *.o

