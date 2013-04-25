AC_INIT([Projet Info], [1.0])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_PROG_CC_C_O

AC_CHECK_HEADERS([float.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([string.h])
AC_FUNC_MALLOC
AC_TYPE_SIZE_T

SDL_VERSION=1.1.1
AM_PATH_SDL($SDL_VERSION,
            :,
	    	AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)

AM_PATH_GTK_2_0([2.10.0],
			:,
			AC_MSG_ERROR([Gtk+ 2.10.0 or higher required.]))

CFLAGS="$CFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

AM_CONFIG_HEADER([config.h:config.hin])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
