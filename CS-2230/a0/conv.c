// CS 2230 | a0 | Richard Schaefer
// Base Conversion Program (C)

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    
    char *ascii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
    char*buf = malloc(32);

    int index = 30;                                 // Index variable
    int decimal = atoi(argv[1]);                    // Integer decimal set to arg 1
    int base = atoi(argv[2]);                       // integer base set to arg 2
    int decimalClone = decimal;                     // Declaring clone that is used for loops
    int rem;                                        // Integer variale used as the remainder
    int mask = (base - 1);                          // Mask variable for Masking
    int shift;                                      // Shift variable initialized for later

    if (argc > 3) {                                 // Validates the ammount of inputs
        printf("Too many arguments supplied.\n");
        exit(1);                                    // Exits the program if not correct
    }

    else if (argc != 3) {                           // Validates the ammount of inputs
        printf("Not enough arguments supplied.\n");
        exit(-1);                                   // Exits the program if not correct
    }

    // Sets the shiift variable, according to the base
    if (base == 2) {
        shift = 1;
    }
    
    if (base == 4) {
        shift = 2;
    }

    if (base == 8) {
        shift = 3;
    }

    if (base == 16) {
        shift = 4;
    }

    if (base == 64) {
        shift = 6;
    }

    // Mask-Shift Algorithm
    if (base == 2 || base == 4 || base == 8 || base == 16 || base == 64) {
        
        while (decimal != 0) {
            
            // Step One
            rem = (decimal&mask);

            // Step Two
            decimal = (decimal >> shift);

            // Step Three
            buf[index] = ascii[rem];

            // Step Four
            index--;
        }

    }

    // Handling other bases
    else if (base > 2 && base < 16) {
        
        while (decimal != 0) {
            
            // Step One
            rem = (decimal%base);
            //rem = (decimal&(base-1));

            // Step Two
            decimal = (decimal/base);

            // Step Three
            buf[index] = ascii[rem];

            // Step Four
            index--;

        }

    }

    else {
    
        printf("INVALID BASE!\n");                  // Verifies the input base
        exit(1);                                    // Exits the program if not correct
    
    }
    
    // Prints the FINAL Annswer
    printf("%s", &buf[index+1]);    
    printf("\n");


    // Returns nothing at the end of the program
    return 0;
}
