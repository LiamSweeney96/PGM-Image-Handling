
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "reader.h"
#include "testFiles.h"
#include "exitCodes.h"

/*
    The following function compares two given files by 
    comparing the values stored in two struct variables.
    Prints "IDENTICAL" or "DIFFERENT" based on whether or
    not the files are logically identical.
*/

int testFiles (fileData * theData, FILE * input_file_two) 
{
    // Declare new struct variable to compare to the original struct variable
    fileData * theDataTwo = (fileData *) malloc (sizeof(fileData));
    if (theDataTwo == NULL)
    {
        return theDataTwo->returnCode = EXIT_MALLOC_FAIL;
    }
    // Run pgmComp functions again using second struct variable
    theDataTwo->returnCode = reader (input_file_two, theDataTwo);
    if (theDataTwo->returnCode != 0)
    {
        return theDataTwo->returnCode;
    }
    
    // Declare int arrays of size imageData + nImageBytes to store ratio of maxGray:pixel
    int pixelValueOne[sizeof(theData->imageData + theData->nImageBytes)] = {0};
    int pixelValueTwo[sizeof(theDataTwo->imageData + theDataTwo->nImageBytes)] = {0};

    // Loop to calculate values of the imageData in file one
    for (int i = 0; i < sizeof(theData->height * theData->width); i++) 
    {
        if (theData->imageData[i] != 0) 
        {
            pixelValueOne[i] = theData->maxGray / theData->imageData[i];
        }
        else
        {
            pixelValueOne[i] = 0;
        }
    }
    // Loop to calculate values of the imageData in file Two
    for (int i = 0; i < sizeof(theDataTwo->height * theDataTwo->width); i++) 
    {
        if (theDataTwo->imageData[i] != 0) 
        {
            pixelValueTwo[i] = theDataTwo->maxGray / theDataTwo->imageData[i];
        }
        else
        {
            pixelValueTwo[i] = 0;
        }
        if (pixelValueOne[i] != pixelValueTwo[i])
        {
            printf("DIFFERENT");
            return EXIT_NO_ERRORS;
        }
    }
    
    printf("IDENTICAL");
    return EXIT_NO_ERRORS;
}