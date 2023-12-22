#include "County.h"

County::County(std::string cn, int p, double z, double f, double t, double ff, double s) {
    countyname = cn;
    pop = p;
    zero = z;
    fifteen = f;
    thirty = t;
    fourtyfive = ff;
    sixty = s;
}

std::string County::asString() {
    return "{" + countyname + "," + std::to_string(pop) + "," + std::to_string(zero) + "," + std::to_string(fifteen)+ std::to_string(thirty) + "," + std::to_string(sixty) + "}";
}