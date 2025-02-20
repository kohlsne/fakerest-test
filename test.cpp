#include "restclient.h" 
#include "external/httplib.h"
#include "external/acutest.h"

//test httplib get webdata
void json_get_success(void)
{
    RestClient restClient("http://test.brightsign.io:3000");
    std::string responseBody = restClient.getJson();
    TEST_ASSERT(!responseBody.empty());
}
//test httplib throw an exception if bad endpoint
void invalid_endpoint(void)
{
    RestClient restClient("not_an_enpoint");
    TEST_EXCEPTION(restClient.getJson(),std::runtime_error);
}
//test parser to throw an exception if bad format
void parse_invalid_json(void)
{
    RestClient restClient;
    std::string responseBody = "invalid format";
    TEST_EXCEPTION(restClient.parseJson(responseBody),std::runtime_error);
}
//test if can parse and calcuate queries with one object
void parse_json_object(void)
{
    RestClient restClient;
    std::string responseBody = "{\"id\":0,\"name\":\"Elijah\",\"city\":\"Austin\",\"age\":78,\"friends\":[{\"name\":\"Michelle\",\"hobbies\":[\"Watching Sports\",\"Traveling\",\"Skiing & Snowboarding\"]},{\"name\":\"Robert\",\"hobbies\":[\"Traveling\",\"Video Games\"]}]}";
    restClient.parseJson(responseBody);
    TEST_ASSERT(restClient.getQueryResults(Query::AVE_AGE_PER_CTY) == "[[\"city\",\"Austin\",\"average age\",78.0]]");
    TEST_ASSERT(restClient.getQueryResults(Query::AVE_NUM_FRIENDS_PER_CTY) == "[[\"city\",\"Austin\",\"average num friends\",2.0]]");
    TEST_ASSERT(restClient.getQueryResults(Query::USER_MOST_FRIENDS_PER_CTY) == "[[\"city\",\"Austin\",\"id\",0,\"name\",\"Elijah\"]]");
    TEST_ASSERT(restClient.getQueryResults(Query::MOST_COMMON_FIRST_NAME) == "[[\"name\",\"Elijah\"]]");
    TEST_ASSERT(restClient.getQueryResults(Query::MOST_COMMON_HOBBY) == "[[\"hobbies\",\"Traveling\"]]");
}
//test if can parse and calcuate queries with multiple objects
void parse_json_objects(void)
{
    RestClient restClient;
    std::string responseBody = "{\"id\":0,\"name\":\"Elijah\",\"city\":\"Austin\",\"age\":30,\"friends\":[{\"name\":\"Michelle\",\"hobbies\":[\"Watching Sports\",\"Traveling\",\"Skiing & Snowboarding\"]},{\"name\":\"Robert\",\"hobbies\":[\"Surfing\",\"Video Games\"]}]}\n{\"id\":1,\"name\":\"Michael\",\"city\":\"St. Louis\",\"age\":60,\"friends\":[{\"name\":\"Mateo\",\"hobbies\":[\"Movie Watching\",\"Collecting\"]},{\"name\":\"Chris\",\"hobbies\":[\"Housework\",\"Bicycling\",\"Walking\"]}]}\n{\"id\":2,\"name\":\"Doug\",\"city\":\"Austin\",\"age\":60,\"friends\":[{\"name\":\"Michelle\",\"hobbies\":[\"Watching Sports\",\"Traveling\",\"Skiing & Snowboarding\"]}]}";
    restClient.parseJson(responseBody);
    TEST_ASSERT(restClient.getQueryResults(Query::AVE_AGE_PER_CTY) == "[[\"city\",\"St. Louis\",\"average age\",60.0],[\"city\",\"Austin\",\"average age\",45.0]]");
    TEST_ASSERT(restClient.getQueryResults(Query::AVE_NUM_FRIENDS_PER_CTY) == "[[\"city\",\"St. Louis\",\"average num friends\",2.0],[\"city\",\"Austin\",\"average num friends\",1.5]]");
    TEST_ASSERT(restClient.getQueryResults(Query::USER_MOST_FRIENDS_PER_CTY) == "[[\"city\",\"St. Louis\",\"id\",1,\"name\",\"Michael\"],[\"city\",\"Austin\",\"id\",0,\"name\",\"Elijah\"]]");
    TEST_ASSERT(restClient.getQueryResults(Query::MOST_COMMON_FIRST_NAME) == "[[\"name\",\"Doug\"],[\"name\",\"Michael\"],[\"name\",\"Elijah\"]]");
    TEST_ASSERT(restClient.getQueryResults(Query::MOST_COMMON_HOBBY) == "[[\"hobbies\",\"Skiing & Snowboarding\"],[\"hobbies\",\"Traveling\"],[\"hobbies\",\"Watching Sports\"]]");
}
//use in acutest.h, list of functions to test
TEST_LIST = {
    { "json get success", json_get_success },
    { "invalid endpoint", invalid_endpoint },
    { "parse invalid json", parse_invalid_json },
    { "parse json object", parse_json_object },
    { "parse json objects", parse_json_objects },
    { NULL, NULL }     /* zeroed record marking the end of the list */

};