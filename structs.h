
typedef struct _fileData {

    char format;
    char * commentLine;
    unsigned int width;
    unsigned int height;
    unsigned int maxGray;
    unsigned char * imageData;
    long nImageBytes;
    int scanCount;
    int returnCode;
    

} fileData;
