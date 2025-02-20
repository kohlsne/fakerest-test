#include "restclient.h"
#include "external/httplib.h"
#include "external/json.hpp"
#include <string>
#include <sstream> 
#include <stdexcept>
RestClient::RestClient() : endpoint("http://test.brightsign.io:3000"){};
RestClient::RestClient(const std::string &endpoint) : endpoint(endpoint){};
RestClient::~RestClient(){}

std::string RestClient::getJson()
{
	std::string responseBody = "";
	if (endpoint.empty())
	{
		std::cout << "No Endpoint found\n";
	}
	// HTTP
	httplib::Client httpCli(endpoint);
	if (auto res = httpCli.Get("/"))
	{
		auto err = res.error();
		if (err != httplib::Error::Success){
			std::cout << "HTTP error: " << httplib::to_string(err) << std::endl;
			throw std::runtime_error( "HTTP error: " + httplib::to_string(err));
		}else{
			responseBody = res->body;
		}
	}
	else
	{
		throw std::runtime_error( "Invalid Endpoint\n");
	}
	return responseBody;
}


void RestClient::parseJson(const std::string &responseBody)
{
	std::stringstream ss(responseBody);
	std::string line;
	unsigned int line_num = 1;
	//Parse line by line
	while (std::getline(ss, line))
	{
		nlohmann::json j_user;
		try{
			j_user = nlohmann::json::parse(line);
		} catch (nlohmann::json::parse_error& e){
			throw std::runtime_error( "Error Parsing Json on line: " + std::to_string(line_num) + "\n" + line);
		}
		// Aggregate City Data
		if (mapCityData.find(j_user["city"]) == mapCityData.end())
		{
			struct CityData cityData{
				.ageSum = j_user["age"],
				.numOfUsers = 1,
				.friendsSum = static_cast<unsigned int>(j_user["friends"].size()),
				.friendsMax = static_cast<unsigned int>(j_user["friends"].size()),
				.idWithMostFriends = j_user["id"].get<unsigned int>(),
				.userWithMostFriends = j_user["name"]};
			mapCityData.insert({j_user["city"], cityData});
		}
		else
		{
			mapCityData[j_user["city"]].numOfUsers++;
			mapCityData[j_user["city"]].ageSum += j_user["age"].get<unsigned int>();
			mapCityData[j_user["city"]].friendsSum += j_user["friends"].size();
			if (mapCityData[j_user["city"]].friendsMax < j_user["friends"].size())
			{
				mapCityData[j_user["city"]].friendsMax = j_user["friends"].size();
				mapCityData[j_user["city"]].userWithMostFriends = j_user["name"];
				mapCityData[j_user["city"]].idWithMostFriends = j_user["id"];
			}
		}
		// Map Name and frequency
		if (mapFirstName.find(j_user["name"]) == mapFirstName.end())
		{
			mapFirstName.insert({j_user["name"], 1});
		}
		else
		{
			mapFirstName[j_user["name"]]++;
		}
		// Map Hobby and frequency
		for (unsigned int friendIndex = 0; friendIndex < j_user["friends"].size(); friendIndex++)
		{
			for (unsigned int hobbyIndex = 0; hobbyIndex < j_user["friends"][friendIndex]["hobbies"].size(); hobbyIndex++)
			{
				if (mapHobbies.find(j_user["friends"][friendIndex]["hobbies"][hobbyIndex]) == mapHobbies.end())
				{
					mapHobbies.insert({j_user["friends"][friendIndex]["hobbies"][hobbyIndex], 1});
				}
				else
				{
					mapHobbies[j_user["friends"][friendIndex]["hobbies"][hobbyIndex]]++;
				}
			}
		}
		line_num++;
	}
	return;
}

std::string RestClient::getAveAgePerCty()
{
	nlohmann::json j_answer;
	for (const auto &cityData : mapCityData)
	{
		float averageAge = static_cast<float>(cityData.second.ageSum) / cityData.second.numOfUsers;
		j_answer.push_back({"city", cityData.first, "average age", averageAge});
	}
	return j_answer.dump();
}
std::string RestClient::getAveNumOfFriendsPerCty()
{
	nlohmann::json j_answer;
	for (const auto &cityData : mapCityData)
	{
		float averageNumFriends = static_cast<float>(cityData.second.friendsSum) / cityData.second.numOfUsers;
		j_answer.push_back({"city", cityData.first, "average num friends", averageNumFriends});
	}
	return j_answer.dump();
}
std::string RestClient::getTopFriendsUserPerCty()
{
	nlohmann::json j_answer;
	for (const auto &cityData : mapCityData)
	{ 
		j_answer.push_back({"city", cityData.first,"id", cityData.second.idWithMostFriends,"name", cityData.second.userWithMostFriends});
	}
	return j_answer.dump();
}
std::string RestClient::getMostCommonName()
{
	std::vector<std::string> keys;
	unsigned int max = 0;
	for (const auto &firstName : mapFirstName)
	{ 
		if (firstName.second > max){
			max = firstName.second;
			keys.clear();
			keys.push_back(firstName.first);
		}
		else if (firstName.second == max){
			keys.push_back(firstName.first);
		}
	}
	nlohmann::json j_answer;
	for (std::string key : keys){
		j_answer.push_back({"name", key});
	}
	return j_answer.dump();
}
std::string RestClient::getMostCommonHobby()
{
	std::vector<std::string> keys;
	unsigned int max = 0;
	for (const auto &hobby : mapHobbies)
	{ 
		if (hobby.second > max){
			max = hobby.second;
			keys.clear();
			keys.push_back(hobby.first);
		}
		else if (hobby.second == max){
			keys.push_back(hobby.first);
		}
	}
	nlohmann::json j_answer;
	for (std::string key : keys){
		j_answer.push_back({"hobbies", key});
	}
	return j_answer.dump();
}

std::string RestClient::getQueryResults(Query query){
	std::string results;
	switch (query){
		case Query::AVE_AGE_PER_CTY:
			results = getAveAgePerCty();
			break;
		case Query::AVE_NUM_FRIENDS_PER_CTY:
			results = getAveNumOfFriendsPerCty();
			break;
		case Query::USER_MOST_FRIENDS_PER_CTY:
			results = getTopFriendsUserPerCty();
			break;
		case Query::MOST_COMMON_FIRST_NAME:
			results = getMostCommonName();
			break;
		case Query::MOST_COMMON_HOBBY:
			results = getMostCommonHobby();
			break;
		default: 
			std::cout << "Invalid Query\n";
			break;
	}
	return results;
}

