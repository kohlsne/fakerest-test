#ifndef REST_CLIENT_H
#define REST_CLIENT_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

//Specifies the Query
enum class Query { 
	NO_QUERY,
	AVE_AGE_PER_CTY, 
	AVE_NUM_FRIENDS_PER_CTY, 
	USER_MOST_FRIENDS_PER_CTY,
	MOST_COMMON_FIRST_NAME,
	MOST_COMMON_HOBBY
	};

class RestClient{
	private:
	    std::string endpoint;
		//updated as json is parsed line by line
	    struct CityData{
		    unsigned int ageSum = 0;
		    unsigned int numOfUsers = 0;
			unsigned int friendsSum = 0;
		    unsigned int friendsMax = 0;
			unsigned int idWithMostFriends = 0;
		    std::string userWithMostFriends = "";
	    };
		//contains aggregate of data by city
	    std::unordered_map<std::string,struct CityData> mapCityData;
		//contains frequency of first name
	    std::unordered_map<std::string,int> mapFirstName;
		//contains frquency of hobbies
	    std::unordered_map<std::string,int> mapHobbies;

		std::string getAveAgePerCty();
		std::string getAveNumOfFriendsPerCty();
		std::string getTopFriendsUserPerCty();
		std::string getMostCommonName();
		std::string getMostCommonHobby();
	public:
		RestClient();
		RestClient(const std::string& endpoint);
		~RestClient();
		
		//http client gets the json from the endpoint
		std::string getJson();
		// json is parsed and the memeber maps are updated
		void parseJson(const std::string& responseBody);
		// calculates query results from maps and returns result
		std::string getQueryResults(Query query);
};

#endif
