#include <iostream>
#include "Color.h"
#include "County.h"
#include "libpq-fe.h"

int main()
{
    //stubs to test compilation
    const char* conninfo;
    PGconn* conn;

    std::cout << "{Hello, World!}" << std::endl;
    Color testcolor = Color(1, 2, 3);
    County testcounty = County("test", 1, 2, 3, 4, 5, 6);

    std::cout << testcolor.asString() << std::endl;
    std::cout << testcounty.asString() << std::endl;
}
