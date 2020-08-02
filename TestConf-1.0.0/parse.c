#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"

//extern int skfd;
//extern struct nlmsghdr *nlh;
//extern struct sockaddr_nl saddr, daddr;

char *trim_left_right(char *s)
{
	char *e;
	/* 去除开头的空白 */
	while (isspace(*s)) {
		s++;
	}

	if (strlen(s) == 0) {
		return s;
	}

	/* 结尾空白全部置为\0 */
	e = s + strlen(s) - 1;
	while (isspace(*e) && e > s) {
		*e = '\0';
		e--;
	}

	return s;
}

int parseFile(conf_t *conf)
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
	memset(buf, 0, MAX_BUF_LEN);

	while (fgets(buf, MAX_BUF_LEN, fp) != NULL) {
		/* 去除前后的空白符 */
		para = trim_left_right(buf);

		if (*para == '\0') {
			continue;
		}

		protocol = para;
		ip = para;

		while (!isspace(*ip) && *ip!= '\0') {
			ip++;
		}

		while (isspace(*ip) && *ip != '\0') {
			/*protocol str end*/
			*ip = '\0';
			ip++;
		}

		port = ip;
		while (!isspace(*port) && *port != '\0') {
			port++;
		}
		while (isspace(*port) && *port != '\0') {
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
		strcpy(conf->protocol, protocol);
		strcpy(conf->ip, ip);
		conf->port = atoi(port);

		printf("send to Kernel: %s %s %d\n",conf->protocol, conf->ip, conf->port);

		memcpy(NLMSG_DATA(nlh), conf, sizeof(conf_t));
		int ret = sendto(skfd, nlh, nlh->nlmsg_len, 0, (struct sockaddr *)&daddr, sizeof(struct sockaddr_nl));
		if (!ret) {
			perror("sendto error\n");
			close(skfd);
			exit(-1);
		}
		memset(buf, 0, MAX_BUF_LEN);
		memset(conf, 0, sizeof(conf_t));
	}

	return 1;
}
