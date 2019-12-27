#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

static int LINE_MAX = 10000;

void printBanner();
int queryip(void *domain);

struct addrinfo hints, *res, *p;
int status, sockfd, gpn;
char *myhostname;

struct sockaddr peer;
struct sockaddr_in *sin_peer;

char peer_host[1024];
char peer_service[20];

int main(int argc, char *argv[]){
	printBanner();

	status = queryip("hypsosdev.com");

    printf("%s: %d\n", "Status is", status);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    printf("%s: %x\n","The socket descriptor", sockfd);



    connect(sockfd, res->ai_addr, res->ai_addrlen);

    //int getpeername(int sockfd, struct sockaddr *addr, int *addrlen);
    gpn = getpeername(sockfd, &peer, &(LINE_MAX));
    sin_peer = (struct sockaddr_in *)&peer;
    memset(sin_peer->sin_zero, '\0', sizeof sin_peer->sin_zero);

    getnameinfo(&peer, sizeof peer, peer_host, sizeof peer_host, peer_service, sizeof peer_service, 0);
    printf("   host: %s\n", peer_host);    // e.g. "www.example.com"
	printf("service: %s\n", peer_service); // e.g. "http"

    printf("%s: %d\n", "sin_peer", htons(sin_peer->sin_port));
	return 0;
}

void printBanner(){
	printf("\n****** Sock starting ******\n\n");
	//char hostName[LINE_MAX];
	char *hostname = malloc(200 * sizeof(char));
	gethostname(hostname, LINE_MAX - 1);
	printf("%s: %s\n", "You are", hostname);
	free(hostname);
}
int queryip(void *domain){
	printf("Quering: %s\n", domain);

	memset(&hints, 0, sizeof hints); // hints MUST be empty
    hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(domain, "443", &hints, &res)) != 0) {
    	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    	return 2;
    }

    return status;
}