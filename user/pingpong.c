#include "kernel/types.h"
#include "user/user.h"
int main(int argc, char *argv[]){
	//We ned to create two pipes that will have two different direction
	//i.e one pipe will read-----write
	//i.e other pipe will write----read
	
	//Create Pipe
	int rw[2];
	int wr[2];

	pipe(rw);
        pipe(wr);

	//Create a fork
	int id = fork();

	//Create array thaat holds the string;
	char array[5];

	if (id == 0){
		//Child Process
		int pid_w = getpid(); //retrieve pid process number

		//Get rw[0] and write it to wr[1]
		read(rw[0], array, 4);

		wait(0);

		write(wr[1], "pong", 4);// data variable to be sent to the main process, write to pipe
		printf("%d: received %s\n",pid_w,array);

		wait(0);
		exit(0);
	}
	else{
		//Main Process (parent process)
		
		int pid_w = getpid(); //retrieve pid process number

                //Get rw[1] and write it to wr[1]

                write(rw[1], "ping", 4);// data variable to be sent to the main process, write to pipe
		wait(0);	                
		read(wr[0], array, 4);
		printf("%d: received %s\n",pid_w, array);
		wait(0);	
                exit(0);
	
	}
	exit(0);

}
