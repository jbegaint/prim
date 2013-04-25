AC_INIT([Projet Info], [1.0])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CC

AC_CHECK_HEADERS([float.h stdlib.h string.h])

AC_FUNC_MALLOC
AC_TYPE_SIZE_T

SDL_VERSION=1.1.1
AM_PATH_SDL($SDL_VERSION,
            :,
	    	AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)

AC_CHECK_LIB([SDL_ttf], [TTF_Init])


CFLAGS="$CFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

AM_CONFIG_HEADER([config.h:config.hin])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
