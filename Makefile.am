bin_PROGRAMS = ttt5x5

ttt5x5_SOURCES = src/ttt5x5.c \
                 src/imath.c src/imath.h \
                 src/5x5.c src/5x5.h \
                 src/camera.c src/camera.h \
                 src/session.c src/session.h \
                 src/picker.c src/picker.h \
                 src/draw_field.c src/draw_field.h \
                 src/btn.c src/btn.h \
                 src/completed.c src/completed.h \
                 src/levels.X.h

ttt5x5_CFLAGS = -I${srcdir}/src ${RAYLIB_CFLAGS} -g \
                -DPKGDATADIR="\"${pkgdatadir}\"" # would probably fail 99% time

ttt5x5_LDADD = ${RAYLIB_LIBS} -lm

dist_pkgdata_DATA = assets/black16.png \
                    assets/black48.png \
                    assets/layout.svg \
                    assets/leave.png \
                    assets/leave_hovered.png \
                    assets/leave_pressed.png \
                    assets/back.png \
                    assets/back_hovered.png \
                    assets/back_pressed.png \
                    assets/session.png \
                    assets/solve.png \
                    assets/solve_hovered.png \
                    assets/solve_pressed.png \
                    assets/white16.png \
                    assets/white48.png \
                    assets/dark_green48.png \
                    assets/light_green48.png \
                    assets/picker.png \
                    assets/completed.png
