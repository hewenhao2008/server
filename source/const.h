#ifndef __CONST_H_
#define __CONST_H_

#define SERVAPP "SERV"
#define VERSION "1.0.1"

#define UNIX_SOCKET "/var/run/serv101.socket"

#define version() do{\
	fprintf(stdout, "%s %s\n", SERVAPP, VERSION); exit(0);\
}while(0)

#endif
