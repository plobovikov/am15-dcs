#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void sigint_handler(int sig)
{
	signal(SIGINT, sigint_handler);
	write(STDOUT_FILENO, "SIGINT received!\n", 17);
}
void sigkill_handler(int sig)
{
	printf("Receive SIGKILL signal = %d", sig);
}

void sigstop_handler(int sig)
{
	printf("Receive SIGSTOP signal = %d", sig);
}
int main()
{
  	if (signal(SIGINT, sigint_handler) == SIG_ERR) printf("Can't catch signal SIGINT\n");
  	if (signal(SIGSTOP, sigstop_handler) == SIG_ERR) printf("Can't catch signal SIGSTOP\n");
	if (signal(SIGKILL, sigkill_handler) == SIG_ERR) printf("Can't catch signal SIGKILL\n");
  	signal(SIGUSR1, SIG_DFL);	//default behavoir
	signal(SIGUSR2, SIG_IGN);	//ignore signal

	while(true)
		pause();
	return 0;
}