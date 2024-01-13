# VirginiaCensus
A virginia map that colors counties accoring to the age of the population inside said counties.

Being the Final Project of my cmsc 160 class, I figure this will be a good template to show my improved skills. 
The original final verison of my project will be uploaded, then improvements showing the skills I've learned will follow.

Thank you to Dr. Dymacek for originally assiging this project and providing the census2010.txt and va-tiny-names.txt files. 

# Original Version
The program opens two files, census2010.txt (contains 2010 census data) and va-tiny-name.txt(an outline of Virginia and its counties). It then uses the census data to build a color determined by the age population of the county, applies the color to the county, and outputs an svg file containing a map of Virginia's counties colored according to its age demographic.

- Bugs and Issues:
  - The complete old version did not assign the correct color to the correct county, so the map that is created is inaccurate.


# Updated Version (Python - Complete)
The updated program will still open and use the va-tiny-names.txt and will to produce a virginia.svg file, but will open and use an SQL database in place of the census2010.txt file. This will be an improvement over the original version because it is more 'real world' and allows the user to simply update the database as needed. Plus, this allows me to demonstrate the skills I have learned throughout my time at Longwood.

- Notes:
  For this version, I decided to use Python as it is what I am currently most familiar with in interacting with databases. In this version, I accomplished moving the census data from a text file to an postgreSQL database, and fixed the logic from my original version to correctly and accurately display the colors associated with each county. 
  
- Fixes:
  Correctly display rgb values associated with each county, the created svg file is accurate to the census data.
  
# Updated Version (C++ - In-Progress)
The updated program will use a postgreSQL database instead of a text file for county data, hosted from a raspberry pi on my local network. I will be using the libpq++ library (https://www.postgresql.org/docs/7.2/libpqplusplus.html) to connect to the postgreSQL server.

- Notes:
  used Homebrew (https://brew.sh/) to install libpq 
  thank you to this article to elaborating more on the libpq library and its functions (https://dev.to/omarsaad/building-a-postgresql-database-client-with-libpq-in-c-connecting-and-executing-queries-5a51)
