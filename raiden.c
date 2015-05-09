/************************************************************************
Program Name: 	raiden.c
Author1:       	Nicholas Kelly
Red Id1:        814584401
Author2:		Julian Allotta
Red Id2:		816825224
Date Submitted: 5/5/15
Class:        	CompE 560 Spring 2015
Instructor:   	Sweta Sarkar
Compiler:     	gcc
OS:           	OSX-10.9.5
Description:  	Client 2 from socket assignment which acts as the new server
Input Files:  	None
Output Files: 	None
*************************************************************************/


#include "Utilities.h"
#include "UtilFunctions.c"

#define PORT_NUM 5000
#define BUFF_SIZE 4096
#define QUE_SIZE 4


int main(int argc, char *argv[])
{

	// Declare variables
	int socketFd, b, c, l, readSize, on = 1, client_sock;

	struct sockaddr_in server, client;

	char buff[BUFF_SIZE];

	Packet c1Packet, c2Packet;
	Packet *c1PktPtr = &c1Packet, *c2PktPtr = &c2Packet;

	memset(&server, 0, sizeof(server));

	if(argc != 2) fatal("Usage: server server-ip");

	// Establish socket parameters
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port = htons(PORT_NUM);


	// create the socket
	socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socketFd < 0) fatal("Creation of socket failed.");
	puts("Socket successfully created...");

	setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

	// bind the socket ip to the port number to establish a connection
	b = bind(socketFd, (struct sockaddr *)&server, sizeof(server));
	if(b < 0){
		perror("Bind:");
		fatal("Unable to bind socket.");
	}
	puts("Bind successfull...");

	// listen for incoming connections
	l = listen(socketFd, QUE_SIZE);
	if(l < 0) fatal("Unable to listen for connections.");
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	while(1)
	{
		client_sock = accept(socketFd, (struct sockaddr *)&client, (socklen_t*)&c);
		char *str;

		char connectStatus[100];
		strcpy(connectStatus, "Connection accepted from: ");
		strcat(connectStatus, inet_ntoa(client.sin_addr));
		puts(connectStatus);

		puts("Preparing to receive struct from the server...");

		if((readSize = recv(client_sock, &c1Packet, sizeof(struct Pack), 0)) > 0)
		{
			printf("The client wrote: %d, %.2f, %c\n", c1Packet.num, c1Packet.f, c1Packet.c);
			break;
		}
		else
		{
			close(socketFd);
			fatal("Unable to receive message from the server.");
		}
	}

	puts("Closing socket...");
	close(socketFd);
	return 0;
}
