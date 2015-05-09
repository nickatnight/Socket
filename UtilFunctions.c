/************************************************************************
Program Name: 	UtilFunctions.c
Author:       	Nicholas Kelly
Red Id:         814584401
Author2:		Julian Allotta
Red Id2:		816825224
Date Submitted: 5/5/15
Class:        	CompE 560 Spring 2015
Instructor:   	Sweta Sarkar
Compiler:     	gcc
OS:           	OSX-10.9.5
Description:  	Utility functions
Input Files:  	None
Output Files: 	None
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>


/*
 * Function: fatal
 * ---------------
 *  takes a string as input and returns it. Once returning the string
 *  the program gracefully exits.
 *
 *  string: desired message
 *
 *  returns: nothing
 */
void fatal(char *string)
{
	printf("%s\n", string);
	exit(1);
}

/*
 * Function: calculations
 * ----------------------
 *  takes packet one, performs the neccessary calculations, and then stores
 *  the new values in packet 2. Passing the values by reference to the values
 *  can be updated in the calling function. Both arguments are packet structs
 *
 *  c1p: packet 1 from client 1
 *  c2p: packet 2 that we are sending to the client 2
 *
 *  returns: nothing
 */
void calculations(Packet *c1p, Packet *c2p)
{

	// if the character is a z or Z, loop back to the beginning of the alphabet
	if(((c1p->c) == 'Z') || ((c1p->c) == 'z'))
		c2p->c = c1p->c - 25;
	else
		c2p->c = c1p->c + 1;

	c2p->num = c1p->num * 2;
	c2p->f = c1p->f + 1;
}

/*
 * Function: swap_int32
 * ----------------------
 *  Reverses the byte order of the int since the servers run different compilers on them
 *  (big endian vs little endian)
 *
 *  val: integer value from the struct to swap the byte order of
 *
 *  returns: new integer in reverse order
 */
int32_t swap_int32(int32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | ((val >> 16) & 0xFFFF);
}

/*
 * Function: swap_float
 * ----------------------
 *  Reverses the byte order of the float since the servers run different compilers on them
 *  (big endian vs little endian)
 *
 *  val: float value from the struct to swap the byte order of
 *
 *  returns: new float in reverse order
 */
float swap_float(const float f)
{
	float retValue;
	char *fConvert = (char*) &f;
	char *returnF = (char*) &retValue;

	returnF[0] = fConvert[3];
	returnF[1] = fConvert[2];
	returnF[2] = fConvert[1];
	returnF[3] = fConvert[0];

	return retValue;
}

/*
 * Function: check_char_range
 * ----------------------
 *  Checks the range of the character to make sure it is valid
 *
 *  n: the character we are checking
 *
 *  returns: true if the the character is valid, and false otherwise
 */
int check_char_range(char n)
{
	// ASCII ranges for valid chars
	if((n >= 65 && n <= 90) || (n >= 97 && n <= 122)) return 1;
	else return 0;
}

