/* progmsg.h: logging
Copyright (C) 2026 TheMaither <themaither@gmail.com> */

#ifndef IMATH_H_INCLUDED
#define IMATH_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/* Sets a name, which is shown with messages.  Ussually it is set to argv[0]. */
void progmsg_setname (const char *);

/* Print a message. */
void progmsg  (const char *fmt, ...);
void vprogmsg (const char *fmt, va_list);

#ifdef __cplusplus
}
#endif

#endif /* IMATH_H_INCLUDED */
