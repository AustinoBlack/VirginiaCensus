#ifndef County_H
#define County_H

#include <string>

class County {
    private:
        std::string countyname;
        int pop;
        double zero;
        double fifteen;
        double thirty;
        double fourtyfive;
        double sixty;

    public:
        /* class Constructor */
        County( std::string countyname, int pop, double zero, double fifteen, double thirty, double fourtyfive, double sixty );

        /* Prints the class as a readable string */
        std::string asString();
};

#endif