# A Python program to produce a map of VA and its counties

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

def Main():
    county = County( "Richmond.City", "213735", "15.9", "28.8", "20", "18.3", "17.2" )
    print( county )

    y = Color( county.young, county.middle, county.old )
    print( y )

Main()
