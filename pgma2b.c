
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "reader.h"
#include "writeFile.h"
#include "errorCodes.h"
#include "exitCodes.h"

/*
    Program to take an ascii file and convert it to the 
    binary format. This program requires 3 arguments,
    the program name, the file to convert, and an output 
    file.
*/
int main (int argc, char **argv) 
{
    // Open files for reading/writing. Declare struct variable and allocate memory
    FILE *input_file = fopen(argv[1], "r"), *output_file = fopen(argv[2], "w");
    fileData *theData = (fileData *) malloc (sizeof(fileData));

    // Validate arguments print specific error message and return error code if invalid
    if (argc == 1) {
        printf("Usage: ./pgma2b inputImage.pgm outputImage.pgm\n");
        return EXIT_NO_ERRORS;
    }
    if (argc != 3)
    {
        printf("ERROR: Bad Argument Count\n");
        return EXIT_WRONG_ARG_COUNT;
    }
    // Check files open correctly, return error message if not 
    if (input_file == NULL || output_file == NULL)
    {
        return errorCodes(EXIT_BAD_FILENAME, argv[1]);
    }
    // Check if memory allocated correctly. Return error code if not
    if (!theData)
    {
        return errorCodes(EXIT_MALLOC_FAIL, argv[1]);
    }
    // Initialise struct variable. Set returnCode equal to return value of reader, run errorCodes if returnCode is not zero
    theData->returnCode = reader (input_file, theData);
    if (theData->format == 'B')
    {
        theData->returnCode = EXIT_BAD_MAGIC;
        return errorCodes (theData->returnCode, argv[1]);
    }
    if (theData->returnCode != 0)
    {
        return errorCodes(theData->returnCode, argv[1]);
    }
    // Set returnCode equal to return value of writeBinary, run errorCodes if returnCode is not zero
    theData->returnCode = writeBinary (output_file, theData);
    if (theData->returnCode != 0)
    {
        return errorCodes(theData->returnCode, argv[2]);
    }
    // Print success message, close the files, and return success code
    printf("CONVERTED");
    fclose(input_file), fclose(output_file);
    return EXIT_NO_ERRORS;
}