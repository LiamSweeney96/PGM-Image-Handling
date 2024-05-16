#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "pgmEcho.h"
#include "reader.h"
#include "writeFile.h"
#include "errorCodes.h"
#include "exitCodes.h"

/*
    Program to create an identical file in the given format.
    This program takes 3 arguments; the program name, an input
    file, and an output file.
*/
int main (int argc, char **argv) 
{
    // Open files for reading/writing. Declare struct variable and allocate memory
    FILE *input_file = fopen(argv[1], "r"), *output_file = fopen(argv[2], "w");
    fileData *theData = (fileData *) malloc (sizeof(fileData));   
    // Validate arguments print specific error message and return error code if invalid
    if (argc == 1) {
        printf("Usage: ./pgmEcho inputImage.pgm outputImage.pgm\n");
        return EXIT_NO_ERRORS;
    }
    if (argc != 3)
    {
        printf("ERROR: Bad Argument Count\n");
        return EXIT_WRONG_ARG_COUNT;
    }
    // Check file opened correctly, return error message if not
    if (input_file == NULL|| output_file == NULL)
    {
        return errorCodes (EXIT_BAD_FILENAME, argv[1]);
    }
    // Validate malloc, return malloc fail exit code if unsuccessful
    if (!theData)
    {
        return errorCodes (EXIT_MALLOC_FAIL, argv[1]);
    }
    theData->returnCode = 0;
    // Set returnCode equal to the return code of the reader function, run errorCodes function if non-zero value returned
    theData->returnCode = reader (input_file, theData);
    if (theData->returnCode != 0)
    {
        return errorCodes (theData->returnCode, argv[1]);
    }
    // Set returnCode equal to the return code of the writeFile function, run errorCodes function if non-zero value returned
    theData->returnCode = writeFile (output_file, theData);
    if (theData->returnCode != 0)
    {
        return errorCodes (theData->returnCode, argv[1]);
    }
    // Print success message and close the files
    printf("ECHOED");
    fclose(input_file);
    fclose(output_file);

    return EXIT_NO_ERRORS;
}
