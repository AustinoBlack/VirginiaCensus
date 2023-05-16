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


def gather_counties():
    '''opens the vacensus table and returns a list of all county names from the county column'''
    with psycopg2.connect( database="vacensus", user="austinoblack", password="(AUS.Data.1998)", host="localhost" ) as conn:
        with conn.cursor() as cur:
            cur.execute( 'SELECT county FROM vacensus' )
            rv = [r[0] for r in cur.fetchall()]
    conn.close()
    return rv


def Main():
    names = gather_counties()
    print( names )


Main()
