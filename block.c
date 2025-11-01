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
#define READING_SIZE 2048
#define BUFFER_SIZE 8192


int main(int argc,char*argv[])  {


int fd, nread;
   char *buf;
   void *d;
    int bpos;	
   char d_type;
   int position;
  int pid; 

	 buf = (char*) syscall(SYS_mmap,0,  BUF_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

 fd = open("/sys/block", O_RDONLY | O_DIRECTORY);
	while ((nread = syscall(SYS_getdents64, fd, buf, BUF_SIZE))!=0 )  for (bpos = 0; bpos < nread;bpos +=*((unsigned short *) (d +16) ))
	{

				d =  (buf + bpos);
		d_type = *(buf + bpos +18);
		const char *name = ((char *) (d +19) );
		int size = strlen(name); 
		

	if((argc< 2 || strcmp(name,argv[1]) == 0) && strcmp((char *) (d +19),".") !=0  && strcmp((char *) (d +19),"..") !=0 ) {
	printf("\n\n%s\n",name);

	int blkfd =  openat(fd,name, O_RDONLY | O_DIRECTORY);
	int statfd =  openat(blkfd,"stat", O_RDONLY );
	int sizefd =  openat(blkfd,"size", O_RDONLY );
	char labels[16][24] = {"read I/Os","read merges","read sectors","read ticks","write I/Os","write merges","write sector","write ticks","in_flight","io_ticks","time_in_queue","discard I/Os","discard merges","discard sector","discard ticks"};


	int read_byte, offset=0 , k;
	bool label_displayed=false;
	int label_index=0;
	char buffer[BUFFER_SIZE];

	while( (read_byte = read(statfd,buffer + offset,
                         (BUFFER_SIZE-offset)  >= READING_SIZE ? READING_SIZE :  (BUFFER_SIZE-offset)   )) >0 ) 
    for(k=offset;k<read_byte + offset;k++) {
			
			if(!label_displayed)if(buffer[k]<='9' && buffer[k]>='0')printf("%s : %c",labels[label_index++],buffer[k]) && (label_displayed=true);else;else
			if(buffer[k]<='9' && buffer[k]>='0') printf("%c",buffer[k]);else printf("\n") && (label_displayed=false);



				}

	read_byte=read(sizefd,buffer,1024);
	buffer[read_byte]='\0';
	printf("Size : %s\n",buffer);







	}


	}


}
