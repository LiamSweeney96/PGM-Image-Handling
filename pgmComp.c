
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "pgmComp.h"
#include "reader.h"
#include "testFiles.h"
#include "errorCodes.h"
#include "exitCodes.h"
/*
    Program to compare 2 input files. This program will
    take 3 arguments; the program name, the first input
    file, and the second input file.
*/
int main (int argc, char **argv) 
{
    // Open files for reading. Declare struct variable and allocate memory
    FILE *input_file_one = fopen(argv[1], "r"), *input_file_two = fopen(argv[2], "r");
    fileData *theData = (fileData *) malloc (sizeof(fileData));
    // Validate arguments print specific error message and return error code if invalid
    if (argc == 1) {
        printf("Usage: ./pgmComp inputImage.pgm inputImage.pgm\n");
        return EXIT_NO_ERRORS;
    }
    if (argc != 3 && argc != 1)
    {
        printf("ERROR: Bad Argument Count\n");
        return EXIT_WRONG_ARG_COUNT;
    }
    // Check if memory allocated correctly. Return error code if not
    if (!theData)
    {
        return errorCodes(EXIT_MALLOC_FAIL, argv[1]);
    }
    // Check file opened correctly
    if (input_file_one == NULL)
    {
        return errorCodes(EXIT_BAD_FILENAME, argv[1]);
    }
    // Initialise struct variable. Set returnCode equal to return value of reader, run errorCodes if returnCode is not zero
    theData->returnCode = reader (input_file_one, theData);
    if (theData->returnCode != 0)
    {
        return errorCodes(theData->returnCode, argv[1]);
    }
    // Set returnCode equal to return value of testFiles, run errorCodes if returnCode is not zero
    theData->returnCode = testFiles (theData, input_file_two);
    if (theData->returnCode != 0)
    {
        return errorCodes(theData->returnCode, argv[2]);
    }
    // Close the files on completion, return success code
    fclose(input_file_one), fclose(input_file_two);
    return EXIT_NO_ERRORS;
}
