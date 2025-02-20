# Nick Notes
## To Build Program
``` Bash
git clone https://github.com/kohlsne/fakerest-test.git
cd FAKEREST-TEST
make
```

## To Run Program
To see list of commands:
```
./prog -h
```
Arguments:
```
-v  Enable verbose mode
-e  Specify the endpoint address (e.g. http://test.brightsign.io:3000)
-1  Output average age of all users per city
-2  Output average number of friends per city
-3  Output the user with the most friends per city
-4  Output the most common first name in all cities
-5  Output the most common hobby of all friends of users in all cities
-h  Display this help message
```
Example:
``` Bash
./prog -e http://test.brightsign.io:3000 -4

```
Outputs:
```
[["name","Michael"]]
```

## Unit Tests
test.cpp contains unit tests

To run the tests:
``` 
./test
```


## External Libraries Used
### httplib
https://github.com/yhirose/cpp-httplib
- Single Header
- Simplifies HTTP requests

### json
https://github.com/nlohmann/json
- Single Header
- JSON objects
- JSON parser

### acutest
- Single Header
- Provides google like unit tests


### Considerations
- No need to reinvent the wheel. I opted out of using a custom parser and object to injest the JSON
- Calculations could be simplified using SQL commands with the embedded database SQLite, but REST is stateless and the endpoint needs to be queried  everytime

## JSON Objects
The user object contains:
- id
- name
- city
- age
- list of friends
    - name
    - list of hobbies
## Security

## Assumptions\
- Calculating "the most common first name in all cities" does not include the friends names
- Any calculation that requires the max of a parameter, will return multiple object if they all have the max.
---
---

# Take-Home Coding Assignment
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
