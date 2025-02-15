#ifndef CLIENT_H
#define CLIENT_H

#include "sqlite3.h"
#include <string>
#include <iostream>


namespace StatusCode { // Or it could be a class instead of a namespace
    enum Code {
        OK_200 = 200,
        Created_201 = 201,
        BadRequest_400 = 400,
        Unauthorized_401 = 401,
        NotFound_404 = 404,
        InternalServerError_500 = 500,
        // ... other status codes ...
    };
    // You might have helper functions or constants related to StatusCode here as well.
    // For example, a function to get a string representation of a StatusCode.
}

class Client{
	private:
	    sqlite3* db;
	    std::string endpoint;
	public:
		Client() = delete;
		Client(const std::string& endpoint);
		~Client();
		std::string getJSON();
		void parseJSON(const std::string& responseBody);




	


};


#endif
