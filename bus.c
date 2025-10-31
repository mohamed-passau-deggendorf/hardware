#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/mman.h> 
#include <errno.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>


#define BUF_SIZE 8192

int main(int argc,char*argv[])  {

int fd, nread;
   char *buf;
   void *d;
    int bpos;	
   char d_type;
   int position;
  int pid; 

	 buf = (char*) syscall(SYS_mmap,0,  BUF_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	fd = open("/sys/bus", O_RDONLY | O_DIRECTORY);

	while ((nread = syscall(SYS_getdents64, fd, buf, BUF_SIZE))!=0 )  for (bpos = 0; bpos < nread;bpos +=*((unsigned short *) (d +16) )) 		{


					d =  (buf + bpos);
		d_type = *(buf + bpos +18);
		const char *name = ((char *) (d +19) );
		int size = strlen(name); 
	if(d_type == 4 && strcmp((char *) (d +19),".") !=0  && strcmp((char *) (d +19),"..") !=0  ) {

	printf("\n%s:  ",name);

	int busfd =  openat( openat(fd,name, O_RDONLY | O_DIRECTORY)  , "devices", O_RDONLY | O_DIRECTORY) ;
			
				int bus_nread;
			 char *bus_buf;
			   void *bus_d;
    			int bus_bpos;   
   			char bus_d_type;
   			int bus_position;

	bus_buf = (char*) syscall(SYS_mmap,0,  BUF_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

	while ((bus_nread = syscall(SYS_getdents64, busfd, bus_buf, BUF_SIZE))>0 )   for (bus_bpos = 0;bus_bpos < bus_nread;bus_bpos +=*((unsigned short *) (bus_d +16) )) {


			 bus_d =  (bus_buf + bus_bpos);
                		bus_d_type = *(bus_buf + bus_bpos +18);
                		const char *bus_name = ((char *) (bus_d +19) );
                		int bus_size = strlen(bus_name);

	if( strcmp((char *) (bus_d +19),".") !=0  && strcmp((char *) (bus_d +19),"..") !=0  )
	printf("\n * %s",bus_name);




	}

			}
		


	}

	printf("\n\n");
}
