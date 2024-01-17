#include <iostream>
#include <string>
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

/* closeConnection closes the connection to a Postgres database provided by a given PGconn* conn */
void closeConnection( PGconn* conn )
{
    PQfinish( conn );
}

/* executeQuery executes a given query on a given connection */
PGresult* executeQuery( PGconn* conn, char* query )
{
    PGresult *res = nullptr;

    // clear previous query result
    PQclear( res );

    // Submit the query and retrieve the result
    res = PQexec(conn, query);

    // Check the status of the query result
    ExecStatusType resStatus = PQresultStatus(res);

    // Convert the status to a string and print it
    printf("Query Status: %s\n", PQresStatus(resStatus));

    // Check if the query execution was successful
    if (resStatus != PGRES_TUPLES_OK) {
        // If not successful, print the error message and finish the connection
        printf("Error while executing the query: %s\n", PQerrorMessage(conn));

        // Clear the result
        PQclear(res);

        // Finish the connection
        PQfinish(conn);

        // Exit the program
        exit(1);
    }

    // We have successfully executed the query
    printf("Query Executed Successfully\n");

    // return the result
    return res;
}

/* createColor creates a path tag with the appropriate rgb values with a given county and connection */
std::string createColor( PGconn* conn, std::string county )
{
    std::string rv;
    return rv;
}

int main()
{
    const char* conninfo = "dbname=censusdata user=austinoblack password=(AUS.Census.1998) host=CensusData.local port=5432";
    PGconn* conn = connectDB( conninfo );

    closeConnection( conn );
}
