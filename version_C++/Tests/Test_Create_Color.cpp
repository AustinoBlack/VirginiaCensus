#include <iostream>
#include <fstream>
#include <string>
#include "libpq-fe.h"
#include "../Color.h"

PGresult* executeQuery( PGconn* conn, const char* query )
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

std::string createColor( PGconn* conn, const std::string county )
{
    //build query for given county
    std::string query = "SELECT group1, group2, group3, group4, group5 "
                        "FROM vacensus "
                        "WHERE county = '" + county + " '";

    //execute query
    PGresult* res = executeQuery( conn, query.c_str() );

    //parse results into separate rgb percentages.
    int r = atoi( PQgetvalue(res, 0, 0)) + atoi(PQgetvalue(res, 0, 1)); // 0 - 30
    int g = atoi( PQgetvalue(res, 0, 2)) + atoi(PQgetvalue(res, 0, 3)); // 30 - 60
    int b = atoi( PQgetvalue(res, 0, 4)); // 60 +
    //std::cout << r << "\t" << g << "\t" << b << std::endl; //DEBUG

    // build <path> tag with parsed results
    Color color (r, g, b);

    //return the path tag
    return color.asString();
}

int main(int argc, char* argv[])
{
    std::string file = argv[1];

    // Database info & connection
    const char* conninfo = "dbname=censusdata user=austinoblack password=(AUS.Census.1998) host=CensusData.local port=5432";
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

    // open given filename and insert pathtag
    std::ofstream f( file.substr(0, file.length()) + ".txt", std::ifstream::trunc);
    f << createColor( conn, file ) << std::endl;
}
