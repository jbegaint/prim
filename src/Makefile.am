bin_PROGRAMS = programme1 programme2 view gtk_view

programme1_SOURCES = programme1.c liste.c file.c utils.c sommet.c algo.c arbre.c
programme2_SOURCES = programme2.c liste.c file.c utils.c sommet.c algo.c arbre.c
view_SOURCES = mainview.c view.c liste.c file.c utils.c sommet.c algo.c arbre.c 

include_HEADERS = sommet.h arc.h arbre.h liste.h file.h utils.h algo.h view.h

gtk_view_SOURCES = gtk_view.c
gtk_view_CPPFLAGS = @GTK_CFLAGS@
gtk_view_LDADD = @GTK_LIBS@

CLEANFILES = *~