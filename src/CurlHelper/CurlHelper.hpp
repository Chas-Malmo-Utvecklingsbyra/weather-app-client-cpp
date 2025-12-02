#ifndef __CurlHelper_hpp__
#define __CurlHelper_hpp__

#include <string>

#include <curl/curl.h>

class CurlHelper
{
    private:
        CURL* curlPtr;

    public:
        CurlHelper();

        void httpGet(const std::string &url);
        
        ~CurlHelper();

};

#endif