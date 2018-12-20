/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "time.h"
#include <time.h>

long *
bin_date_1_svc(void *argp, struct svc_req *rqstp)
{
	static long  result;

	result = time((long *)0);
	printf("Send data: %d\n", result);

	return &result;
}

char **
str_date_1_svc(long *argp, struct svc_req *rqstp)
{
	static char * result;

	result = ctime(argp);

	printf("Send data: %s\n", result);

	return &result;
}
