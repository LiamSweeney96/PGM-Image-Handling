#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "writeFile.h"
#include "exitCodes.h"

/*
    Function to check the format of the input file, and 
    run the relevant function to output the data in either
    binary or ascii
*/

int writeFile (FILE *output_file, fileData *theData) {

    // Check the format of the input file
    if (theData->format == 'A')
    {
        theData->returnCode = writeAscii (output_file, theData);
    }
    if (theData->format == 'B')
    {
        theData->returnCode = writeBinary (output_file, theData);
    }
    return theData->returnCode;
}

// Function to write to the output file in binary format
int writeBinary (FILE *output_file, fileData *theData)
{
    // Count amount of bytes written to the file to ensure it is output correctly
    size_t nBytesWritten = fprintf(output_file, "P5\n%d %d\n%d\n", theData->width, theData->height, theData->maxGray);
    // Loop to write the image data to the output file in binary
    for (int i = 0; i < theData->nImageBytes; i++)
	{
        fwrite(&theData->imageData[i], sizeof(unsigned char), 1, output_file);
    }
    // Check if the output was successful, return error code if not
    if (nBytesWritten == 0 || output_file == NULL)
    { 
        return EXIT_OUTPUT_FAIL;
    } 
    return EXIT_NO_ERRORS;
}

// Function to write to the output file in ascii format
int writeAscii (FILE *output_file, fileData *theData)
{
    // Count amount of bytes written to the file to ensure it is output correctly
    size_t nBytesWritten = fprintf(output_file, "P2\n%d %d\n%d\n", theData->width, theData->height, theData->maxGray);
    if (nBytesWritten == 0)
    {   
        return EXIT_OUTPUT_FAIL;
    } 
    // Loop to write the image data to the output file in ascii
    for (unsigned char *nextGrayValue = theData->imageData; nextGrayValue < theData->imageData + theData->nImageBytes; nextGrayValue++)
    {   
        // get next char's column
        int nextCol = (nextGrayValue - theData->imageData + 1) % theData->width;
        // Write the entry and whitespace
        nBytesWritten = fprintf(output_file, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );
    } 
    // Check if the output was successful, return error code if not
    if (nBytesWritten == 0 || output_file == NULL)
    {   
        return EXIT_OUTPUT_FAIL;
    } 
    return EXIT_NO_ERRORS;
}