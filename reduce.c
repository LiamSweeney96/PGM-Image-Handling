
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "reduce.h"
#include "writeFile.h"
#include "exitCodes.h"

/*
    Function to calculate the number of values required, and
    grab the required values from the input image to store in 
    a new struct variable
*/

int reduce (int n, FILE * output_file, fileData * theData)
{
    // Declare new struct variable to hold every nth pixel of theData variable
    fileData * theDataTwo = (fileData *) malloc (sizeof(fileData));
    int j = 0, x = 0, y = 0;
    // Calculate the width & height required for the reduced image
    theDataTwo->width = theData->width / n + 1;
    theDataTwo->height = theData->height / n + 1;
    // Set the format & maxGray values to be that of the input file
    theDataTwo->format = theData->format;
    theDataTwo->maxGray = theData->maxGray;
    
    // Calculate the number of bytes required
    int byteSize = ((theData->width / n) * (theData->height / n));
    
    unsigned char byteString[byteSize];

    theDataTwo->imageData = byteString; 

    // Loop to store the nth value from original struct variable in imageData of new struct variable
    for (int i = 0; i < theData->width * theData->height; i++)
    {
        x = i % theData->width;
        y = i / theData->width;

        if (x % n == 0)
        {
            if (y % n == 0)
            {
                theDataTwo->imageData[j] = theData->imageData[i];
                j++;
            }
        } 
    }
    
    theDataTwo->nImageBytes = j;

    return theData->returnCode = writeFile (output_file, theDataTwo);
}