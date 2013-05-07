AM_CPPFLAGS=-I$(top_builddir)/include


DEPS = liste.c file.c utils.c algo.c arbre.c
bin_PROGRAMS = programme1 programme2 view tests

programme1_SOURCES = programme1.c $(DEPS)
programme2_SOURCES = programme2.c $(DEPS)
view_SOURCES = mainview.c view.c $(DEPS)

#ifdef PHELMA_FLAG
	view_LDFLAGS=-L$(DIRSDL)/lib -lSDL_draw
#endif

tests_SOURCES = tests.c $(DEPS)

CLEANFILES = *~
