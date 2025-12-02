#include <iostream>

#include "CurlHelper/CurlHelper.hpp"

int main()
{
    CurlHelper curl;

    curl.httpGet("localhost:8080/weather?latitude=59.85&longitude=44.44");

    return 0;
}