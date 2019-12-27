#include <stdio.h>
#include <poll.h>

int main(void){
	struct pollfd pfds[1];  			//will contains sockets file descriptors
										// this in particular will store just one socketd
	pfds[0].fd = 0; 					// Set fd to file descriptors 0, the STDIN
	pfds[0].events = POLLIN;			// Poll for input

	printf("Hit RETURN or wait 2.5 seconds for timeout\n");

	//poll() syscall with timeout
	int num_events = poll(pfds, 1, 2500); // 2.5 second timeout

	if (num_events == 0) {
        printf("Poll timed out!\n");
    }else{

    	// check if POLLIN with bitmask
    	int pollin_happened = pfds[0].revents & POLLIN;

    	if(pollin_happened){
    		printf("File descriptor %d is ready to read\n", pfds[0].fd);
    	}else{
    		printf("Unexpected event occurred: %d\n", pfds[0].revents);
    	}
    }

    return 0;
}