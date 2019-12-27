#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN		( 1024 * ( EVENT_SIZE + 16))

int main(void){

	int length, i = 0;
	int fd;
	int wd;
	char buffer[120];
	printf("%d\n", BUF_LEN);

	fd = inotify_init();
	if ( fd < 0 ) {
		perror( "inotify_init" );
	}

	
	
	(void)close(fd);


	return 0;
}