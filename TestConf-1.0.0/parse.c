#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"

char *trim_left_right(char *s)
{
	char *e;
	if (strlen(s) == 0) {
		return s;
	}
	/* 去除开头的空白 */
	while (isspace(*s)) s++;

	/* 结尾空白全部置为\0 */
	e = s + strlen(s) - 1;
	while (isspace(*e) && e > s) {
		*e = '\0';
		e--;
	}

	return s;
}

int isdelimiter(char c)
{
	if (isspace(c) || c == '=' || c == ':' ) {
		return 1;
	} else {
		return 0;
	}
}


int parseFile(conf_t *cf)
{
	FILE *fp = NULL;
	char *protocol, *ip, *port;
	char *para;
	char buf[MAX_BUF_LEN];

	fp = fopen(MINITASK_CONF,"r+");
	if (fp == NULL) {
		printf("open %s fail!\n", MINITASK_CONF);
		return -1;
	}


	while (fgets(buf, MAX_BUF_LEN, fp) != NULL) {
		/* 去除前后的空白符 */
		para = trim_left_right(buf);

		if (*para == '\0') {
			memset(buf, 0, MAX_BUF_LEN);
			continue;
		}

		protocol = para;
		ip = para;
		
		while (!isdelimiter(*ip) && *ip!= '\0') {
			ip++;
		}

		while (isdelimiter(*ip) && *ip != '\0') {
			/*protocol str end*/
			*ip = '\0';
			ip++;
		}

		port = ip;
		while (!isdelimiter(*port) && *port != '\0') {
			port++;
		}
		while (isdelimiter(*port) && *port != '\0') {
			/*ip str end*/
			*port = '\0';
			port++;
		}

		if (*port == '\0') {
			printf("ERROR: Invalid parameter");
			memset(buf, 0, MAX_BUF_LEN);
			continue;
		}
		
		if (strcmp(protocol, "Protocol") == 0) {
			continue;
		}
		strcpy(cf->protocol, protocol);
		strcpy(cf->ip, ip);
		cf->port = atoi(port);

		memset(buf, 0, MAX_BUF_LEN);
	}

	return 1;
}
