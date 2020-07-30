#pragma once
#include <iostream>
#include <curl/curl.h>
#include <json_cpp/json_web_response.h>
#define Json_web_get(URL) json_cpp::Json_web_request(json_cpp::Json_URI(URL)).get_response()

namespace json_cpp {

    struct Json_URI {
        Json_URI();
        explicit Json_URI(const std::string &);
        enum Protocol{
            http,
            https
        };
        Protocol protocol;
        std::string domain;
        unsigned int port;
        std::string query_string;
        std::string url() const;
        friend std::ostream & operator << (std::ostream & , const Json_URI &);
    };

    struct Json_web_request {
        explicit Json_web_request(Json_URI);
        Json_web_response get_response();
    private:
        Json_URI uri;
    };
}