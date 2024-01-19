#include <iostream>
#include <fstream>
#include <string>

// a sample program that creates a file with a color for testing file comparison logic and working directory structure
// this will act as a template for future testing
int main()
{
    std::string str = "Red";
    std::ofstream f( "Color_Output.txt", std::ifstream::trunc);

    f << str;
}
