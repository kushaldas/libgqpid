AC_INIT([libgqpid], [0.1], [kushaldas@gmail.com])
AM_INIT_AUTOMAKE(dist-bzip2)

AM_MAINTAINER_MODE

AC_PROG_LIBTOOL

AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

ac_save_LIBS="$LIBS"
LIBS="$LIBS -lqpidmessaging"

AC_LANG_PUSH([C++])
AC_MSG_CHECKING([if qpid c++ client libraries are present])
AC_LINK_IFELSE(
	[AC_LANG_PROGRAM([#include <qpid/messaging/Connection.h>], [qpid::messaging::Connection con])],
	[QPID_LIBS="$LIBS"],
	[AC_MSG_ERROR([qpid c++ client development libraries not found])])

AC_LANG_POP

LIBS=$ac_save_LIBS
AC_SUBST(QPID_LIBS)

PKG_CHECK_MODULES(GLIB, glib-2.0)
AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)
PKG_CHECK_MODULES(GOBJECT, glib-2.0)
AC_SUBST(GOBJECT_CFLAGS)
AC_SUBST(GOBJECT_LIBS)

AC_OUTPUT([Makefile src/Makefile])
