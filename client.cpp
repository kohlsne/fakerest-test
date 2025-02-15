#include "client.h"
#include "external/httplib.h"
#include <typeinfo>
#include <string>
Client::Client(const std::string& endpoint): endpoint(endpoint){
	std::cout << endpoint <<std::endl;
};

Client::~Client(){

}

std::string Client::getJSON(){
	std::string responseBody = "";
	if (endpoint.empty()){
	  std::cout<<"No Endpoint found\n";
	}
	// HTTP
	httplib::Client cli(endpoint);
	std::cout << "Client: " << typeid(cli).name() << std::endl;
	if (auto res = cli.Get("/")) {
    		auto err = res.error();
    		std::cout << "HTTP error: " << httplib::to_string(err) << std::endl;
		std::cout << "res: " << typeid(res).name() << std::endl;
		std::cout << "res->status: " << typeid(res->status).name() << std::endl;
		std::cout << "res->body: " << typeid(res->body).name() << std::endl;
		responseBody = res->body;
  	} else{
		std::cout << "Invalid Endpoint\n";
	}
	return responseBody;
}

void Client::parseJSON(const std::string& responseBody){

	return;
}
