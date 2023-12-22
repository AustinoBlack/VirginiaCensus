#ifndef Color_H
#define Color_H

#include <string>

class Color {
    private:
        double red;
        double green;
        double blue;

    public:
        /* class Constructor */
        Color( double red, double green, double blue );

        /* Prints a string representation of the Color class in svg format */
        std::string asString();
};

#endif
