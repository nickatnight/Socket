/************************************************************************
Program Name: 	Utilities.h
Author1:       	Nicholas Kelly
Red Id1:        814584401
Author2:		Julian Allotta
Red Id2:		816825224
Date Submitted: 5/5/15
Class:        	CompE 560 Spring 2015
Instructor:   	Sweta Sarkar
Compiler:     	gcc
OS:           	OSX-10.9.5
Description:  	Header files
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

#ifndef AAY
#define AYY
typedef struct Pack
{
    int num;
    float f;
    char c;
} Packet;
#endif

void fatal(char *string);

void calculations(Packet *c1p, Packet *c2p);

int32_t swap_int32(int32_t val);

float swap_float(const float f);

int check_char_range(char n);

