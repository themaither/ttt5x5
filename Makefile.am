SUBDIRS = lib
ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = m4/gnulib-cache.m4

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
                 src/database.c src/database.h \
                 src/draw.c src/draw.h \
                 src/title.c src/title.h \
                 src/dlf.c src/dlf.h \
                 src/strdupf.c src/strdupf.h \
                 src/gamescript.c src/gamescript.h \
                 assets.c

BUILT_SOURCES = assets.c

ttt5x5_CFLAGS = -g -DPKGDATADIR="${PKGDATADIR}" -I${srcdir}/src \
                ${RAYLIB_CFLAGS} \
                -I${srcdir}/lib -Ilib

ttt5x5_LDADD = -lm $(HARD_LOCALE_LIB) $(LIBC32CONV) \
               $(LIBUNISTRING) $(MBRTOWC_LIB) $(SETLOCALE_NULL_LIB) ${LIBGNU} \
               -Llib -lgnu ${RAYLIB_LIBS} ${EMSCRIPTEN_LDFLAGS}

ttt5x5_DEPENDENCIES = ${RAYLIB_DEPENDENCIES}

raylib/raylib/libraylib.a :
	${EMCMAKE_CMAKE} ${srcdir}/raylib -B ./raylib
	cd ./raylib; make

www :
	install -D ttt5x5 www/ttt5x5.js
	install -D ttt5x5.wasm www/ttt5x5.wasm
	sed 's/{{{ SCRIPT }}}/<script src="ttt5x5.js"><\/script>/' <${srcdir}/raylib/src/shell.html >www/index.html

.PHONY : www

assets.c :
	echo "" > assets.c
	echo "" > assets.h
	xxd -n assets_black16 -i ${srcdir}/assets/black16.png >>assets.c
	echo "extern unsigned char assets_black16[];" >> assets.h
	echo "extern unsigned int assets_black16_len;" >> assets.h
	xxd -n assets_black48 -i ${srcdir}/assets/black48.png >>assets.c
	echo "extern unsigned char assets_black48[];" >> assets.h
	echo "extern unsigned int assets_black48_len;" >> assets.h
	xxd -n assets_layout -i ${srcdir}/assets/layout.svg >>assets.c
	echo "extern unsigned char assets_layout[];" >> assets.h
	echo "extern unsigned int assets_layout_len;" >> assets.h
	xxd -n assets_leave -i ${srcdir}/assets/leave.png >>assets.c
	echo "extern unsigned char assets_leave[];" >> assets.h
	echo "extern unsigned int assets_leave_len;" >> assets.h
	xxd -n assets_back -i ${srcdir}/assets/back.png >>assets.c
	echo "extern unsigned char assets_back[];" >> assets.h
	echo "extern unsigned int assets_back_len;" >> assets.h
	xxd -n assets_session -i ${srcdir}/assets/session.png >>assets.c
	echo "extern unsigned char assets_session[];" >> assets.h
	echo "extern unsigned int assets_session_len;" >> assets.h
	xxd -n assets_white16 -i ${srcdir}/assets/white16.png >>assets.c
	echo "extern unsigned char assets_white16[];" >> assets.h
	echo "extern unsigned int assets_white16_len;" >> assets.h
	xxd -n assets_white48 -i ${srcdir}/assets/white48.png >>assets.c
	echo "extern unsigned char assets_white48[];" >> assets.h
	echo "extern unsigned int assets_white48_len;" >> assets.h
	xxd -n assets_dark_green48 -i ${srcdir}/assets/dark_green48.png >>assets.c
	echo "extern unsigned char assets_dark_green48[];" >> assets.h
	echo "extern unsigned int assets_dark_green48_len;" >> assets.h
	xxd -n assets_light_green48 -i ${srcdir}/assets/light_green48.png >>assets.c
	echo "extern unsigned char assets_light_green48[];" >> assets.h
	echo "extern unsigned int assets_light_green48_len;" >> assets.h
	xxd -n assets_picker -i ${srcdir}/assets/picker.png >>assets.c
	echo "extern unsigned char assets_picker[];" >> assets.h
	echo "extern unsigned int assets_picker_len;" >> assets.h
	xxd -n assets_completed -i ${srcdir}/assets/completed.png >>assets.c
	echo "extern unsigned char assets_completed[];" >> assets.h
	echo "extern unsigned int assets_completed_len;" >> assets.h
	xxd -n assets_prev -i ${srcdir}/assets/prev.png >>assets.c
	echo "extern unsigned char assets_prev[];" >> assets.h
	echo "extern unsigned int assets_prev_len;" >> assets.h
	xxd -n assets_next -i ${srcdir}/assets/next.png >>assets.c
	echo "extern unsigned char assets_next[];" >> assets.h
	echo "extern unsigned int assets_next_len;" >> assets.h
	xxd -n assets_digit_0 -i ${srcdir}/assets/digit_0.png >>assets.c
	echo "extern unsigned char assets_digit_0[];" >> assets.h
	echo "extern unsigned int assets_digit_0_len;" >> assets.h
	xxd -n assets_digit_1 -i ${srcdir}/assets/digit_1.png >>assets.c
	echo "extern unsigned char assets_digit_1[];" >> assets.h
	echo "extern unsigned int assets_digit_1_len;" >> assets.h
	xxd -n assets_digit_2 -i ${srcdir}/assets/digit_2.png >>assets.c
	echo "extern unsigned char assets_digit_2[];" >> assets.h
	echo "extern unsigned int assets_digit_2_len;" >> assets.h
	xxd -n assets_digit_3 -i ${srcdir}/assets/digit_3.png >>assets.c
	echo "extern unsigned char assets_digit_3[];" >> assets.h
	echo "extern unsigned int assets_digit_3_len;" >> assets.h
	xxd -n assets_digit_4 -i ${srcdir}/assets/digit_4.png >>assets.c
	echo "extern unsigned char assets_digit_4[];" >> assets.h
	echo "extern unsigned int assets_digit_4_len;" >> assets.h
	xxd -n assets_digit_5 -i ${srcdir}/assets/digit_5.png >>assets.c
	echo "extern unsigned char assets_digit_5[];" >> assets.h
	echo "extern unsigned int assets_digit_5_len;" >> assets.h
	xxd -n assets_digit_6 -i ${srcdir}/assets/digit_6.png >>assets.c
	echo "extern unsigned char assets_digit_6[];" >> assets.h
	echo "extern unsigned int assets_digit_6_len;" >> assets.h
	xxd -n assets_digit_7 -i ${srcdir}/assets/digit_7.png >>assets.c
	echo "extern unsigned char assets_digit_7[];" >> assets.h
	echo "extern unsigned int assets_digit_7_len;" >> assets.h
	xxd -n assets_digit_8 -i ${srcdir}/assets/digit_8.png >>assets.c
	echo "extern unsigned char assets_digit_8[];" >> assets.h
	echo "extern unsigned int assets_digit_8_len;" >> assets.h
	xxd -n assets_digit_9 -i ${srcdir}/assets/digit_9.png >>assets.c
	echo "extern unsigned char assets_digit_9[];" >> assets.h
	echo "extern unsigned int assets_digit_9_len;" >> assets.h
	xxd -n assets_moves -i ${srcdir}/assets/moves.png >>assets.c
	echo "extern unsigned char assets_moves[];" >> assets.h
	echo "extern unsigned int assets_moves_len;" >> assets.h
	xxd -n assets_selection_bl -i ${srcdir}/assets/selection_bl.png >>assets.c
	echo "extern unsigned char assets_selection_bl[];" >> assets.h
	echo "extern unsigned int assets_selection_bl_len;" >> assets.h
	xxd -n assets_selection_br -i ${srcdir}/assets/selection_br.png >>assets.c
	echo "extern unsigned char assets_selection_br[];" >> assets.h
	echo "extern unsigned int assets_selection_br_len;" >> assets.h
	xxd -n assets_selection_tl -i ${srcdir}/assets/selection_tl.png >>assets.c
	echo "extern unsigned char assets_selection_tl[];" >> assets.h
	echo "extern unsigned int assets_selection_tl_len;" >> assets.h
	xxd -n assets_selection_tr -i ${srcdir}/assets/selection_tr.png >>assets.c
	echo "extern unsigned char assets_selection_tr[];" >> assets.h
	echo "extern unsigned int assets_selection_tr_len;" >> assets.h
	xxd -n assets_title -i ${srcdir}/assets/title.png >>assets.c
	echo "extern unsigned char assets_title[];" >> assets.h
	echo "extern unsigned int assets_title_len;" >> assets.h
	xxd -n assets_level_select -i ${srcdir}/assets/level_select.png >>assets.c
	echo "extern unsigned char assets_level_select[];" >> assets.h
	echo "extern unsigned int assets_level_select_len;" >> assets.h
	xxd -n assets_level_select_hovered -i ${srcdir}/assets/level_select_hovered.png >>assets.c
	echo "extern unsigned char assets_level_select_hovered[];" >> assets.h
	echo "extern unsigned int assets_level_select_hovered_len;" >> assets.h
	xxd -n assets_level_select_pressed -i ${srcdir}/assets/level_select_pressed.png >>assets.c
	echo "extern unsigned char assets_level_select_pressed[];" >> assets.h
	echo "extern unsigned int assets_level_select_pressed_len;" >> assets.h
	xxd -n assets_quit -i ${srcdir}/assets/quit.png >>assets.c
	echo "extern unsigned char assets_quit[];" >> assets.h
	echo "extern unsigned int assets_quit_len;" >> assets.h
	xxd -n assets_quit_hovered -i ${srcdir}/assets/quit_hovered.png >>assets.c
	echo "extern unsigned char assets_quit_hovered[];" >> assets.h
	echo "extern unsigned int assets_quit_hovered_len;" >> assets.h
	xxd -n assets_quit_pressed -i ${srcdir}/assets/quit_pressed.png >>assets.c
	echo "extern unsigned char assets_quit_pressed[];" >> assets.h
	echo "extern unsigned int assets_quit_pressed_len;" >> assets.h
	xxd -n assets_button_hovered -i ${srcdir}/assets/button_hovered.png >>assets.c
	echo "extern unsigned char assets_button_hovered[];" >> assets.h
	echo "extern unsigned int assets_button_hovered_len;" >> assets.h
	xxd -n assets_button_pressed -i ${srcdir}/assets/button_pressed.png >>assets.c
	echo "extern unsigned char assets_button_pressed[];" >> assets.h
	echo "extern unsigned int assets_button_pressed_len;" >> assets.h
	xxd -n assets_button -i ${srcdir}/assets/button.png >>assets.c
	echo "extern unsigned char assets_button[];" >> assets.h
	echo "extern unsigned int assets_button_len;" >> assets.h
	xxd -n assets_dejavusans -i ${srcdir}/assets/dejavusans.ttf >>assets.c
	echo "extern unsigned char assets_dejavusans[];" >> assets.h
	echo "extern unsigned int assets_dejavusans_len;" >> assets.h

