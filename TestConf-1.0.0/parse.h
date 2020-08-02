#ifndef __PARSE__H
#define __PARSE__H

#define MINITASK_CONF "/etc/minitask.conf"
#define MAX_BUF_LEN 512

typedef struct 
{
	char protocol[10];
	char ip[20];
	int  port;
}conf_t;

int parseFile(conf_t *cf);
#endif
