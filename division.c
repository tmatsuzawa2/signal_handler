////////////////////////////////////////////////////////////////////////////////
// Main File:        intdate.c, division.c
// This File:        division.c
// Other Files:      sendsig.c, intdate.c
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

//The global variable that count the number of calculations
int count = 0;

/*The first signal handler:
 *print the message and exit(0) when SIGFPE is caught
 */
void catcher_FPE(int signum) {
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: ");
    printf("%d\n", count);
    printf("The program will be terminated.\n");
    exit(0);
}

/*The second signal handler:
 *print the message and exit(0) when SIGINT is caught
 */
void catcher_INT(int signum) {
    printf("\n");
    printf("Total number of operations completed successfully: ");
    printf("%d\n", count);
    printf("The program will be terminated.\n");
    exit(0);
}

//The main function that set signals and process the calculations
int main() {
    //Variables that are used for reading data and calculations
    char buf[100]; 
    int first = 0;
    int second = 0;
    int quotient = 0;
    int remain = 0;

    //set up the two signals (-FPE and -INT)
    struct sigaction sa_FPE;
    struct sigaction sa_INT;
    memset(&sa_FPE, 0, sizeof(sa_FPE));
    memset(&sa_INT, 0, sizeof(sa_INT));
    sa_FPE.sa_handler = catcher_FPE;
    sa_INT.sa_handler = catcher_INT;
    //print the error message and quit if the signal is not successfully set
    if (sigaction(SIGFPE, &sa_FPE, NULL) != 0) {
        printf("Error: Registering SIGFPE\n");
        exit(1);
    }
    if (sigaction(SIGINT, &sa_INT, NULL) != 0) {
        printf("Error: Registering SIGINT\n");
        exit(1);
    }

    //The while loop
    while (1) {
        //read the argument's value and make calculations
        printf("Enter first integer: ");
        fgets(buf, 100, stdin); 
        first = atoi(buf);
        printf("Enter second integer: ");
        fgets(buf, 100, stdin); 
        second = atoi(buf);

        quotient = first / second;
        remain = first % second;

        printf("%d ", first);
        printf("/ %d", second);
        printf(" is %d ", quotient);
        printf("with a remainder of %d\n", remain);
        //if the calculation is made correctly, count adds one
        count++;
    }
    return 0;
}   
