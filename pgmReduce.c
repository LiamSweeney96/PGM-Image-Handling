
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "reader.h"
#include "reduce.h"
#include "errorCodes.h"
#include "exitCodes.h"

/*
    Program to take an input image parameter and reduce its size 
    by a given integer parameter. From this, a new, reduced image 
    will be written to a file given as a parameter.
*/

int main (int argc, char **argv) 
{
    // Open files for reading/writing. Declare struct variable and allocate memory
    FILE *input_file = fopen(argv[1], "r"), *output_file = fopen(argv[3], "w");
    fileData *theData = (fileData *) malloc (sizeof(fileData));
    
    // Validate arguments print specific error message and return error code if invalid
    if (argc == 1) {
        printf("Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm\n");
        return EXIT_NO_ERRORS;
    }
    if (argc != 4)
    {
        printf("ERROR: Bad Argument Count\n");
        return EXIT_WRONG_ARG_COUNT;
    }
    // Check argv[2] is an integer, return error code if not
    if (!atoi(argv[2]))
    {
        printf("ERROR: Miscellaneous (Argument Must Be Integer)");
        return EXIT_MISC;
    }
    // Ensure argv[2] is not a negative integer
    if (argv[2][0] == '-')
    {
        printf("ERROR: Miscellaneous (Argument Must Be Positive Integer)");
        return EXIT_MISC;
    }
    // Check files open correctly, return error message if not 
    if (input_file == NULL|| output_file == NULL)
    {
        return errorCodes (EXIT_BAD_FILENAME, argv[1]);
    }
    // Check if memory allocated correctly. Return error code if not
    if (!theData)
    {
        return errorCodes (EXIT_MALLOC_FAIL, argv[1]);
    }
    // Initialise struct variable. Set returnCode equal to return value of reader, run errorCodes if returnCode is not zero
    theData->returnCode = reader (input_file, theData);
    if (theData->returnCode != 0)
    {
        return errorCodes (theData->returnCode, argv[1]);
    }
    // Assign argv[2] to a long variable to use as the reduction factor
    char * n;
    long number = strtol(argv[2], &n, 10);
    // Set returnCode equal to return value of reduce, run errorCodes if returnCode is not zero
    theData->returnCode = reduce (number, output_file, theData);
    if (theData->returnCode != 0)
    {
        return errorCodes (theData->returnCode, argv[2]);
    }
    // Print success message, close the files, and return success code
    printf("REDUCED");
    fclose(input_file), fclose(output_file);
    
    return EXIT_NO_ERRORS;
}