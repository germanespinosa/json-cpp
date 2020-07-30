#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <json_cpp/json_base.h>
#include <json_cpp/json_web_request.h>

using namespace std;
namespace json_cpp {

    size_t Json_web_request::_json_callback(char* buf, size_t size, size_t nmemb, void *request_ptr)
    {
        auto *request = (Json_web_request *) request_ptr;
        request->_buffer.set_mem(buf ,size * nmemb);
        request->_json_stream_ready = true;
        return size * nmemb;
    }

    Json_web_request::Json_web_request(const Json_URI &uri) :
    istream(&_buffer),
    _buffer (){
        CURLcode res;
        _curl_handler = curl_easy_init();
        if(_curl_handler) {
            string url = uri.url();
            curl_easy_setopt(_curl_handler, CURLOPT_URL, url.c_str());
            curl_easy_setopt(_curl_handler, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(_curl_handler, CURLOPT_WRITEFUNCTION, _json_callback);
            curl_easy_setopt(_curl_handler, CURLOPT_WRITEDATA, (void *)this);
            _json_stream_ready = false;
            res = curl_easy_perform(_curl_handler);
            if(res != CURLE_OK) {
                curl_easy_cleanup(_curl_handler);
            }
            while (!_json_stream_ready);
        }
    }

    Json_web_request::~Json_web_request() {
        if (_json_stream_ready) {
            curl_easy_cleanup(_curl_handler);
        }
    }

    std::string Json_web_request::read() const {
        if (!_json_stream_ready) throw logic_error("web request did not finished");
        stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(ostream &o, const Json_web_request &jwr) {
        if (!jwr._json_stream_ready) throw logic_error("web request did not finished");
        o << jwr;
        return o;
    }

    Json_URI::Json_URI(const std::string &url) {
        stringstream ss (url);
        string part;
        getline(ss, part, ':');
        if ( part == "https") protocol = https;
        else if ( part == "http") protocol = http;
        else throw logic_error("supported protocols are http and https");
        getline(ss, part, '/');
        if (!part.empty()) throw logic_error("url format error");
        getline(ss, part, '/');
        if (!part.empty()) throw logic_error("url format error");
        getline(ss, part, '/');
        if (part.empty()) throw logic_error("url format error");
        if (part.find(':') !=std::string::npos){
            stringstream sd (part);
            getline(sd, domain, ':');
            string port_s;
            getline(sd, port_s, '/');
            port = stoi(port_s);
        } else {
            domain = part;
            port = protocol == http?80:443;
        }
        getline(ss, query_string);
    }

    Json_URI::Json_URI() {
        protocol = https;
        port = 443;
    }

    std::string Json_URI::url() const {
        stringstream ss;
        if (protocol == http) ss << "http";
        else ss <<"https";
        ss << "://" << domain << ":" << port << "/" << query_string;
        return ss.str();
    }

    std::ostream &operator<<(ostream &o, const Json_URI &uri) {
        o << uri.url();
        return o;
    }

    Json_URI::operator std::string() const {
        return this->url();
    }
}