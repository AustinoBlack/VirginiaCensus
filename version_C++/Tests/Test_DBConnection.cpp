#include <iostream>
#include "libpq-fe.h"

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

void closeConnection( PGconn* conn )
{
    PQfinish( conn );
}

int main()
{
    const char* conninfo = "dbname=censusdata user=austinoblack password=(AUS.Census.1998) host=CensusData.local port=5432";
    PGconn* conn = connectDB( conninfo );

    closeConnection( conn );
}
