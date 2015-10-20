#ifndef __UTIL_H_
#define __UTIL_H_

#define BUFF_SIZE 512

void *env(char **pairs);
ulong heartbeat(const ulong data);
void parse_env_vars();

#endif
