#########################################################################
# Program Name:   README.txt
# Author1:        Nicholas Kelly
# Red Id1:        814584401
# Author2:        Julian Allotta
# Red Id2:        816825224
# Date Submitted: 5/5/15
# Class:          CompE 560 Spring 2015
# Instructor:     Sweta Sarkar
# Compiler:       gcc
# OS:             OSX-10.9.5
# Description:    README file
# Included Files: noob_saibot.c
#                 scorpion.c
#                 raiden.c
#                 UtilFunctions.c
#                 Utilities.h
#                 Makefile
#                 README.txt
########################################################################

Version 1.0

Instructions:
    To run the server program: make server --> ./server 'server_ip'

    Once the program is running, log onto a different school server to run the
    client1 program: make client1 --> ./client1 'host_ip'

    The client 1 program will then connect to the server and request data
    from the user. After the user inputs the data, the server will then close
    the socket and attempt to connect to client 2 (which will be running server
    code) so the data can be sent to client 2. The user will then be asked which
    server they would like to connect to. In another terminal window, type the
    following command to run the server code on client 2:
    make client2 --> ./client2 'server_ip'
    
    Now back to the original window, the user can either input a host name
    or host ip. The program will validate the host name and if it cant be
    validated, the user will be asked to re-input another host name. They are
    given 3 attempts before the program gracefully shuts down. Upon successful
    validation, the original server sends the data to client 2 (the new server).
    All connections are closed and the program terminates.
