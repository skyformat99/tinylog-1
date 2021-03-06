/*
 * Copyright (C) 2018 Ruilin Peng (Nick) <pymumu@gmail.com>
 */

#ifndef TLOG_H
#define TLOG_H
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

typedef enum {
    TLOG_DBG = 0,
    TLOG_INFO = 1,
    TLOG_WARN = 2,
    TLOG_ERR = 3,
    TLOG_END = 4
} tlog_level;

struct tlog_time {
    int year;
    int mon;
    int mday;
    int hour;
    int min;
    int sec;
    int millisec;
};

struct tlog_info {
    const char *level;
    const char *file;
    const char *func;
    int line;
    struct tlog_time time;
};

/*
Function：Print log   
level: Current log Levels  
format: Log formats  
*/
#define tlog(level, format, ...) tlog_ext(level, __FILE__, __LINE__, __func__, 0, format, ##__VA_ARGS__)

extern int tlog_ext(tlog_level level, const char *file, int line, const char *func, void *userptr, const char *format, ...) __attribute__((format(printf, 6, 7)));

/* set log level */
extern int tlog_setlevel(tlog_level level);

/*
Function：Initialize log module  
logdir: Log Output path.    
logname: Log name.  
maxlogsize: The maximum size of a single log file.    
maxlogcount: Number of archived logs.    
block: Blocked if buffer is not sufficient.    
buffsize: Buffer size  
 */
extern int tlog_init(const char *logdir, const char *logname, int maxlogsize, int maxlogcount, int block, int buffsize);

extern void tlog_exit(void);

/*
customize log output format
steps:
1. define format function, function must be defined as tlog_format_func, use snprintf or vsnprintf format log to buffer
2. call tlog_reg_format_func to register format function.

read _tlog_format for example.
*/
typedef int (*tlog_format_func)(char *buff, int maxlen, struct tlog_info *info, void *userptr, const char *format, va_list ap);
extern int tlog_reg_format_func(tlog_format_func func);

#ifdef __cplusplus
}
#endif /*__cplusplus */
#endif // !TLOG_H
