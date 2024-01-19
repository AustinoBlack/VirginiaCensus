#include <fstream>
#include <iostream>
#include <string>

// created with help from AI - introduced tellg(), seekg() and logic from lines 7,8,20,&21 to me so thanks!
int compareFiles(const std::string& correct_file, const std::string& testing_file) {
    std::ifstream file1(correct_file, std::ifstream::binary | std::ifstream::ate);
    std::ifstream file2(testing_file, std::ifstream::binary | std::ifstream::ate);

    if (!file1.is_open() || !file2.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return 1; // Error in opening file
    }

    if (file1.tellg() != file2.tellg()) {
        return 1; // Sizes are different
    }

    // Reset both files to the beginning
    file1.seekg(0, std::ifstream::beg);
    file2.seekg(0, std::ifstream::beg);

    char ch1, ch2;
    while (file1.get(ch1) && file2.get(ch2)) {
        if (ch1 != ch2) {
            return 1; // Contents are different
        }
    }

    return 0; // Files are identical
}

int main( int argc, char* argv[] )
{
    if( argc != 3 )
    {
        std::cout << "Must include two files\n - Correct file first, Testing file second\n";
        return 1;
    }

    std::string path = "/Users/austinoblack/Desktop/Projects/VirginiaCensus/version_C++/Tests/";
    //std::cout << "Correct_file: " << argv[1] << std::endl;
    //std::cout << "Testing_file: " << argv[2] << std::endl;

    //build path to correct file - correct file is in the Test directory, output files are in the debug folder
    std::string correct_file = path + argv[1];
    std::string testing_file = argv[2];

   // std::cout << correct_file << std::endl << testing_file << std::endl;

    int result = compareFiles(correct_file, testing_file);
    if (result == 0) {
        std::cout << "Files are identical." << std::endl;
    } else {
        std::cout << "Files are different." << std::endl;
    }

    return result;
}