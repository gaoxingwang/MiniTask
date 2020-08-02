#ifndef __PARSE__H
#define __PARSE__H
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <linux/netlink.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>

#define MINITASK_CONF "/etc/minitask.conf"
#define MAX_BUF_LEN 512

typedef struct 
{
	char protocol[10];
	char ip[20];
	int  port;
}conf_t;

int parseFile(conf_t *cf);

int skfd;
struct nlmsghdr *nlh;
struct sockaddr_nl saddr, daddr;
#endif
