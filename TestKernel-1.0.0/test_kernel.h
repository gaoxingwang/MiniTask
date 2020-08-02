#ifndef __TEST_KERNEL_H
#define __TEST_KERNEL__H

#define MAX_BUF_LEN 512

typedef struct 
{
	char protocol[10];
	char ip[20];
	int  port;
}conf_t;

#endif
