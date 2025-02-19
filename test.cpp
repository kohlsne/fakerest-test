#include "restclient.h" 
#include "external/httplib.h"
#include "external/acutest.h"


void test_success(void)
{
    /* Do nothing */
}


void json_get_success(void)
{
    RestClient restClient("http://test.brightsign.io:3000",true);
    // std::string responseBody = restClient.getJson();
    // TEST_ASSERT(!responseBody.empty());
}

void invalid_endpoint(void)
{
    // RestClient restClient("not_an_enpoint",true);
    // std::string responseBody = restClient.getJson();
    // TEST_ASSERT(!responseBody.empty());
}

TEST_LIST = {
    { "success", test_success },
    { "success", json_get_success },
    { "success", invalid_endpoint },

    { NULL, NULL }     /* zeroed record marking the end of the list */

};