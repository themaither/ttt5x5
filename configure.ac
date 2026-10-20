#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.72])
AC_INIT([ttt5x5], [0.0.8], [themaither@gmail.com])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AS_IF([test "x$USE_EMSCRIPTEN" = "xyes"],
  [
    AC_MSG_NOTICE([using emscripten settings])
  ])

gl_EARLY
AC_PROG_CC

gl_INIT

AS_IF([test "x$COMPILE_RAYLIB" = "xyes"],
  [
    AC_MSG_NOTICE([raylib going to be compiled])
    AC_MSG_NOTICE([ensure that '${srcdir}' has raylib source code, ])
    AC_MSG_NOTICE([and you have CMake installed])

    [RAYLIB_CFLAGS="-I${srcdir}/raylib/src"]

    AS_IF([test "x$USE_EMSCRIPTEN" = "xyes"],
      [
        [RAYLIB_LIBS="-Lraylib/raylib -lraylib"]
      ],
      [
        [RAYLIB_LIBS="-Lraylib/raylib -lraylib -lX11"]
      ])

    AC_SUBST([RAYLIB_CFLAGS])
    AC_SUBST([RAYLIB_LIBS])

    # CMake is used to compile raylib
    AS_IF([test "x$USE_EMSCRIPTEN" = "xyes"],
      [
        [EMCMAKE_CMAKE="emcmake cmake"]
      ],
      [
        [EMCMAKE_CMAKE="cmake"]
      ])
    AC_SUBST([EMCMAKE_CMAKE])

    RAYLIB_DEPENDENCIES="raylib/raylib/libraylib.a"
    AC_SUBST([RAYLIB_DEPENDENCIES])
  ],
  [
    AC_MSG_NOTICE([using pkg-config to resolve raylib])
    PKG_CHECK_MODULES([RAYLIB], [raylib])
    RAYLIB_DEPENDENCIES=""
    AC_SUBST([RAYLIB_DEPENDENCIES])
  ])

AS_IF([test "x$USE_READLINE" = "xno"],
  [
    [READLINE_CFLAGS=""]
    [READLINE_LIBS=""]
    AC_SUBST([READLINE_CFLAGS])
    AC_SUBST([READLINE_LIBS])
    AC_DEFINE([TMLIB_USE_READLINE], [0], [Whether or not tmlib should use GNU Readline])
  ],
  [
    PKG_CHECK_MODULES([READLINE], [readline])
  ])

AS_IF([test "x$TMLIB_OPTBUS" = "xno"],
  [
    AC_DEFINE([TMLIB_OPTBUS], [0], [Disable or enable tmlib optbus library])
  ])

# Flags used to compile using emscripten toolchain
AS_IF([test "x$USE_EMSCRIPTEN" = "xyes"],
  [
    [EMSCRIPTEN_LDFLAGS="-sUSE_GLFW=3 -sASSERTIONS=1 -sWASM=1 -sASYNCIFY -sGL_ENABLE_GET_PROC_ADDRESS=1"]
  ],
  [
    [EMSCRIPTEN_LDFLAGS=""]
  ])

AC_SUBST([EMSCRIPTEN_LDFLAGS])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([lib/Makefile])
AC_CONFIG_FILES([tm/Makefile])
AC_CONFIG_HEADERS([config.h])
AC_OUTPUT
