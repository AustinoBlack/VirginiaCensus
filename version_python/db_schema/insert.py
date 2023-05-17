import psycopg2
import os

def insert_data():
    conn = psycopg2.connect( database="vacensus", user="austinoblack", password="(AUS.Data.1998)", host="localhost" )
    cur = conn.cursor()

    with open( "census2010.txt" ) as f:
        data = []
        for line in f:
            temp = line.strip('\n')
            temp = temp.split('\t')
            data.append( temp )
            print( data )
        f.close()

    for row in data:
        print( row )
        cur.execute( "INSERT INTO vacensus (county, population, group1, group2, group3, group4, group5) VALUES (%s, %s, %s, %s, %s, %s, %s)", (row[0], row[1], row[2], row[3], row[4], row[5], row[6]) )
        conn.commit()
    conn.close()
    print( "DONE\n" )

insert_data()
