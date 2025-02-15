#include "client.h"
#include "external/httplib.h"
#include "external/json.hpp"
#include <typeinfo>
#include <string>
#include <sstream> // For std::stringstream
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
	std::stringstream ss(responseBody); // Create a stringstream from the string
   	std::string line;
    	std::cout << "Parsed lines:\n";
    	std::getline(ss, line);
        std::cout << line << std::endl;	
	nlohmann::json j_user = nlohmann::json::parse(line);
	//Aggregate City Data
        if (mapCityData.find(j_user["city"]) == mapCityData.end()){
    		struct CityData cityData{
			.ageSum=j_user["age"],
			.numOfUsers=1,
			.friendsMax=static_cast<unsigned int>(j_user["friends"].size()),
			.userWithMostFriends=j_user["name"]};
		mapCityData.insert({j_user["city"], cityData});
	}else{
		mapCityData[j_user["city"]].numOfUsers++;
		mapCityData[j_user["city"]].ageSum+=j_user["age"].get<unsigned int>();
		if (mapCityData[j_user["city"]].friendsMax < j_user["friends"].size()){
			mapCityData[j_user["city"]].friendsMax = j_user["friends"].size();
			mapCityData[j_user["city"]].userWithMostFriends = j_user["name"];
		}
	}
	std::cout << "city data complete" << std::endl;
	//Map Name and frequency
	if (mapFirstName.find(j_user["name"]) == mapFirstName.end()){
		mapFirstName.insert({j_user["name"],1});
	} else{
		mapFirstName[j_user["name"]]++;
	}
	std::cout << "Name complete" << std::endl;
	//Map Hobby and frequency
	for (unsigned int friendIndex = 0; friendIndex < j_user["friends"].size(); friendIndex++){
		for (unsigned int hobbyIndex = 0; hobbyIndex < j_user["friends"][friendIndex]["hobbies"].size(); hobbyIndex++){
			if (mapHobbies.find(j_user["friends"][friendIndex]["hobbies"][hobbyIndex]) == mapHobbies.end()){
				mapHobbies.insert({j_user["friends"][friendIndex]["hobbies"][hobbyIndex] ,1});
			} else{
				mapHobbies[j_user["friends"][friendIndex]["hobbies"][hobbyIndex]]++;
			}
		}
	}
	std::cout << "hobby data complete" << std::endl;
	std::cout << std::setw(4) << j_user << "\n\n";
//	std::cout << j_complete.size() << std::endl;
//	std::cout << j_complete["name"] << std::endl;
//	std::cout << j_complete["friends"] << std::endl;
//	std::cout << j_complete["friends"].size() << std::endl;
//	std::cout << j_complete["friends"][0] << std::endl;
//	std::cout << j_complete["friends"][0].size() << std::endl;
//	std::cout << j_complete["friends"][0]["name"]<< std::endl;
//	std::cout << j_complete["friends"][0]["hobbies"]<< std::endl;
	return;
}
void hello(){
	std::cout << "Here we go!\n";
}
void getAveAgePerCty(){
	std::cout << "Inside this method\n";

}
//void getAverageAgePerCity(){
	//nlohmann::json j_answer;
//	for (const auto& cityData : mapCityData){
//		long averageAge = static_cast<float>(cityData.second.ageSum)/cityData.second.numOfUsers;
//		j_answer.push_back{"city", cityData.first, "average age", averageAge};
//	}
	//return j_answer.dump();
//	std::cout << "Hello\n";
//	return;
//}
//std::string getAverageNumOfFriendsPerCity(){
///	return "";
//}
//std::string getTopFriendsUserPerCity(){
//	return "";
//}
//std::string getMostCommonName(){
//	return "";
//}
//std::string getMostCommonHobby(){
//	return "";
//}

