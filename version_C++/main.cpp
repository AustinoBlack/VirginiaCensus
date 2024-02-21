#include <iostream>
#include <string>
#include <vector>
#include <fstream>
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
    //printf("Query Status: %s\n", PQresStatus(resStatus));

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
    //printf("Query Executed Successfully\n");

    // return the result
    return res;
}

/* createColor creates a path tag with the appropriate rgb values with a given county and connection */
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

/* pullCounties queries and returns a vector of all county names from the vacensus table from a given connection */
std::vector<std::string> pullCounties( PGconn* conn )
{
    std::vector<std::string> rv;
    std::string query = "SELECT county "
                        "FROM vacensus";

    //execute query
    PGresult* res = executeQuery( conn, query.c_str() );

    //put results into a vector
    rv.reserve(PQntuples(res));
    for( int i = 0; i < PQntuples(res); i++ )
    {
        rv.emplace_back( PQgetvalue(res, i, 0) );
        //std::cout << rv[i] << std::endl; // DEBUG
    }

    //return the vector of county names
    return rv;
}

int main()
{
    // establish DB connection
    const char* conninfo = "dbname=censusdata user=austinoblack password=(AUS.Census.1998) host=CensusData.local port=5432";
    PGconn* conn = connectDB( conninfo );

    // open file
    std::fstream temp;
    std::fstream out;
    temp.open( "Virginia.template", std::fstream::in );
    out.open( "Virginia.svg", std::fstream::out | std::fstream::trunc );
/*
    // get number of lines
    file.unsetf(std::ios_base::skipws);
    unsigned line_count = std::count(
            std::istream_iterator<char>(file),
            std::istream_iterator<char>(),
            '\n');

    std::cout << "Lines: " << line_count << "\n";
*/
    // main loop
    std::string line;
    std::string prev;
    std::string title;
    int i = 1;
    while ( getline( temp, line) ) {
        if ( i <= 7 || i == 276 ) {
            out << line << std::endl;
        }

        else if( i > 7 && i%2 != 0 && i < 276) {
            //std::cout << "LINE: " << i << std::endl;
            title = line;
            line = line.erase(0, 15);
            line = line.erase( line.length() - 15, 15);
            //std::cout << "COUNTY: " << line  << std::endl;
            //std::string color = createColor(conn, line );
            out << "\t" << createColor(conn, line ) << " " << prev << std::endl;
            out << title << std::endl;
        }

        else if( i > 7 && i%2 == 0 && i < 276 ){ // get path data and hold on to it
            //std::cout << "LINE: " << i << std::endl;
            prev = line.erase( 0, 10 );
            //std::cout << "PREV: " << prev << std::endl;
        }
        i++;
    }

    temp.close();
    out.close();
    closeConnection( conn );

    std::cout << "DONE!" << std::endl;
}
