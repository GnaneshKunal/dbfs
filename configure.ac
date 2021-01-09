#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([dbfs], [0.1], [gnaneshkunal@outlook.com])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign 1.11.2])

AM_PROG_AR

# Checks for programs.
AC_PROG_CC
AC_PROG_LIBTOOL
AC_CONFIG_MACRO_DIRS([m4])
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADER_STDBOOL

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_MALLOC

dnl Enable debug
AC_ARG_ENABLE([debug],
    AS_HELP_STRING([--enable-debug], [Enable debug]))

AS_IF([test "x$enable_debug" = "xyes"], [
            CFLAGS='-g3 -O0 -fno-omit-frame-pointer -fno-optimize-sibling-calls -rdynamic -Wimplicit'
])

dnl with asan
AC_ARG_WITH([asan],
    AS_HELP_STRING([--with-asan], [With address sanitizer]))

AS_IF([test "x$with_asan" = "xyes"], [
            CFLAGS+=' -fsanitize=address'
])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 tests/Makefile])
AC_OUTPUT
