
int reader (FILE *input_file, fileData *theData);
int getMagic (FILE *input_file, fileData *theData);
int commentRead (FILE *input_file, fileData *theData);
int getDimensions (FILE *input_file, fileData *theData);
int getBinaryData (FILE *input_file, fileData *theData);
int getAsciiData (FILE *input_file, fileData *theData);
int validate (FILE *input_file, fileData *theData);