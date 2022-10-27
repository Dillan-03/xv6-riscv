#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
	if (argc != 1){
		//if ( find a way to check if a string is a number of not
		int n;
		n = atoi(argv[1]);
		sleep(n);
	}
	else{
		printf("Error Message!");
		}
	exit(0);
}
