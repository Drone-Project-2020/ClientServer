#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "myClient.h"

int main(int argc, char** argv) {

	/* Declaration of the socket */
	SOCKET sock = 0;

	/* Print the input message that will be send to server */
	printf("Please type your message then press enter : ");

	char* buffer = NULL;
	size_t bufferSize = 0;
	
	/* Get user input buffer from standard input */	
	ssize_t nByteRead = getline(&buffer, &bufferSize, stdin);
	
	/* Check if data is present before sending request to server */
	if (nByteRead > 0) {
		/* Socket initialisation and connection to server */
		initializeSocket(&sock);
		
		/* Sending the message to the server and wainting for the answer */
		sendMessageToServer(sock, buffer);
		waitForAnswerFromServer(sock, buffer);
	
		/* Print answser from the server */
	    	printf("Output buffer : %s\n", buffer);
	
		closeSocket(sock);
	}
	return 0;
}

static void initializeSocket(SOCKET* sock) {
	/* Temporary socket for configuration */
	SOCKET tmpSock = socket(AF_INET, SOCK_STREAM, 0);
	
	if (tmpSock == INVALID_SOCKET) {
		perror("socket()");
		exit(errno);
	}
	
	/* This struct contain information about the server */
	SOCKADDR_IN sin = { 
		.sin_addr = {inet_addr(ADDRESS)},
		.sin_port = htons(PORT),
		.sin_family = AF_INET
	};

	if (connect(tmpSock, (SOCKADDR*) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		perror("connect()");
		exit(errno);
	}

	/* Assign our temporary socket to the general socket used by the program */
	*sock = tmpSock;
}

static void sendMessageToServer(const SOCKET sock, const char* buffer) {
	if (send(sock, buffer, strlen(buffer), 0) < 0) {
		perror("send()");
		exit(errno);
	}
}

static void waitForAnswerFromServer(const SOCKET sock, char* buffer) {
	int nbBytes = recv(sock, buffer, BUFFER_SIZE-1, 0);
	if (nbBytes < 0) {
		perror("recv()");
		exit(errno);
	}
}

static void closeSocket(SOCKET sock) {
	close(sock);
}
