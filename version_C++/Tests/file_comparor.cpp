#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void compareFiles(FILE *file1, FILE *file2) {
    char ch1 = getc(file1);
    char ch2 = getc(file2);
    int error = 0, pos = 0, line = 1;
    while (ch1 != EOF && ch2 != EOF) {
        pos++;
        if (ch1 == '\n' && ch2 == '\n') {
            line++;
            pos = 0;
        }
        if (ch1 != ch2) {
            error++;
            printf("Line Number : %d \tError \n Position : %d ", line, pos);
        }
    }
}

int main( int argc, char* argv[] )
{
    std::cout << "file1: " << argv[1] << std::endl;
    std::cout << "file2: " << argv[2] << std::endl;

    if( argc != 3 )
    {
        std::cout << "Must include two files\n";
        return 1;
    }

    else
    {

        FILE* f1 = fopen( "one.txt","r" );
        FILE* f2 = fopen( "two.txt","r" );
        if (f1 == NULL || f2 == NULL){
            printf("Error : Files not open");
            exit(1);
        }
        compareFiles( f1, f2 );
        fclose( f1 );
        fclose( f2 );
    }
}