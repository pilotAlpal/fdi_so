#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

static volatile int contadorINT = 0;
static volatile int contadorTSTP = 0;

void handler(int signal)
{
if(signal == SIGINT)
	contadorINT++;
if(signal == SIGTSTP)
	contadorTSTP++;
}

void main (int args, char **argv)
{
struct sigaction act;
act.sa_handler = handler;
act.sa_flags = 0;
sigaction(SIGTSTP, &act, NULL);
sigaction(SIGINT, &act, NULL);

while (contadorINT+contadorTSTP < 10){};
printf ("SigINT = %i \n", contadorINT);
printf ("SigTSTP = %i \n", contadorTSTP);
}
