#include <iostream>
#include <unistd.h> // getopt - parsing
#include "restclient.h" // custom class
#include <string>
#include "external/httplib.h"
#include <fstream>


int main(int argc, char *argv[])
{
    int opt;
    std::string endpoint;
    unsigned int answerOptionCnt = 0;
    Query query = Query::NO_QUERY;

    // Parse command line options
    while ((opt = getopt(argc, argv, "e:h12345")) != -1)
    {
        switch (opt)
        {
        case '1':
            answerOptionCnt++;
            query=Query::AVE_AGE_PER_CTY;
            break;
        case '2':
            answerOptionCnt++;
            query=Query::AVE_NUM_FRIENDS_PER_CTY;
            break;
        case '3':
            answerOptionCnt++;
            query=Query::USER_MOST_FRIENDS_PER_CTY;
            break;
        case '4':
            answerOptionCnt++;
            query=Query::MOST_COMMON_FIRST_NAME;
            break;
        case '5':
            answerOptionCnt++;
            query=Query::MOST_COMMON_HOBBY;
            break;
        case 'e':
            endpoint = optarg;
            if (endpoint.back() == '/')
            {
                endpoint.pop_back();
            }
            break;
        case 'h':
            std::cout << "Usage: " << argv[0] << " [-v] [-e <endpoint>] [-h]\n";
            std::cout << "  -v            Enable verbose mode\n";
            std::cout << "  -e <endpoint> Specify the endpoint address (e.g. http://test.brightsign.io:3000)\n";
            std::cout << "  -1            Output average age of all users per city\n";
            std::cout << "  -2            Output average number of friends per city\n";
            std::cout << "  -3            Output the user with the most friends per city\n";
            std::cout << "  -4            Output the most common first name in all cities\n";
            std::cout << "  -5            Output the most common hobby of all friends of users in all cities\n";
            std::cout << "  -h            Display this help message\n";
            return 0;
        default:
            std::cerr << "Error Usage: " << argv[0] << " [-v] [-e <endpoint>] [-h] [-num]\n";
            return 1;
        }
    }

    // Check if arguments are correct
    if (endpoint.empty())
    {
        std::cout << "No endpoint specified.\n";
        return 1;
    }
    if (answerOptionCnt != 1)
    {
        std::cout << "Please Specify Only One Query\n";
        return 1;
    }

    //create rest client
    RestClient restClient(endpoint);
    //get data from endpoint
    std::string responseBody = restClient.getJson();


    //////////////////////////
    std::string filename = "my_file.txt"; // Or any filename you want
    std::ofstream outputFile(filename); // Open the file for writing
    if (outputFile.is_open()) {
        outputFile << responseBody << std::endl; // Write the string to the file, std::endl adds a newline
        outputFile.close(); // Close the file (important!)
        std::cout << "String saved to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return 1; // Indicate an error
    }
////////////////////////////////
    //parse data and update private member data structures
    restClient.parseJson(responseBody);
    //output the specified quiried results
    std::cout << restClient.getQueryResults(query);
    
    return 0;
}
