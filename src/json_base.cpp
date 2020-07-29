#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <json_cpp/json_base.h>
#include <curl/curl.h>


using namespace std;
namespace json_cpp {

    std::istream &operator>>(istream &i, Json_base &j) {
        j.json_parse(i);
        return i;
    }

    std::ostream &operator<<(ostream &o, const Json_base &j) {
        j.json_write(o);
        return o;
    }

    bool Json_base::load(const string &file_name) {
        std::ifstream file;
        file.open(file_name.c_str());
        if (!file.good()) return false;
        json_parse(file);
        return true;
    }

    bool Json_base::save(const string &file_name) const {
        std::ofstream file;
        file.open(file_name.c_str());
        if (!file.good()) return false;
        json_write(file);
        return true;
    }

    std::string &operator>>(string &i, Json_base &j) {
        std::stringstream ss(i);
        ss >> j;
        i = ss.str();
        return i;
    }

    std::string &operator<<(string &o, const Json_base &j) {
        std::stringstream ss(o);
        ss << j;
        o = ss.str();
        return o;
    }

    char *operator>>(char *s, Json_base &j) {
        string ss(s);
        ss>>j;
        return s;
    }

    const char *operator>>(const char *s, Json_base &j) {
        string ss(s);
        ss>>j;
        return s;
    }

    void Json_base::json_write(ostream &) const {

    }

    void Json_base::json_parse(istream &) {

    }

    size_t Json_base::_json_callback(char* buf, size_t size, size_t nmemb, void *)
    {
        string data;
        for (unsigned c = 0; c<size*nmemb; c++)
        {
            data.push_back(buf[c]);
        }
        return size * nmemb;
    }

    bool Json_base::load(Json_URI &uri) {
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if(curl) {
            string url = uri;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            /* example.com is redirected, so we tell libcurl to follow redirection */
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Json_base::_json_callback);
            /* Perform the request, res will get the return code */
            res = curl_easy_perform(curl);
            /* Check for errors */
            if(res != CURLE_OK) {
                curl_easy_cleanup(curl);
                return false;
            }
            /* always cleanup */
            curl_easy_cleanup(curl);
        }
        return true;
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

    Json_URI::operator string() const {
        stringstream ss;
        if (protocol == http) ss << "http";
        else ss <<"https";
        ss << "://" << domain << ":" << port << "/" << query_string;
        return ss.str();
    }
}