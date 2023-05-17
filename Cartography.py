# A Python program to produce a map of VA and its counties

import psycopg2

class Color:
    def __init__(self, red, green, blue):
        self.red = red
        self.green = green
        self.blue = blue

    def __str__(self):
        return "<path fill=\"rgb(" + str((self.red/100)*255) + "," + str((self.green/100)*255) + "," + str((self.blue/100)*255) + ")\""


class County:
    def __init__(self, name, pop, zero, fifteen, thirty, fourtyfive, sixty):
        self.name = name
        self.pop = pop
        self.zero = zero
        self.fifteen = fifteen
        self.thirty = thirty
        self.fourtyfive = fourtyfive
        self.sixty = sixty

        self.young = float(self.zero) + float(self.fifteen)
        self.middle = float(self.thirty) + float(self.fourtyfive)
        self.old = float(self.sixty)

    def __str__(self):
        return "Name: " + self.name + "\nPop: " + self.pop + "\nAge 0-14: " + self.zero + "\nAge 15-29: " + self.fifteen + "\nAge 30-44: " + self.thirty + "\nAge 45-60: " + self.fourtyfive + "\nAge 60+: " + self.sixty


def pull_counties():
    '''opens "va-tiny-names.txt" and creates a list of county names as they appear in the file'''
    rv = []
    with open("va-tiny-names.txt") as file:
        iterator = 0
        for line in file:
            iterator = iterator + 1
            if (iterator > 7) and (iterator % 2 != 0):
                line = line.replace( '<title>', '' )
                line = line.replace( '</title>', '' )
                line = line.replace( '</path>', '' )
                line = line.strip( '\n' )
                rv.append( line )
    return rv


def create_color( county ):
    '''opens the vacensus database, finds the statistics for a given county and creates the appropiate rgb values, and retuns a string representation of the rgb value'''
    with psycopg2.connect( database="vacensus", user="austinoblack", password="(AUS.Data.1998)", host="localhost" ) as conn:
        with conn.cursor() as cur:
            cur.execute( 'SELECT * FROM vacensus WHERE county = %s', (county + ' ', ) )
            stats = cur.fetchone()
            if stats:
                county = County( stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6] )
                rgb = Color( county.young, county.middle, county.old )
                return str( rgb ) 
            else:
                return 'DONE'
    conn.close()


def Main():
    counties = pull_counties()
    colors = []
    for county in counties:
        colors.append( create_color( county ) )
    print( colors )
    with open(


Main()
