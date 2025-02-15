# Nick Notes
1. Create Command Parser
    create database from urlqq:w
    average age of all users per city
    average number of friends per city
    the user with the most friends per city
    the most common first name in all cities
    the most common hobby of all friends of users in all cities

2. Create Json getter
3. Create Json Parser
4. Parse data and input into SQLite
5. Using Database operations to select info and output in JSON format
# Take-Home Coding Assignment
ID NAME CITY AGE FREINDS(list)
FRIENDS - NAME HOBBIES(list) 
{"id":200000,
"name":"Elijah",
"city":"Orlando",
"age":62,
"friends":[{"name":"Camila","hobbies":["Martial Arts","Dancing"]},{"name":"Sarah","hobbies":["Running","Team Sports","Woodworking"]}]}



{"id":200001,"name":"Charlotte","city":"New Orleans","age":72,"friends":[{"name":"Mia","hobbies":["Painti
ng","Movie Watching","Socializing"]},{"name":"Grace","hobbies":["Skiing & Snowboarding","Yoga"]},{"name":
"Oliver","hobbies":["Genealogy","Music","Fishing"]}]}
{"id":200002,"name":"Daniel","city":"Miami Beach","age":71,"friends":[{"name":"Emma","hobbies":["Painting","Team Sports","Video Games"]},{"name":"Chris","hobbies":["Music","Housework"]}]}
{"id":200003,"name":"Elijah","city":"Los Angeles","age":63,"friends":[{"name":"Sophie","hobbies":["Yoga","Golf"]},{"name":"Elijah","hobbies":["Gardening","Dancing","Quilting"]}]}
{"id":200004,"name":"Sophie","city":"Savannah","age":66,"friends":[{"name":"Michelle","hobbies":["Music","Gardening","Calligraphy"]},{"name":"Mateo","hobbies":["Movie Watching","Running"]},{"name":"Zoey","hobbies":["Genealogy","Housework"]},{"name":"Jack","hobbies":["Music","Volunteer Work","Writing"]},{"name":"Emma","hobbies":["Socializing","Bicycling"]}]}



## JSON REST client

This coding assignment will allow us to evaluate your ability to write a REST client that processes JSON data.  This is aimed at a more senior Engineer.

When assigned this test you will also be instructed if there is a preferred language to use, usually typescript, C++ or golang.  If not directed otherwise,
you may use any language you like. We are looking for clean, simple code that works and that is easy to read and understand.

Please follow these instructions *exactly* and carefully read the requirements below.  We will ignore any submissions that don't follow these instructions.

## Instructions

The program should query "http://test.brightsign.io:3000" and process the data returned. NOTE: the data returned is not real data and is not sensitive.

The data returned is a JSON array and it changes on each call to the server.  The data is an array of user objects.
There is no further documentation on the format of the data.  You must figure it out from the data itself.  Please consider this as part of the test, and document your findings in your README.

Using the data retreived from the endpoint, calculate #1 and #2.  Unless you have been asked to do more the other tasks are optional, but will be considered as extra credit.

## Calculations

1. average age of all users per city
2. average number of friends per city
3. the user with the most friends per city
4. the most common first name in all cities
5. the most common hobby of all friends of users in all cities

## Output

The data output must be in JSON format suitable for analysis with a CLI tool like jq.

## Requirements

PLEAE READ AND FOLLOW ALL THE INSTRUCTIONS.  We will ignore any submission that does not follow these instructions.

* The challenge is to do a simple REST implementation of this protocol yourself
* Command line only - no GUI wanted or needed.  Please don't do a GUI
* Must run on the command line (terminal), accepting the endpoint to be queried as a command line parameter and returning the data desired
* Program must query the API for a result over the network
* The program must be able to be run repeatedly and process the data correctly each time, even if the data changes
* The program must handle reasonable error conditions
* All source code for the program must be in a public GitHub repository
* You should assume we will clone your repo and test it personally
* You should "think unix philosophy" and consider how this kind of tool would build your toolbox
* Provide some kind of README explaining your work and how others would use it
* Consider security in your solution, even if it's just discussing it in your README
* This is an example of your work.  Don't make a career out of it but take the time to do a decent job

## Submission

Please just submit the URL of the public GitHub repository you used for this assignment.
