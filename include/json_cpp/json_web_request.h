#pragma once
#include <vector>
#include <iostream>
#include <curl/curl.h>

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
        explicit operator std::string() const;
        friend std::ostream & operator << (std::ostream & , const Json_URI &);
    };

    struct Json_web_request : public std::istream{
        ~Json_web_request() override;
        explicit Json_web_request(const Json_URI &);
        std::string read() const;
        friend std::ostream &operator<<(std::ostream &, const Json_web_request &);
    private:
        Json_web_request() = default;
        struct Buffer : public std::basic_streambuf<char> {
            Buffer() = default;
            void set_mem(const char *p, size_t l) {
                setg((char*)p, (char*)p, (char*)p + l);
            }
        };
        Buffer _buffer;
        CURL *_curl_handler;
        bool _json_stream_ready;
        static size_t _json_callback(char *, size_t, size_t, void *);

    };
}