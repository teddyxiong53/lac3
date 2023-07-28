#ifndef __MYLOG_H__
#define __MYLOG_H__
#include <stdio.h>
#include <libgen.h>
#include <time.h>
#include <syslog.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OPEN_MYLOG   1 //是否打开mylog。
#define MYLOG_TIMESTAMP 1 //是否加上时间戳
#define MYLOG_TARGET stdout //日志输出到哪里

static inline int mylog_init()
{
    #if 0 //OPEN_MYLOG
    FILE * f = fopen("./device.log", "a+");
    if(!f) {
        printf("open device.log file fail\n");
        return -1;
    }

    #else
    return 0;
    #endif
}
#if OPEN_MYLOG
#if MYLOG_TIMESTAMP
#define myprintf(...) do {\
                        fprintf(MYLOG_TARGET,"[%s][%s][%d]: ", basename((char *)__FILE__), __func__, __LINE__);\
                        fprintf(MYLOG_TARGET,__VA_ARGS__);\
                        fprintf(MYLOG_TARGET,"\n");\
                       }while(0)
#define mylogd(...) do {\
                            char s[32];\
                            time_t tt = time(0);\
		                    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", localtime(&tt));\
                            fprintf(MYLOG_TARGET,"[%s]", s);\
                            fprintf(MYLOG_TARGET,"[DEBUG][%s][%s][%d]: ", basename((char *)__FILE__), __func__, __LINE__);\
                            fprintf(MYLOG_TARGET,__VA_ARGS__);\
                            fprintf(MYLOG_TARGET,"\n");\
                           }while(0)
#define myloge(...) do {\
                            char s[32];\
                            time_t tt = time(0);\
		                    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", localtime(&tt));\
                            fprintf(MYLOG_TARGET,"[%s]", s);\
                            fprintf(MYLOG_TARGET,"[ERROR][%s][%s][%d]: ", basename((char *)__FILE__), __func__, __LINE__);\
                            fprintf(MYLOG_TARGET,__VA_ARGS__);\
                            fprintf(MYLOG_TARGET,"\n");\
                           }while(0)
#define mylogw(...) do {\
                            char s[32];\
                            time_t tt = time(0);\
		                    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", localtime(&tt));\
                            fprintf(MYLOG_TARGET,"[%s]", s);\
                            fprintf(MYLOG_TARGET,"[WARN][%s][%s][%d]: ", basename((char *)__FILE__), __func__, __LINE__);\
                            fprintf(MYLOG_TARGET,__VA_ARGS__);\
                            fprintf(MYLOG_TARGET,"\n");\
                           }while(0)
#else
#define myprintf(...) do {\
                        fprintf(MYLOG_TARGET,"[%s][%s][%d]: ", basename((char*)__FILE__), __func__, __LINE__);\
                        fprintf(MYLOG_TARGET,__VA_ARGS__);\
                        fprintf(MYLOG_TARGET,"\n");\
                       }while(0)
#define mylogd(...) do {\
                            fprintf(MYLOG_TARGET,"[DEBUG][%s][%s][%d]: ", basename((char*)__FILE__), __func__, __LINE__);\
                            fprintf(MYLOG_TARGET,__VA_ARGS__);\
                            fprintf(MYLOG_TARGET,"\n");\
                           }while(0)
#define myloge(...) do {\
                            fprintf(MYLOG_TARGET,"[ERROR][%s][%s][%d]: ", basename((char*)__FILE__), __func__, __LINE__);\
                            fprintf(MYLOG_TARGET,__VA_ARGS__);\
                            fprintf(MYLOG_TARGET,"\n");\
                           }while(0)
#define mylogw(...) do {\
                            fprintf(MYLOG_TARGET,"[WARN][%s][%s][%d]: ", basename((char*)__FILE__), __func__, __LINE__);\
                            fprintf(MYLOG_TARGET,__VA_ARGS__);\
                            fprintf(MYLOG_TARGET,"\n");\
                           }while(0)
#endif
#else
#define mylogd(...) do {\
                            syslog(LOG_INFO,"[DEBUG][%s][%s][%d]: ", basename((char*)__FILE__), __func__, __LINE__ );\
                            syslog(LOG_INFO, __VA_ARGS__); \
                           }while(0)
#define myloge(...) do {\
                            syslog(LOG_INFO,"[ERROR][%s][%s][%d]: ", basename((char *)__FILE__), __func__, __LINE__);\
                            syslog(LOG_INFO, __VA_ARGS__); \
                           }while(0)
//#define mylogd(...)
//#define myloge(...)
#endif


static inline void mydump(const void* p, size_t size) {
    const char  *c = (const char *)p;
    //assert(p);

    fprintf(MYLOG_TARGET,"Dumping %ld bytes from %p:\n", size, p);

    while (size > 0) {
        unsigned i;

        for (i = 0; i < 16; i++) {
            if (i < size)
                fprintf(MYLOG_TARGET,"%02x ", (unsigned char)c[i]);
            else
                fprintf(MYLOG_TARGET,"   ");
        }

        for (i = 0; i < 16; i++) {
            if (i < size)
                fprintf(MYLOG_TARGET,"%c", c[i] >= 32 && c[i] < 127 ? c[i] : '.');
            else
                fprintf(MYLOG_TARGET," ");
        }

        fprintf(MYLOG_TARGET,"\n");

        c += 16;

        if (size <= 16)
            break;

        size -= 16;
    }

}

extern void mysystem(const char *cmd);
#ifdef __cplusplus
}
#endif
#endif
