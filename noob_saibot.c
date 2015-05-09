/************************************************************************
Program Name: 	noob_saibot.c
Author1:       	Nicholas Kelly
Red Id1:        814584401
Author2:		Julian Allotta
Red Id2:		816825224	
Date Submitted: 5/5/15
Class:        	CompE 560 Spring 2015
Instructor:   	Sweta Sarkar
Compiler:     	gcc
OS:           	OSX-10.9.5
Description:  	Server/client for Socket Assignment
Input Files:  	None
Output Files: 	None
*************************************************************************/


#include "Utilities.h"
#include "UtilFunctions.c"


// Define statements for the socket parameters
#define PORT_NUM 5000
#define BUFF_SIZE 4096
#define QUE_SIZE 4
#define ATTEMPTS 3



// MAIN
int main(int argc, char *argv[])
{

	// Declare variables
	int socketFd, b, l, readSize, c, client_sock, clientCount = 0, on = 1, s;

  	// name of the servers we will be connecting to. Used when a client connects,
  	// they are greeted with the proper header (see if clause)
	char *jasonServer = "130.191.166.3";
	char *rohanServer = "130.191.3.100";
	char *voltaServer = "130.191.166.4";

	// Client Data Packet(struct) and pointers to their addresses. We include the
  	// pointers so when we pass the structs to the 'calculations' function, we can
  	// pass the parameters by reference.
	Packet c1Packet, c2Packet;
	Packet *c1PktPtr = &c1Packet, *c2PktPtr = &c2Packet;

  	// creating the socket data structures for the server and the client...here we
  	// will be saving the parameters of the socket
  	struct sockaddr_in server, client;

  	// char string to hold the ASCII art for each of the servers we will
  	// connecting too, along with a message buffer to hold the strings that are
  	// being sent and received
	char *message1, *message2, *message3;
	char message[BUFF_SIZE];

  	// zero out the data structure for safe keeping
	memset(&server, 0, sizeof(server));

  	// check the input and make sure there is a sufficient amount
	if(argc != 2) fatal("Usage: server server-ip");

	// Establish socket parameters
	server.sin_family = AF_INET; 					// IPv4 addresses
	server.sin_addr.s_addr = inet_addr(argv[1]);		// allow any addresses to connect
	server.sin_port = htons(PORT_NUM);				// establish common port for the socket

	// create the socket using IPv4 with a TCP connection
	socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socketFd < 0) fatal("Creation of socket failed.");
	puts("Socket successfully created...");

	// allow port ot reused and establish multiple connections
	setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

	// bind the socket
	b = bind(socketFd, (struct sockaddr *)&server, sizeof(server));
	if(b < 0) fatal("Unable to bind socket.");
	puts("Bind successful...");

	// listen for connections
	l = listen(socketFd, QUE_SIZE);
	if(l < 0) fatal("Unable to listen for connections.");
	puts("\nWaiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    // Constantly accept incoming connections
    while(1)
    {

    	// wait for a connection from an incoming client
    	client_sock = accept(socketFd, (struct sockaddr *)&client, (socklen_t*)&c);

    	// get the string of the servers address
    	char *str;
    	str = inet_ntoa(server.sin_addr);

    	// Mesages to display to client as soon as they connect
    	char *jason = "\n     ____.\n    |    |____    __________   ____\n    |    \\__  \\  /  ___/  _ \\ /    \\\n/\\__|    |/ __ \\_\\___ (  <_> )   |  \\\n\\________(____  /____  >____/|___|  /\n              \\/     \\/           \\/ \n-----------------------------------\n";
    	char *rohan = "\n__________       .__\n\\______   \\ ____ |  |__ _____    ____\n |       _//  _ \\|  |  \\__  \\  /    \\\n |    |   (  <_> )   Y  \\/ __ \\|   |  \\\n |____|_  /\\____/|___|  (____  /___|  /\n        \\/            \\/     \\/     \\/\n--------------------------------------\n";
    	char *volta = "\n____   ____    .__   __\n\\   \\ /   /___ |  |_/  |______\n \\   Y   /  _ \\|  |\\   __\\__  \\\n  \\     (  <_> )  |_|  |  / __ \\_\n   \\___/ \\____/|____/__| (____  /\n                              \\/\n------------------------------\n";
    	message1 = "Welcome to Tobias!\n------------------\n\nThis server will convert your input and send to a different client.\n";

    	// depending on which ip address the client connects from, the server will send a welcome header in some very stunnin ASCII art
    	if(strcmp(jasonServer, str) == 0) write(client_sock, jason, strlen(jason));
    	else if(strcmp(rohanServer, str) == 0) write(client_sock, rohan, strlen(rohan));
    	else if(strcmp(voltaServer, str) == 0) write(client_sock, volta, strlen(volta));
    	else write(client_sock, message1,strlen(message1));

	    // Display status of connection
	    char fin[100];
	    strcpy(fin, "Connection accepted from: ");
	    strcat(fin, inet_ntoa(client.sin_addr));
	    puts(fin);

	    // Receive the packet from the client and display the values
		if((readSize = recv(client_sock, &c1Packet, sizeof(struct Pack),0)) > 0)
		{
			// checks to see if the client or ther server is running on volta. Voltas compiler differs from the Rohan 
			// and Jason servers so when sending data, the endianess's will skew the data
			if(strcmp(voltaServer, inet_ntoa(client.sin_addr)) == 0 || strcmp(voltaServer, inet_ntoa(server.sin_addr)) == 0)
			{
				// swap the bytes for the int and the float
				c1Packet.num = swap_int32(c1Packet.num);
				c1Packet.f = swap_float(c1Packet.f);
			}

			// print the values that the client wrote
			puts("The ORIGINAL values that the client wrote are:");
			printf("\t(before) int: %d, float: %.2f, char: %c\n", c1Packet.num, c1Packet.f,c1Packet.c);
		}
		else
		{
			// close the socket and end the program if there was an error reading the data
			close(socketFd);
			fatal("Unable to receive data.");
		}

		// Perform calculation per assignment instructions, the functions takes the pointer that are pointed
		// to the structs that client 1 sent
		puts("\nPerforming calculations...");
		calculations(c1PktPtr, c2PktPtr);

		// Display the new values
		puts("\nThe NEW values are as follows:");
		printf("\t(after) int: %d, float: %.2f, char: %c\n", c2Packet.num, c2Packet.f, c2Packet.c);

		puts("\nClosing connection with client 1");
		close(socketFd);
		break;
    }

    // create new socket for the new client/server connection
    puts("Creating a new socket with client 2....");

	//struct hostent *h;
	// zero out the client data struct to start a new socket connection
	memset(&client, 0 , sizeof(client));

	// create a new TCP socket connection using IPv4
	socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socketFd < 0) fatal("Unable to create socket.");
	puts("Socket created successfully...");


	// ip address that the user wishes to connect to along with a host data structure to hold
	// information about the host
	char clientip[BUFF_SIZE];
	struct hostent *h;

	// zero out message buffer
	memset(&message, 0, sizeof(message));

	// counter for while loop and number of attempts the user tries to resolve an invalid host
	int t = 0, amoutOfAttempts = 0;
	while(t == 0)
	{
		// loop back here if the host name can not be resolved
		LOOPER:
		// prompt for the user
		printf("Which server would you like to connect to: ");
		fgets(message, BUFF_SIZE, stdin);
		if(sscanf(message, "%s", clientip) == 1) t = 1;
		else
		{
			t = 0;
			
		}
	}

	// get the hostname of the client ip and if it cant be resolved, loop back
	// and prompt user for new hostname
	h = gethostbyname(clientip);
	if(!h)
	{
		puts("Unable to resolve host.");
		amoutOfAttempts++;
		if(amoutOfAttempts > ATTEMPTS)
		{
			close(socketFd);
			fatal("Too many attempts used. Shutting down program.");
		}
			printf("Number of attempts left: %d\n", ATTEMPTS - amoutOfAttempts);
		goto LOOPER;
	}
	
	// create parameters for the client socket that we will be connecting to client 2 (server)
	//client.sin_addr.s_addr = inet_addr(clientip);
	memcpy(&client.sin_addr.s_addr, h->h_addr, h->h_length);
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT_NUM);

    // connect to the server with the client socket parameters and check to make sure there was no error
	c = connect(socketFd , (struct sockaddr *)&client , sizeof(client));
	if(c < 0)
	{
		perror("Connect");
		fatal("Unable to establish connection to server.");
	}

	// prompt the user that we have succefully connected
	printf("Connected to %s at: %s\n", h->h_name, inet_ntoa(client.sin_addr));

	// send the second structure packet to the server
	s = send(socketFd, &c2Packet, sizeof(struct Pack), 0);
	if(s < 0) fatal("Send Failed.");
  	puts("Successfully sent struct to the client.");

	// Close socket
	puts("Closing socket...");
	close(socketFd);

	return 0;
}


