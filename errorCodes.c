#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "errorCodes.h"
#include "exitCodes.h"

/*
    Function to print the correct error code based on the
    parameters passed to it. The parameters are the error
    code and the relevant file in which the error occurred.
*/

int errorCodes (int returnCode, char *errorFile)
{
    if (returnCode == 2)
    {
        printf("ERROR: Bad File Name (%s)", errorFile);
    }
    if (returnCode == 3)
    {
        printf("ERROR: Bad Magic Number (%s)", errorFile);
    }
    if (returnCode == 4)
    {
        printf("ERROR: Bad Comment Line (%s)", errorFile);
    }
    if (returnCode == 5)
    {
        printf("ERROR: Bad Dimensions (%s)", errorFile);
    }
    if (returnCode == 6)
    {
        printf("ERROR: Bad Max Gray Value (%s)", errorFile);
    }
    if (returnCode == 7)
    {
        printf("ERROR: Image Malloc Failed");
    }
    if (returnCode == 8)
    {
        printf("ERROR: Bad Data (%s)", errorFile);
    }
    if (returnCode == 9)
    {
        printf("ERROR: Output Failed (%s)", errorFile);
    }
    if (returnCode == 10)
    {
        printf("ERROR: Bad Layout");
    }
    return returnCode;
}