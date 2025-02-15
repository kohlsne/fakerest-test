#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>
#include <unordered_map>

class Client{
	private:
	    std::string endpoint;

	    struct CityData{
		    unsigned int ageSum = 0;
		    unsigned int numOfUsers = 0;
		    unsigned int friendsMax = 0;
		    std::string userWithMostFriends;
	    };
	    std::unordered_map<std::string,struct CityData> mapCityData;
	    std::unordered_map<std::string,int> mapFirstName;
	    std::unordered_map<std::string,int> mapHobbies;
	public:
		Client() = delete;
		Client(const std::string& endpoint);
		~Client();
		
		std::string getJSON();
		void parseJSON(const std::string& responseBody);
		void hello();
		void getAveAgePerCty();
//		void getAverageAgePerCity();
//		std::string getAverageNumOfFriendsPerCity();
//		std::string getTopFriendsUserPerCity();
//		std::string getMostCommonName();
//		std::string getMostCommonHobby();




	


};


#endif
