#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9999

int main(){
	int sock, client_sock;
	struct sockaddr_in addr, client_addr;
	char buffer[1024];
	int len, addr_len, recv_len;
	
	// make a socket: socket()
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket ");
		return 1;
	}
	
	/*
	 htonl (host network long) = changes byte order of long-type data
	 htons (host to network short) = changes byte order when sending short-type data from host to network
	*/

	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);
	
	// set address(port number) to the new socket: bind()
	if(bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0){
		perror("bind ");
		return 1;
	}

	// wait for the connection request: listen()
	if(listen(sock, 5) < 0){
		perror("listen ");
		return 1;
	}

	addr_len = sizeof(client_addr);
       	
	printf("waiting for client..\n");

	// accept client's connection request: accept()
	// send & receive data: send(), recv()
	// inet_ntoa(): changes 32-bit address into  dotted-decimal notation
	while((client_sock = accept(sock, (struct sockaddr *) &client_addr, &addr_len)) > 0){
		printf("clinet ip : %s\n", inet_ntoa(client_addr.sin_addr));
		
		if((recv_len = recv(client_sock, buffer, 1024, 0)) < 0){
			perror("recv ");
			return 1;
			break;
		}
		buffer[recv_len] = '\0';
		printf("received data: %s\n", buffer);
		send(client_sock, buffer, strlen(buffer), 0);

		close(client_sock);
	}

	// close the connection
	close(sock);
	return 0;
}


