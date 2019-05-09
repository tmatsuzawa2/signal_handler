In division.c, you are asked to input two numbers, and their division will be calculated, and two more numbers are requestd so on and so forth. 
  When the division by zero is caught, SIGFPE is caught and the program will print message and exit normally.
  Same thing when the user press crtl-c, which SIGINT will be caught.
  
In intdate, a periodical alarm(3) is called every three seconds and print the current PID, current time
  When there is an interrupt from SIGUSR1, program will print a message and keep going.
  When the user press crtl-c, which SIGINT is caught and the program will print message and exit normally.
  
In sendsig.c, the program takes two arguments and send the SIGUSR1. 
