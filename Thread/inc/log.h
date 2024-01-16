#ifndef _LOG_H_
#define _LOG_H_

// system problem log
int system_log_write(const char *problem);
// system problem log path
int system_log_path(const char *problem,const char *path);
//log operation revise 
int operation_revise(const char *filename, const char *modify, const char *state);

#endif 
