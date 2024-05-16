
#!/bin/sh

#pgmEcho

echo "pgmEcho Testing:"

#pgmEcho when given bad comment line
./pgmEcho badComment.pgm outputImage.pgm 

#pgmEcho when given too much data
./pgmEcho tooMuchData.pgm outputImage.pgm 

#pgmEcho when given bad data
./pgmEcho badData.pgm outputImage.pgm 

#pgmEcho when given bad magic number
./pgmEcho badMagic.pgm outputImage.pgm

#pgmEcho when given bad max gray value
./pgmEcho badMaxGray.pgm outputImage.pgm

#pgmEcho echoing an ascii file
./pgmEcho inputImage.pgm outputImage.pgm

#pgmEcho echoing a binary file
./pgmEcho binaryImage.pgm outputImage.pgm


#pgmComp

echo "pgmComp Testing:"

#pgmComp when given bad comment line
./pgmComp badComment.pgm outputImage.pgm 

#pgmComp when given too much data
./pgmComp tooMuchData.pgm outputImage.pgm 

#pgmComp when given bad data
./pgmComp badData.pgm outputImage.pgm 

#pgmComp when given bad magic number
./pgmComp badMagic.pgm outputImage.pgm

#pgmComp when given bad max gray value
./pgmComp badMaxGray.pgm outputImage.pgm

#pgmComp comparing two identical ascii files
./pgmComp inputImage.pgm inputImage.pgm

#pgmComp comparing two non-identical ascii files
./pgmComp inputImage.pgm inputImageTwo.pgm

#pgmComp comparing two identical binary files
./pgmComp binaryImage.pgm binaryImage.pgm

#pgmComp comparing two non-identical binary files
./pgmComp binaryImage.pgm binaryImageTwo.pgm

#pgma2b

echo "pgma2b Testing:"

#pgma2b when given bad comment line
./pgma2b badComment.pgm outputImage.pgm 

#pgma2b when given too much data
./pgma2b tooMuchData.pgm outputImage.pgm 

#pgma2b when given bad data
./pgma2b badData.pgm outputImage.pgm 

#pgma2b when given bad magic number
./pgma2b badMagic.pgm outputImage.pgm

#pgma2b when given bad max gray value
./pgma2b badMaxGray.pgm outputImage.pgm

#pgma2b converting valid ascii file
./pgma2b inputImage.pgm outputImage.pgm

#pgma2b when given binary file as input image
./pgma2b binaryImage.pgm outputImage.pgm

#pgmb2a

echo "pgmb2a Testing:"

#pgmb2a when given bad comment line
./pgmb2a badComment.pgm outputImage.pgm 

#pgmb2a when given too much data
./pgmb2a tooMuchData.pgm outputImage.pgm 

#pgmb2a when given bad data
./pgmb2a badData.pgm outputImage.pgm 

#pgmb2a when given bad magic number
./pgmb2a badMagic.pgm outputImage.pgm

#pgmb2a when given bad max gray value
./pgmb2a badMaxGray.pgm outputImage.pgm

#pgmb2a converting valid binary file
./pgmb2a binaryImage.pgm outputImage.pgm

#pgmb2a when given ascii file as input image
./pgmb2a inputImage.pgm outputImage.pgm

#pgmReduce

echo "pgmReduce Testing:"

#pgmReduce when given bad comment line
./pgmReduce badComment.pgm outputImage.pgm 

#pgmReduce when given too much data
./pgmReduce tooMuchData.pgm outputImage.pgm 

#pgmReduce when given bad data
./pgmReduce badData.pgm outputImage.pgm 

#pgmReduce when given bad magic number
./pgmReduce badMagic.pgm outputImage.pgm

#pgmReduce when given bad max gray value
./pgmReduce badMaxGray.pgm outputImage.pgm

#pgmReduce when given ascii file to reduce
./pgmReduce inputImage.pgm 3 outputImage.pgm

#pgmReduce when given binary file to reduce
./pgmReduce binaryImage.pgm 3 outputImage.pgm
