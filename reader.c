#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "reader.h"
#include "errorCodes.h"
#include "exitCodes.h"

/*  
  Reader function which runs the specified function to retrieve
  the data from the file. If anything fails, an error code is 
  returned.
*/
int reader (FILE *input_file, fileData *theData)
{
	theData->returnCode = getMagic (input_file, theData);
	if (theData->returnCode != 0)
	{
		return theData->returnCode;
	} 
	theData->returnCode = commentRead (input_file, theData); 
	if (theData->returnCode != 0)
	{
		return theData->returnCode;
	} 
	theData->returnCode = getDimensions (input_file, theData);
	if (theData->returnCode != 0)
	{
		return theData->returnCode;
	} 
	if (theData->format == 'A')
	{
		theData->returnCode = getAsciiData (input_file, theData);
	}
	if (theData->format == 'B')
	{
		theData->returnCode = getBinaryData (input_file, theData);
	}
	if (theData->returnCode != 0)
	{
		return theData->returnCode;
	} 
	// Return 0 exit code on success
	return EXIT_NO_ERRORS;
}

int getMagic (FILE *input_file, fileData *theData)
{
	// Declare and initialise magic_number array of size 2, read in values
	unsigned char magic_number[2] = {getc(input_file), getc(input_file)};
	// Check if character is read in correctly
	if (magic_number[0] == (char) 0 || magic_number[1] == (char) 0) 
	{
	return EXIT_BAD_MAGIC;
	}    
	// Check whether format is RAW or ASCII
	if (magic_number[0] == 'P' && magic_number[1] == '2')
	{
		theData->format = 'A';
	}
	if (magic_number[0] == 'P' && magic_number[1] == '5') 
	{
		theData->format = 'B';
	}
	// Validate the magic number, return error code if unsuccessful
	if (magic_number[0] != 'P')
	{
	return EXIT_BAD_MAGIC;
	}
	if (magic_number[1] != '2' && magic_number[1] != '5')
	{
	return EXIT_BAD_MAGIC;
	}
	// Return 0 exit code on success
	return EXIT_NO_ERRORS;
  
}

int commentRead (FILE *input_file, fileData *theData)
{
	// Scan whitespace if any present
	fscanf(input_file, " ");
	// Check for a comment line, allocate buffer if present
	char nextChar = fgetc(input_file);
	if (nextChar == '#')
	{
		// Allocate memory for the comment line, and check it has allocated correctly
		theData->commentLine = (char *) malloc (MAX_COMMENT_LINE_LENGTH);
		if (!theData->commentLine)
		{
			return EXIT_MALLOC_FAIL;
		}	
		// Read in the comment line. Allow more characters to be read in than the max comment line length to check if it is too long
		fgets(theData->commentLine, 130, input_file);
		// Return non-zero error code if commentString is NULL and free the memory
		if (strlen(theData->commentLine) > MAX_COMMENT_LINE_LENGTH)
		{
			free(theData->commentLine);
			return EXIT_BAD_COMMENT_LINE;
		}
	}
	else
	{
		ungetc(nextChar, input_file);   
		theData->commentLine = NULL;
		free(theData->commentLine);
	}
	// Return 0 exit code on success
	return EXIT_NO_ERRORS;
}

int getDimensions (FILE *input_file, fileData *theData) 
{
	// Read in the width, height, and maxGray values
	theData->scanCount = fscanf(input_file, " %u %u %u", &(theData->width), &(theData->height), &(theData->maxGray)); 
	// Check dimensions are valid, close file and print error message if not
	if ((theData->scanCount != 3) || (theData->width < MIN_IMAGE_DIMENSION) || (theData->width > MAX_IMAGE_DIMENSION) ||
	(theData->height < MIN_IMAGE_DIMENSION) || (theData->height > MAX_IMAGE_DIMENSION))
	{
		return EXIT_BAD_DIMENSIONS;
	}
	// Check the value of maxGray does not equal 255, close file and return error code
	if (theData->maxGray != 255) 
	{
		return EXIT_BAD_MAX_GRAY;
	}
	// Return 0 exit code on success
	return EXIT_NO_ERRORS;
}

int getAsciiData (FILE *input_file, fileData *theData) 
{
	// Calculate the size of the image bytes required
	theData->nImageBytes = theData->width * theData->height * sizeof(unsigned char);
	// Allocate memory for the image data
	theData->imageData = (unsigned char *) malloc(theData->nImageBytes + 1);
	// Ensure memory was allocated correctly
	if (!theData->imageData)
	{
		return EXIT_MALLOC_FAIL;
	}
	int grayValue = -1, i = 0, numBytes = theData->nImageBytes, scanCount = 0;
	unsigned char *nextGrayValue = theData->imageData;
	// Loop to retrieve the image data. Counts down from the size of the number of image bytes
	while (numBytes > 0)
	{
		grayValue = -1;
		scanCount = fscanf(input_file, " %u", &grayValue);
		// Return exit code if nothing read in, or bad dimensions
		if (scanCount == -1)
		{
			return EXIT_BAD_DATA;
		}
		if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))
		{
			return EXIT_BAD_DIMENSIONS;
		}
		// Store imageData value
		*nextGrayValue = (unsigned char) grayValue;
    	theData->imageData[i] = *nextGrayValue;
		i++;
		nextGrayValue++;
		numBytes--;
	}
	grayValue = -1;
	// If more data than number of image bytes, return exit code
	if (fscanf(input_file, " %u", &grayValue) == 1)
	{
		return EXIT_BAD_DATA;
	}
	return EXIT_NO_ERRORS;
}

int getBinaryData (FILE *input_file, fileData *theData) 
{
	// Calculate the size of the image bytes required
	theData->nImageBytes = theData->width * theData->height * sizeof(unsigned char);
	// Allocate memory for the image data
	theData->imageData = (unsigned char *) malloc(theData->nImageBytes);
	int count = 0;
	// Check memory was allocated correctly
	if (!theData->imageData)
	{
		return EXIT_MALLOC_FAIL;
	}
	// Scan whitespace if any present
	fscanf(input_file, " ");
	int numBytes = theData->nImageBytes, i = 0;
	// Read in binary data and keep a count of number of bytes read in
	count = fread(theData->imageData, 1, numBytes + 5, input_file);
	// If more data read in than the number of imageBytes required, return error code
	if (count > theData->nImageBytes || count < theData->nImageBytes)
	{
		return EXIT_BAD_DATA;
	}
	// Return 0 exit code on success
	return EXIT_NO_ERRORS;
}