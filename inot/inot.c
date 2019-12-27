#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>

#define EVENT_SIZE ( sizeof (struct inotify_event) )
#define BUF_LEN ( 1024 * ( EVENT_SIZE + 16 ) )

int main(void){

	printf("%s\n", "Inot!");
	printf("%s: %d\n", "Event size", EVENT_SIZE);
	printf("%s: %d\n", "Buffer length", BUF_LEN);


	int length, i = 0;
	int fd;
	int wd;
	char buffer[BUF_LEN];

	// Initialize inotify and error checking
	// it returns -1 on error, or file descriptor if ok
	fd = inotify_init();
	if ( fd < 0 ) {
		perror( "inotify_init" );
	}

	// Adds a watch, in this case, a test folder
	wd = inotify_add_watch(fd, "/home/andrea/inot_test", IN_MODIFY | IN_CREATE | IN_DELETE);
	
	// read from the fd descriptor and error checking
	length = read( fd, buffer, BUF_LEN );
	if(length < 0){
		perror("read");
	}

	// loooooop
	while(i < length) {
		struct inotify_event *event = (struct inotify_event *) &buffer[i];
		if (event->len){
			
			// Chec for IN_CREATE mask, then WHAT was created
			if(event->mask & IN_CREATE){
				if(event->mask & IN_ISDIR){
					printf("The directory %s was created.\n", event->name);
				}else{
					printf("The file %s was created.\n", event->name);
				}
			// Check IN_DELETE bitmask
			}else if(event->mask & IN_DELETE){
				if(event->mask & IN_ISDIR){
					printf("The directory %s was deleted.\n", event->name);
				}else{
					printf("The file %s was deleted.\n", event->name);
				}
			} else if(event->mask & IN_MODIFY){
				if(event->mask & IN_ISDIR){
					printf("The directory %s was modified.\n", event->name);
				}else{
					printf("The file %s was modified.\n", event->name);
				}
			}

		}
		i += EVENT_SIZE + event->len;
	}

	// Remove the watches and close the socket
	(void) inotify_rm_watch(fd, wd);
	(void) close(fd);

	return 0;
}