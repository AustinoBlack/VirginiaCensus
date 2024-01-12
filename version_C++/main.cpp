#include <iostream>
#include "Color.h"
#include "County.h"
#include "libpq-fe.h"

/* connect DB attempts to connect to a Postgres database provided by a given conninfo.
 * - A successful connection will return the connection.
 * - An unsuccessful connection will display an error and gracefully exit the program.
 */
PGconn* connectDB( const char* conninfo )
{
    // Attempt Database Connection
    PGconn* conn = PQconnectdb(conninfo);

    // Check if the connection is successful
    if (PQstatus(conn) != CONNECTION_OK) {
        // If not successful, print the error message and finish the connection
        printf("Error while connecting to the database server: %s\n", PQerrorMessage(conn));

        // Finish the connection
        PQfinish(conn);

        // Exit the program
        exit(1);
    }

    // Print connection successful message and stats about what we connected to
    printf("Connection Established\n");
    printf("Port: %s\n", PQport(conn));
    printf("Host: %s\n", PQhost(conn));
    printf("DBName: %s\n", PQdb(conn));

    // Return the connection
    return conn;
}

int main()
{
    const char* conninfo = "dbname=censusdata user=austinoblack password=(AUS.Census.1998) host=CensusData.local port=5432";
    PGconn* conn = connectDB( conninfo );

    char* query = "SELECT county FROM vacensus WHERE population = 23022"; // should return Prince_Edward

    //executes the query
    PGresult *res = PQexec(conn, query);

    //prints out the value returned
    printf("%s\n", PQgetvalue(res, 0, 0));

    // Close the connection and free the memory
    PQfinish(conn);

    std::cout << "{Hello, World!}" << std::endl;
    Color testcolor = Color(1, 2, 3);
    County testcounty = County("test", 1, 2, 3, 4, 5, 6);

    std::cout << testcolor.asString() << std::endl;
    std::cout << testcounty.asString() << std::endl;
}
