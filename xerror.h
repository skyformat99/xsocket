#ifndef X_ERROR_H
#define X_ERROR_H

#include <stdarg.h>
#include <syslog.h>

int deamon_proc;

void xerr_doit(int, int, const char *, va_list);
void xerr_ret(const char *fmt, ...);
void xerr_sys(const char *fmt, ...);
void xerr_dump(const char *fmt, ...);
void xerr_msg(const char *fmt, ...);
void xerr_quit(const char *fmt, ...);

#endif
