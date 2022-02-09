#include <stdio.h>
#include <sys/time.h>
#include <signal.h>

void timer_handler(int);

int main() {
	
	struct sigaction sa;
	struct itimerval timer;
	
	//Install timer for signal handler
	memset(&sa,0,sizeof(sa));
	sa.sa_handler = &timer_handler;
	sigaction(SIGVTALRM, &sa, NULL);
	
	//Configure timer
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 500000;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 500000;
	
	//Start timer
	setitimer(ITIMER_VIRTUAL, &timer, NULL);
	
	//Use while loop to look for signals
	while(1) {
		int interrupt;
		sigaction(interrupt, &sa, NULL);
		if(interrupt == 14) {
			timer_handler(interrupt);
		}
	}
}

void timer_handler(int signum) {
	static int count = 0;
	struct timeval ts;
	
	count+= 1;
	gettimeofday(&ts, NULL);
	printf("%d.%06d: timer expired %d times \n", ts.tv_sec, ts.tv_usec, count);
}
	
