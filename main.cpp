#include <iostream>
#include <unistd.h> // getopt - parsing
#include "client.h" // custom class
#include <string>
#include "external/httplib.h"

int main(int argc, char *argv[]) {
    int opt;
    std::string endpoint;

    // Parse command line options
    while ((opt = getopt(argc, argv, "e:h")) != -1) {
        switch (opt) {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case 'e':
                endpoint = optarg;
		if (endpoint.back() == '/'){
			endpoint.pop_back();
		}
                break;
            case 'h':
                std::cout << "Usage: " << argv[0] << " [-v] [-f <filename>] [-h]\n";
                std::cout << "  -v          Enable verbose mode\n";
                std::cout << "  -f <file>   Specify the input file\n";
                std::cout << "  -h          Display this help message\n";
                return 0;
            default:
                std::cerr << "Usage: " << argv[0] << " [-v] [-f <filename>] [-h]\n";
                return 1;
        }
    }

    // Output the parsed options
    if (endpoint.empty()) {
        std::cout << "No endpoint specified.\n";
	return 1;
    }
	std::cout << "Endpoint: " << endpoint << std::endl;
    Client client(endpoint);
    std::string responseBody = client.getJSON(); 
    client.parseJSON(responseBody);
  //  client.hello();
    client.getAveAgePerCty();
    return 0;
}
