#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"

void find(char* one,char* two){

      char buf[512], *p, *e, *b;
      int fd;
      struct stat st;
      struct direct de;
       //Check if file can be opened 
       if ((fd=open(argv,0))<0){
               printf("File not found: %s\n", *argv);
       }

	














	printf("one:%s; two:%s",one, two);
}







int main(int argc,char*argv[]){

	if (argc<3){
		return -1;
		exit(1);
	}
	find(argv[1],argv[2]);









	exit(0);

}
