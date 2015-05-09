/************************************************************************
Program Name: 	scorpion.c
Author:       	Nicholas Kelly
Red Id:           	814584401
Author2:		Julian Allotta
Red Id2:		816825224
Date Submitted: 5/5/15
Class:        	CompE 560 Spring 2015
Instructor:   	Sweta Sarkar
Compiler:     	gcc
OS:           	OSX-10.9.5
Description:  	Client 1 from socket assignment
Input Files:  	None
Output Files: 	None
*************************************************************************/


#include "Utilities.h"
#include "UtilFunctions.c"

#define PORT_NUM 5000
#define BUFF_SIZE 4096
#define QUE_SIZE 4


// MAIN
int main(int argc, char *argv[])
{

	// initiate variables
	int socketFd, c, i, s, valid = 0;

	// init packet struct
	Packet p;

	// buffer for messages being sent and receieved
	char message[BUFF_SIZE];

	struct hostent *h;
	struct sockaddr_in client;

	// check to make sure that the user inputed the right amount of arguments
	if(argc != 2) fatal("Usage: client server-ip");

	// create socket using a TCP connection with the address format being internet
	// IPv4, and check to make sure the return code is not less than 0. if it is
	// gracefully exit the program
	socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socketFd < 0) fatal("Unable to create socket.");
	puts("Socket created successfully.");

	// init socket parameters for the client socket.
	h = gethostbyname(argv[1]);
	if(!h) fatal("Unable to resolve host.");
	memcpy(&client.sin_addr.s_addr, h->h_addr, h->h_length); 
	//client.sin_addr.s_addr = inet_addr(argv[1]);
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT_NUM);

    // establish connection with the server using client data struct parameters and check the
    // return code to make sure there were no errors
	c = connect(socketFd , (struct sockaddr *)&client , sizeof(client));
	if(c < 0)
	{
		perror("Connect");
		fatal("Unable to establish connection to server.");
	}

	// receive welcome message from the server to verify a successfull connection and print
	// the message to the user
	recv(socketFd, &message, BUFF_SIZE, 0);
	printf("\nConnecting to server %s at: %s", h->h_name, inet_ntoa(client.sin_addr));
	puts(message);

	

	// loop to validate input from the user
	while(valid == 0)
	{

		// zero out message
		memset(&message, 0, sizeof(message));

		// get input for the struct one at a time and zero out the message buffer after each read
		printf("Enter an int: ");
		fgets(message, BUFF_SIZE - 1, stdin);
		if(sscanf(message, "%d", &p.num) != 1 && !isdigit(p.num))
		{
			valid = 0;
			puts("Invalid input.");
			continue;
		}
		memset(&message, 0, sizeof(message));
		printf("Enter a float: ");
		fgets(message, BUFF_SIZE - 1, stdin);
		if(sscanf(message, "%f", &p.f) != 1)
		{
			valid = 0;
			puts("Invalid input.");
			continue;
		}
		memset(&message, 0, sizeof(message));

		// create a temporary holder for the char since we have to validate it through another function
		char userChar;
		printf("Enter a char: ");
		fgets(message, BUFF_SIZE - 1, stdin);

		// check to make sure the user only entered 1 character
		if(strlen(message) > 2)
		{
			valid = 0;
			puts("Invalid input.");
			continue;
		}
		sscanf(message, "%c", &userChar);

		// make sure the character is in range of a-z and A-Z
		if(check_char_range(userChar) != 1)
		{
			valid = 0;
			puts("Invalid input.");
			continue;
		}

		// assign the character and make valid true to exit the loop
		p.c = userChar;
		valid = 1;
		puts("Constructing packet for delivery...");
	}

	// send the struct (packet) to the server
	s = send(socketFd, &p, sizeof(struct Pack), 0);
	if(s < 0) fatal("Send Failed.");
	puts("Struct successfully sent...");

	puts("Closing socket...");
	// Close socket
	close(socketFd);

  	// The client now is converted into the server and has to create a new socket
  	// to accpect incoming connections from the other client (server)
	return 0;
}


