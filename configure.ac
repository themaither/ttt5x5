#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.72])
AC_INIT([ttt5x5], [0.1.0], [themaither@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])


gl_EARLY
AC_PROG_CC

gl_INIT



# Testing if we are using emscripten

AS_IF([test "x$USE_EMSCRIPTEN" = "xyes"],
  [
    AC_MSG_NOTICE([using emscripten settings])
    AC_DEFINE([PLATFORM_WEB], [], [Defined if programs is compiled to run in a browser.])
    [EMSCRIPTEN_LDFLAGS="-sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sASYNCIFY -sGL_ENABLE_GET_PROC_ADDRESS=1"]
  ],
  [
    [EMSCRIPTEN_LDFLAGS=""]
  ])
AC_ARG_VAR([USE_EMSCRIPTEN], [set to 'yes' for emscripten support])
AC_ARG_VAR([EMSCRIPTEN_LDFLAGS], [flags passed to linker if compiling using emscripten])



# Testing for 'emcmake cmake'

AS_IF([test "x$USE_EMSCRIPTEN" = "xyes"],
  [
    [EMCMAKE_CMAKE="emcmake cmake"]
  ],
  [
    [EMCMAKE_CMAKE="cmake"]
  ])
AC_ARG_VAR([EMCMAKE_CMAKE], [emscripten CMake command])



# Checking for readline


AC_ARG_VAR([WITH_READLINE],
  [disable or enable interactive input using GNU readline])

AS_IF([test "x$WITH_READLINE" != "xyes"],
[
  [with_readline="$WITH_READLINE"]
])

AC_ARG_WITH([readline],
  [AS_HELP_STRING([--without-readline],
    [disable interactive input using GNU readline])],
  [],
  [with_readline=yes])

AS_IF([test "x$with_readline" = "xno"],
  [
    [READLINE_CFLAGS=""]
    [READLINE_LIBS=""]
    AC_SUBST([READLINE_CFLAGS])
    AC_SUBST([READLINE_LIBS])
    AC_DEFINE([TMLIB_USE_READLINE], [0], [Whether or not tmlib should use GNU readline.])
  ],
  [
    PKG_CHECK_MODULES([READLINE], [readline])
  ])



# Checking for tmlib-optbus

AC_ARG_VAR([ENABLE_TMLIB_OPTBUS],
  [disable or enable tmlib program argument parser])

AS_IF([test "x$ENABLE_TMLIB_OPTBUS" != "xyes"],
[
  [enable_tmlib_optbus="$ENABLE_TMLIB_OPTBUS"]
])

AC_ARG_ENABLE([tmlib-optbus],
  [AS_HELP_STRING([--disable-tmlib-optbus],
    [disable tmlib program argument parser])],
  [],
  [enable_tmlib_optbus=yes])

AS_IF([test "x$enable_tmlib_optbus" = "xno"],
  [
    AC_DEFINE([TMLIB_OPTBUS], [0], [Disable or enable tmlib optbus library.])
  ])



# Checking for raylib

AC_ARG_VAR([COMPILE_RAYLIB], [set to 'yes' whether or not to compile Raylib
from source instead of finding it through pkg-config])
AS_IF([test "x$COMPILE_RAYLIB" = "xyes"],
  [
    AC_MSG_NOTICE([raylib going to be compiled])
    AC_MSG_NOTICE([ensure that '${srcdir}' has raylib source code, ])
    AC_MSG_NOTICE([and you have CMake installed])

    [RAYLIB_CFLAGS="-I${srcdir}/raylib/src"]
    [RAYLIB_LIBS="-Lraylib/raylib -lraylib"]

    AC_SUBST([RAYLIB_CFLAGS])
    AC_SUBST([RAYLIB_LIBS])


    RAYLIB_DEPENDENCIES="raylib/raylib/libraylib.a"
    AC_SUBST([RAYLIB_DEPENDENCIES])
  ],
  [
    AC_MSG_NOTICE([using pkg-config to resolve raylib])
    PKG_CHECK_MODULES([RAYLIB], [raylib])
    RAYLIB_DEPENDENCIES=""
    AC_SUBST([RAYLIB_DEPENDENCIES])
  ])



AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([lib/Makefile])
AC_CONFIG_FILES([tm/Makefile])
AC_CONFIG_HEADERS([config.h])
AC_OUTPUT
