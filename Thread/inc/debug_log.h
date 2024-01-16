#ifndef _DEBUG_LOG_H_
#define _DEBUG_LOG_H_

#ifdef DEBUG
#define COLOR_BLACK "\033[1;30m"
#define COLOR_RED "\033[1;31m"
#define COLOR_GREEN "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_PURPLE "\033[1;35m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_WHITE "\033[1;37m"


#define DEBUG_LOG(fmt, args...) do\
                            {\
                                /*printf("\033[1;32m<<File:%s  Line:%d  Function:%s>>\033[0m ", __FILE__, __LINE__, __FUNCTION__);*/\
                                printf(fmt, ##args);\
                                printf("\033[0m");\
                            }while(0);\
                            printf("\n")
#else
#define DEBUG_LOG(fmt, args...)
#endif

#endif
