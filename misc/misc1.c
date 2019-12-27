#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

int main(){

	int status; // status of getaddrinfo syscall
	struct addrinfo hints; // original addringo struct
	struct addrinfo *res, *p;  	// pointer to addrinfo struct that will store getaddrinfo result
								// p will be a copy of res, it will be used for looping

	

	memset(&hints, 0, sizeof hints); //zeroing hints struct
	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

	int sock_i; // socket identifier
	int conn_i; // connect syscall ret

	

	// Target str and max len for ipstr converted from inet_ntop
	char ipstr[INET6_ADDRSTRLEN];


	// getaddrinfo syscall
	// WTF moment: res param is a **res in func prototype. As res is alread a pointer, we pass the address of the pointer: &res = **res
	status = getaddrinfo("hypsosdev.com", "80", &hints, &res); 

	// getaddrinfo syscall error handling
	if(status  != 0){
		fprintf(stderr, "get addrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}
	printf("%s\n", "All good.");

	

	// loop! through the linked list
	for(p = res; p != NULL; p = p->ai_next){

		char *ipver; // It will contain the ip family presentation string
		struct in_addr ipv4;

		// check if ipv4
		if(p->ai_family == AF_INET){
			struct sockaddr_in *ip4ptr =  (struct sockaddr_in *)p->ai_addr; // Cast addrinfo sockaddr to sockaddr_in
			ipv4 = ip4ptr->sin_addr; // get the in_addr struct from the sockaddr_in
			ipver = "IPV4";
		}

		// convert the IP to a string and print it with ntop (Network TO Presentation)
		// ipstr and INET6... are the target string and max size of target string
		inet_ntop(p->ai_family, &(ipv4), ipstr, INET6_ADDRSTRLEN);

		printf("%s: %s\n", "Ip address is", ipstr);

		// Open a socket to the remote host
		sock_i = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		
		conn_i = connect(sock_i, p->ai_addr, p->ai_addrlen);
		printf("%s: %d\n", "Conn i return",conn_i);

		
		socklen_t len;
		struct sockaddr_storage addr;
		char ipstr[INET6_ADDRSTRLEN];
		int port;

		len = sizeof addr;
		getpeername(sock_i, (struct sockaddr*)&addr, &len);

		struct sockaddr_in *s = (struct sockaddr_in *)&addr;
		struct addrinfo *ai_remote = (struct addrinfo *)&addr;

		port = ntohs(s->sin_port);
		inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
		printf("%s: %d\n", "Remote port is", port);

		
	}

	freeaddrinfo(res); // free the linked list

	return 0;
}