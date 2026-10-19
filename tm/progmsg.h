/* progmsg.h: logging
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef PROGMSG_H_INCLUDED
#define PROGMSG_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/* Sets a name, which is shown with messages.  Ussually it is set to argv[0]. */
void progmsg_setname (const char *);

/* Print a message. */
void progmsg  (const char *fmt, ...);
void vprogmsg (const char *fmt, va_list);

/* Fancy. */
#define progmsg_pos(FMT, ...)                                                  \
    progmsg ("%s:%d (%s): " FMT, __FILE__, __LINE__,                           \
                                 __PRETTY_FUNCTION__, __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* PROGMSG_H_INCLUDED */

