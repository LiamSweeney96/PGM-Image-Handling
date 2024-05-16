#
# COMP 1921 Programming Project
# 2021-22 Spring Semester
#
# Liam Sweeney
#
#
# Makefile

TARGETS=pgmEcho pgmComp pgma2b pgmb2a pgmReduce 

all:	$(TARGETS)

# NB on compile flags:
#   -E                  preprocess only
#   -c                  compile only
#   -g                  debug support for gdb
#   -std=c99            use the C99 C standard
#   -o pgmEcho          output file name
#   -Wall               turn all warnings on
#   -Werror             treat all warnings as errors

# First target is the default, so make it the entire Programming
# target            implementation                            																				interfaces
pgmEcho:			pgmEcho.c reader.c writeFile.c errorCodes.c																				pgmEcho.h exitCodes.h structs.h reader.h writeFile.h errorCodes.h
#       tool        compile flags                                   output name			files to compile
		gcc			-g -std=c99										-o pgmEcho			pgmEcho.c reader.c writeFile.c errorCodes.c

# target            implementation 																											interfaces
pgmComp:			pgmComp.c reader.c testFiles.c errorCodes.c				 																pgmComp.h structs.h exitCodes.h reader.h testFiles.h errorCodes.h
#       tool        compile flags                                   output name			files to compile
		gcc			-g -std=c99 									-o pgmComp			pgmComp.c reader.c testFiles.c errorCodes.c

# target            implementation 																											interfaces
pgma2b:				pgma2b.c reader.c writeFile.c errorCodes.c								 				 								pgma2b.h structs.h exitCodes.h reader.h writeFile.h errorCodes.h
#       tool        compile flags                                   output name			files to compile
		gcc			-g -std=c99 									-o pgma2b			pgma2b.c reader.c writeFile.c errorCodes.c

# target            implementation 																											interfaces
pgmb2a:				pgmb2a.c reader.c writeFile.c errorCodes.c								 				 								pgmb2a.h structs.h exitCodes.h reader.h writeFile.h errorCodes.h
#       tool        compile flags                                   output name			files to compile
		gcc			-g -std=c99										-o pgmb2a			pgmb2a.c reader.c writeFile.c errorCodes.c 

# target            implementation 																											interfaces
pgmReduce:			pgmReduce.c reader.c reduce.c writeFile.c errorCodes.c											 						pgmReduce.h structs.h exitCodes.h reader.h reduce.h writeFile.h errorCodes.h
#       tool        compile flags                                   output name			files to compile
		gcc			-g -std=c99 									-o pgmReduce		pgmReduce.c reader.c reduce.c writeFile.c errorCodes.c

clean:
		rm -rf *.o pgmEcho pgmComp pgma2b pgmb2a pgmReduce