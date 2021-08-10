
/* (1) Run your counter as a SCHED_BACKGROUND process.Record how long it takes to count*/

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>

int main(){
	long count=1 ;      
	struct timeval start, end ;
	struct rusage usage ;
	struct timeval start_sys, end_sys ;
	struct timeval start_user, end_user ;

	getrusage(RUSAGE_SELF, &usage);
	start_sys = usage.ru_stime ;
	start_user = usage.ru_utime ;	
	printf("Initial Wall-Clock time (test1) : %ld micro-sec.\n",(start.tv_sec*1000000 + 								start.tv_usec)) ; 

	struct sched_param sp = {
		.sched_priority = 1 
	};	
	
	gettimeofday(&start, NULL) ;

	int check = sched_setscheduler(getpid(), 2, &sp) ;  
	long i=1 ;	
	for(i=1; i<=5000000000; i++){
		count+=1 ;	
	}
	gettimeofday(&end, NULL) ;
	
	getrusage(RUSAGE_SELF, &usage) ;
	end_sys = usage.ru_stime ;
	end_user = usage.ru_utime ;	

	printf("System time (test1) : %ld micro-sec.\n",(end_sys.tv_sec*1000000 + end_sys.tv_usec)-      					(start_sys.tv_sec*1000000 + start_sys.tv_usec)) ;

	printf("User time (test1) : %ld micro-sec.\n",(end_user.tv_sec*1000000 + end_user.tv_usec)-      					(start_sys.tv_sec*1000000 + start_user.tv_usec)) ;

	printf("Final Wall-Clock time (test1) : %ld micro-sec.\n",+(end.tv_sec*1000000 + 								end.tv_usec)) ;
	
return 0 ;
}


