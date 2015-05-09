#########################################################################
# Program Name: 	Makfile
# Author1:       	Nicholas Kelly
# Red Id1:          814584401
# Author2:       	Julian Allotta
# Red Id2: 			816825224
# Date Submitted: 	5/5/15
# Class:        	CompE 560 Spring 2015
# Instructor:   	Sweta Sarkar
# Compiler:     	gcc
# OS:           	OSX-10.9.5
# Description:  	Makefile for socket program
# Input Files:  	User defined
# Output Files: 	None
########################################################################

SERV = server
CL1 = client1
CL2 = client2
CC = gcc
CFLAGS = -lsocket -lnsl
READ = readme

$(SERV):
	$(CC) -o $(SERV) noob_saibot.c $(CFLAGS)
	rm -f *.o

$(CL1):
	$(CC) -o $(CL1) scorpion.c
	rm -f *.o

$(CL2):
	$(CC) -o $(CL2) raiden.c $(CFLAGS)
	rm -f *.o

$(READ):
	cat README.txt

clean_serv:
	rm -f *.o core a.out $(SERV)

clean_c1:
	rm -f *.o core a.out $(CL1)

clean_c2:
	rm -f *.o core a.out $(CL2)

