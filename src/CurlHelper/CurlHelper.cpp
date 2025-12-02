#include "CurlHelper.hpp"


CurlHelper::CurlHelper()
{
    this->curlPtr = curl_easy_init();
}


void CurlHelper::httpGet(const std::string &url)
{
    curl_easy_setopt(this->curlPtr, CURLOPT_URL, url.c_str());

    curl_easy_perform(this->curlPtr);
}


CurlHelper::~CurlHelper()
{
    curl_easy_cleanup(this->curlPtr);
}