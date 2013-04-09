# DIRSDL=/home/jean/Documents/Cours/Info/C/S2/TD7/SDLPHELMA
# CFLAGS=-c -g -O2 -I$(DIRSDL)/include/SDL -I$(DIRSDL)/include
CFLAGS=-c -g -O2
# LFLAGS=-L$(DIRSDL)/lib -lSDL -lSDL_ttf -lSDL_image  -lSDL_sound -lSDL_phelma -lSDL_draw -lm

all: programme1 tests lecture

programme1: programme1.o liste.o file.o sommet.o

tests: tests.o liste.o file.o arbre.o 
	gcc  -o $@ $^ $(LDFLAGS)

lecture: lecture.o liste.o file.o utils.o
	gcc  -o $@ $^ $(LDFLAGS)

%.o: %.c
	gcc $(CFLAGS) $< 

clean:
	rm *.o

