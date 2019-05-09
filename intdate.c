////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c, division.c
// This File:        intdate.c
// Other Files:      sendsig.c, division.c
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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/*Global variables:
 *check: the int that check whether the alarm has ended or not
 *counter: the count
 *t: time_t that is used to record the time
 */
int check = 0;
int counter = 0;
time_t t;

/*The first signal handler:
 *print the pid and time when SIGALRM is caught
 */
void catcher_ALRM (int signum) {
    printf("PID: %d", getpid());
    printf(" | Current Time: %s", ctime(&t));
    check = 1;
}

/*The second signal handler:
 *print the message when SIGUSR1 is caught
 */
void catcher_USR1 (int signum) {
    printf("SIGUSR1 caught!\n");
    counter++;
}

/*The third signal handler:
 *print the message and exit(0) when SIGINT is caught
 */
void catcher_INT (int signum) {
    printf("\n");
    printf("SIGINT received.\n");
    printf("SIGUSR1 was received %d", counter);
    printf(" times. Exiting now.\n");
    exit(0);
}

/*
 * The main function:
 */
int main() {
    //create and initialize the three sigactions
    struct sigaction sa_ALRM;
    struct sigaction sa_USR1;
    struct sigaction sa_INT;
    memset(&sa_ALRM, 0, sizeof(sa_ALRM));
    memset(&sa_USR1, 0, sizeof(sa_USR1));
    memset(&sa_INT, 0, sizeof(sa_INT));
    sa_ALRM.sa_handler = catcher_ALRM;
    sa_USR1.sa_handler = catcher_USR1;
    sa_INT.sa_handler = catcher_INT;

    printf("Pid and time will be printed every 3 seconds.\n");
    printf("Enter ^C to end the program.\n");
    
    //process the first alarm of SIGALRM
    if (sigaction(SIGALRM, &sa_ALRM, NULL) != 0) {
        printf("Error: Registering SIGALRM\n");
        exit(1);
    }
    alarm(3);
    while (check != 1) {
        time(&t);
    }
    check = 0;

    //process the SIGUSR1
    if (sigaction(SIGUSR1, &sa_USR1, NULL) != 0) {
        printf("Error: Registering SIGUSR1\n");
        exit(1);
    }

    //process the SIGINT
    if (sigaction(SIGINT, &sa_INT, NULL) != 0) {
        printf("Error: Registering SIGINT\n");
        exit(1);
    }

    //the while loop
    while (1) {
        alarm(3);
        while (check != 1) {
            time(&t);
        }
        check = 0;
    }
}   
