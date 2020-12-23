## Important Things:
1. Include .h header files in .c source file will still need to compile or link all the .c source files correspond to the header files.<br />
If we using normal mode to build the executable suppose we have main.c, func.h and func.c and func.h is included in main.c:<br />
gcc -o main main.c func.c<br />
If we want to make object files we need to do the following in below.<br />
2. We can't pass multiple .c files to gcc when compiling using -c mode because they are not going to be linked in -c mode. The solution will be compile each .c files to multiple object files in -c mode and use ld to link all the object files together.<br />
gcc -o main.o -c main.c<br />
gcc -o func.o -c func.c<br />
then use ld to link them together.