#include <iostream>
#include <fstream>
#include <string>
#include "../Color.h"

// a sample program that creates a file with a color for testing file comparison logic and working directory structure
// this will act as a template for future testing
int main()
{
    std::ofstream f( "Color_Output.txt", std::ifstream::trunc);

    Color c = Color( 100, 0, 0 );

    f << c.asString();
}
