#include <stdio.h>
#include <time.h>
#include <rpc/rpc.h>

#include "time.h"

int main(int argc, char **argv) {
	CLIENT* cl;
	cl = clnt_create("localhost", DATE_PROG, DATE_VERS, "udp");
	long *lresult; /* return from bin_date */
	char **sresult; /* return from str_date */
	/* call the procedure bin_date */
	lresult = bin_date_1(NULL, cl);
	printf("time is %ld\n", *lresult);
	/* convert the result to a date string */
	sresult = str_date_1(lresult, cl);
	printf("date is %s", *sresult);
	return 0;
} 