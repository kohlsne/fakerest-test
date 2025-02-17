#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>


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
		bool verbosity;

	    struct CityData{
		    unsigned int ageSum = 0;
		    unsigned int numOfUsers = 0;
			unsigned int friendsSum = 0;
		    unsigned int friendsMax = 0;
			unsigned int idWithMostFriends = 0;
		    std::string userWithMostFriends;
	    };



	    struct JsonObject{
			struct FriendObject{
				std::string name;
				std::vector<std::string> hobbies;
 	    	};
		    unsigned int id = 0;
			unsigned int age = 0;
			std::string name;
			std::string city;
			std::vector<FriendObject> friends;
	    };

	    std::unordered_map<std::string,struct CityData> mapCityData;
	    std::unordered_map<std::string,int> mapFirstName;
	    std::unordered_map<std::string,int> mapHobbies;

		JsonObject parseObject(const std::string& line);
		std::string getAveAgePerCty();
		std::string getAveNumOfFriendsPerCty();
		std::string getTopFriendsUserPerCty();
		std::string getMostCommonName();
		std::string getMostCommonHobby();
	public:
		RestClient() = delete;
		RestClient(const std::string& endpoint, const bool& verbosity);
		~RestClient();
		
		std::string getJson();
		void parseJson(const std::string& responseBody);
		void validateJson(const std::string& responseBody);
		std::string getQueryResults(Query query);





	


};


#endif
