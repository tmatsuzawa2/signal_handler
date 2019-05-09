////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c, division.c
// This File:        sendsig.c
// Other Files:      intdate.c, division.c
// Semester:         CS 354 SPRING 2019
//           
// Author:           Takashi Matsuzawa
// Email:            tmatsuzawa@wisc.edu
// CS Login:         takashi
//           
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//           
// Persons:          N/A
//           
// Online sources:   N/A
////////////////////////////////////////////////////////////////////////////////

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * The main function that send the signals
 */
int main(int argc, char *argv[]) {  
    //error message if wrong argument  
    if (argc != 3) {
        printf("Usage: <signal type> <pid>\n");
    }

    //store recognize the value of arguments, then send the signals accordingly
    char *type = argv[1]; 
    int pid = atoi(argv[2]);
    if (strcmp(type,"-i") == 0) {
        kill(pid, SIGINT);
    }
    else if (strcmp(type,"-u") == 0) {
        kill(pid, SIGUSR1);
    }
    else {
        printf("Usage: <signal type> <pid>\n");
    }
}