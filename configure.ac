dnl ner: configure.ac

AC_PREREQ(2.59)

AC_INIT([one_astronaut], [0.0.1], [mforney@mforney.org])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_LANG([C])

AC_CONFIG_SRCDIR([main.c])

m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_PROG_CC

PKG_PROG_PKG_CONFIG([0.9.0])

dnl Check for libraries {{{
PKG_CHECK_MODULES([allegro], [allegro-5.0],,
    [AC_MSG_ERROR([one_astronaut requires allegro])])
dnl }}}

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

