#include <iostream>
#include <string>
#include <json_cpp/json_web_request.h>
#include <cstring>

using namespace std;
namespace json_cpp {
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
        cout << query_string << endl;
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

    size_t ignore_data(void *, size_t size, size_t nmemb, void *) { return size * nmemb; }
    size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
        auto r = (Json_web_response *)userp;
        r->push_data((char *) buffer, size * nmemb);
        return size * nmemb;
    }

    Json_web_response Json_web_request::get_response() {
        auto url = uri.url();
        CURL *curl = curl_easy_init();
        if(!curl) throw logic_error("failed to create curl object");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HEADER, 1);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ignore_data);

        struct curl_slist *headers=NULL;
        curl_slist_append(headers, "Cache-Control: max-age=0");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        CURLcode res;
        res = curl_easy_perform(curl);
        curl_off_t ct;
        res = curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &ct);
        if (res != CURLE_OK) throw logic_error("failed to retrieve response info");
        if (ct < 0) throw logic_error("failed to retrieve '" + url + "'");

        curl_easy_cleanup(curl);

        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        Json_web_response r(ct);
        auto v = (void *) &r;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, v);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) throw logic_error("failed to retrieve content from '" + url + "'");

        curl_easy_cleanup(curl);
        return r;
    }

    Json_web_request::Json_web_request(Json_URI uri) : uri(uri) {}
}