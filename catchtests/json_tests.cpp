#include<catch.h>
#include<json_cpp.h>
#include<iostream>
#include<sstream>
#include <cstring>

using namespace json_cpp;
using namespace std;

TEST_CASE("basic wrapper"){
    int v = 50;
    Json_object_wrapper<int> i(v);
    string s = "25";
    stringstream ist(s);
    ist >> i;
    stringstream o;
    o << i;
    string r;
    o >> r;
    CHECK(v==25);
    CHECK(r=="25");
}

TEST_CASE("basic const wrapper bool"){
    const bool v = false;
    auto i = json_cpp::Json_object_wrapper<bool>(v);

    stringstream o;
    o << i;
    string r;
    o >> r;
    CHECK(r=="0");

    string s = "1";
    stringstream ist(s);
    CHECK_THROWS(ist >> i);
}

TEST_CASE("basic enum wrapper"){
    enum Enum{
        a,b,c
    };
    Enum v = b;
    auto i = json_cpp::Json_object_wrapper<Enum>(v);
    stringstream o;
    o << i;
    string r;
    o >> r;
    CHECK(r=="1");
    string s = "2";
    stringstream ist(s);
    ist >> i;
    CHECK(v==Enum::c);
}


TEST_CASE("basic wrapper string"){
    string v = "hello";
    Json_object_wrapper<string> i(v);
    string s = "\"bye\"";
    stringstream ist(s);
    ist >> i;
    stringstream o;
    o << i;
    string r;
    o >> r;
    CHECK(v=="bye");
    CHECK(r=="\"bye\"");
}

TEST_CASE("json builder"){
    int i = 10;
    string s = "hello";
    Json_builder jb;
    Add_member(i);
    Add_member(s);
    string json = "{\"i\":20,\"s\":\"bye\"}";
    stringstream ist(json);
    ist >> jb;
    CHECK(i==20);
    CHECK(s=="bye");
    stringstream o;
    o << jb;
    string r;
    o >> r;
    CHECK(r==json);

}


TEST_CASE("json object"){
    struct Test_json_object: Json_object {
        Test_json_object(int i, string s): i(i), s(s) {}
        int i;
        string s;
        Json_object_members({
                             Add_member(i);
                             Add_member(s);
                         })
    };
    Test_json_object tjo {1,"hello"};
    string json = "{\"i\":20,\"s\":\"bye\"}";
    stringstream ist(json);
    ist >> tjo;
    stringstream o;
    o << tjo;
    string r;
    o >> r;
    CHECK(r==json);
    const Test_json_object tjo2{1,"hello"};
    stringstream o2;
    o2 << tjo2;
    string r2;
    o2 >> r2;
    CHECK(r2=="{\"i\":1,\"s\":\"hello\"}");
}

TEST_CASE("json nested object"){
    struct Test_member: Json_object {
        Test_member(int i, string s): i(i), s(s) {}
        int i;
        string s;
        Json_object_members({
            Add_member(i);
            Add_member(s);
        })
    };
    struct Test_json_object: Json_object {
        Test_json_object(int i, string s, Test_member m): i(i), s(s), m(m) {}
        int i;
        string s;
        Test_member m;
        Json_object_members({
                             Add_member(i);
                             Add_member(s);
                             Add_member(m);
                         })
    };
    Test_member tm {20,"bye"};
    Test_json_object tjo {1,"hello", {20,"bye"}};
    string json = "{\"i\":20,\"s\":\"bye\",\"m\":{\"i\":200,\"s\":\"hello\"}}";
    stringstream ist(json);
    ist >> tjo;
    stringstream o;
    o << tjo;
    string r;
    o >> r;
    CHECK(r==json);
}

TEST_CASE("int list"){
    Json_vector<int> i;
    i.push_back(1);
    i.push_back(2);
    i.push_back(3);
    string json = "[4,5,6]";
    stringstream ist(json);
    ist >> i;
    stringstream o;
    o << i;
    string r;
    o >> r;
    CHECK(r==json);
}

TEST_CASE("double list"){
    Json_vector<double> i;
    i.push_back(-1.5);
    i.push_back(2.5);
    i.push_back(3.5);
    string json = "[-4.5,5.5,6.5]";
    stringstream ist(json);
    ist >> i;
    stringstream o;
    o << i;
    string r;
    o >> r;
    CHECK(r==json);
}

TEST_CASE("bool list"){
    Json_vector<bool> i;
    i.push_back(true);
    i.push_back(false);
    i.push_back(true);
    string json = "[0,1,0]";
    stringstream ist(json);
    ist >> i;
    stringstream o;
    o << i;
    string r;
    o >> r;
    CHECK(r==json);
}
TEST_CASE("list slice"){
    Json_vector<int> v;
    for (int i=0;i<100; i++){
        v.push_back(i+100);
    }
    string s1;
    s1 << v.slice(20);
    string s2;
    s2 << v.slice(20,30);
    CHECK (s1 == "[100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119]");
    CHECK (s2 == "[120,121,122,123,124,125,126,127,128,129]");
}

TEST_CASE("object list"){
    struct Test_json_object: Json_object {
        Test_json_object(){};
        Test_json_object(int i, string s): i(i), s(s) {}
        int i;
        string s;
        Json_object_members({
                             Add_member(i);
                             Add_member(s);
                         })
    };
    Json_vector<Test_json_object> i;
    i.push_back({1,"1"});
    i.push_back({2,"2"});
    i.push_back({3,"3"});
    string json = "[{\"i\":4,\"s\":\"4\"},{\"i\":5,\"s\":\"5\"},{\"i\":6,\"s\":\"6\"}]";
    stringstream ist(json);
    ist >> i;
    stringstream o;
    o << i;
    string r;
    o >> r;
    CHECK(r==json);
}

TEST_CASE("nested object list"){
    struct Test_member: Json_object {
        Test_member(){};
        Test_member(int i, string s): i(i), s(s) {}
        int i;
        string s;
        Json_object_members({
                             Add_member(i);
                             Add_member(s);
                         })
    };
    struct Test_json_object: Json_object {
        Test_json_object(){};
        Test_json_object(int i, string s, Test_member m): i(i), s(s), m(m) {}
        int i;
        string s;
        Test_member m;
        Json_object_members({
                             Add_member(i);
                             Add_member(s);
                             Add_member(m);
                         })
    };
    Test_json_object o {1,"1",{2, "2"}};
    Json_vector<Test_json_object> i;
    i.push_back({1,"1",{1,"1"}});
    i.push_back({2,"2",{1,"1"}});
    i.push_back({3,"3",{1,"1"}});
    string json = "[{\"i\":4,\"s\":\"4\",\"m\":{\"i\":400,\"s\":\"400\"}},{\"i\":5,\"s\":\"5\",\"m\":{\"i\":410,\"s\":\"410\"}},{\"i\":6,\"s\":\"6\",\"m\":{\"i\":420,\"s\":\"420\"}}]";
    stringstream ist(json);
    ist >> i;
    stringstream ou;
    ou << i;
    string r;
    ou >> r;
    CHECK(r==json);
}

TEST_CASE("json object from string"){
    struct Test_json_object: Json_object {
        Test_json_object(int i, string s): i(i), s(s) {}
        int i;
        string s;
        Json_object_members({
                             Add_member(i);
                             Add_member(s);
                         })
    };
    Test_json_object tjo {1,"hello"};
    string json = "{\"i\":20,\"s\":\"bye\"}";
    json >> tjo;
    string r;
    r << tjo;
    CHECK(r==json);
    const Test_json_object tjo2{1,"hello"};
    stringstream o2;
    o2 << tjo2;
    string r2;
    o2 >> r2;
    CHECK(r2=="{\"i\":1,\"s\":\"hello\"}");
}

TEST_CASE("json object from char array"){
    struct Test_json_object: Json_object {
        Test_json_object(int i, string s): i(i), s(s) {}
        int i;
        string s;
        Json_object_members({
                             Add_member(i);
                             Add_member(s);
                         })
    };
    Test_json_object tjo {1,"hello"};
    "{\"i\":20,\"s\":\"bye\"}" >> tjo;
    string r;
    r << tjo;
    CHECK(r=="{\"i\":20,\"s\":\"bye\"}");
    const Test_json_object tjo2{1,"hello"};
    stringstream o2;
    o2 << tjo2;
    string r2;
    o2 >> r2;
    CHECK(r2=="{\"i\":1,\"s\":\"hello\"}");
}

TEST_CASE("Uri load") {
    Json_URI u1("https://www.google.com");
    CHECK(u1.protocol == Json_URI::Protocol::https);
    CHECK(u1.domain == "www.google.com");
    CHECK(u1.query_string == "");
    CHECK(u1.port == 443);
    string url;
    url = u1.url();
    CHECK(url == "https://www.google.com:443/");

    Json_URI u2("http://www.google.com:65/query123?123/1");
    CHECK(u2.protocol == Json_URI::Protocol::http);
    CHECK(u2.domain == "www.google.com");
    CHECK(u2.query_string == "query123?123/1");
    CHECK(u2.port == 65);
    url = u2.url();
    CHECK(url == "http://www.google.com:65/query123?123/1");
}

TEST_CASE("load json object from url"){
    struct Test_obj : Json_object{
        Json_object_members({
            Add_member(member1);
            Add_member(member2);
        })
        string member1;
        int member2{};
    };
    Test_obj test_obj;
    string url ("https://raw.githubusercontent.com/germanespinosa/cellworld_data/master/test.json");
    auto r = Json_web_get(url);
    r.get_stream() >> test_obj;
    CHECK(test_obj.member1 == "value");
    CHECK(test_obj.member2 == 5);
}

TEST_CASE("pp"){
    auto r = Json_web_get("https://raw.githubusercontent"
                                    ".com/germanespinosa/cellworld_data/master/world/world_0_0");
    CHECK(25416 == r.size());
}

TEST_CASE("fix pointer"){
    struct Test_object : Json_object{
        Test_object():Json_object(){}
        int a = 10,b = 20;
        Json_object_members({
            Add_member(a);
            Add_member(b);
        })
    };
    Test_object *t2 = new((Test_object *)malloc(sizeof(Test_object) + 4)) Test_object();
    stringstream o2;
    o2 << (*t2);
    CHECK(o2.str() == "{\"a\":10,\"b\":20}");
}

TEST_CASE("json_create"){
    struct Test_obj : Json_object{
        Json_object_members({
                                Add_member(member1);
                                Add_member(member2);
                            })
        string member1;
        int member2{};
    };
    ;
    string url ("https://raw.githubusercontent.com/germanespinosa/cellworld_data/master/test.json");
    auto test_obj = Json_create<Test_obj>(Json_web_get(url).get_stream());
    CHECK(test_obj.member1 == "value");
    CHECK(test_obj.member2 == 5);
}

TEST_CASE("check 404"){
    string url ("https://bogus-url.com");
    CHECK_THROWS(Json_web_get(url));
}

TEST_CASE("check needs quotes") {
    string a;
    int b;
    CHECK(needs_quotes<string>(a) == true);
    CHECK(needs_quotes<int>(b) == false);
    CHECK(Json_needs_quotes(a) == true);
    CHECK(Json_needs_quotes(b) == false);
}

TEST_CASE("dictionary") {
    string json = "{\"i\":20,\"s\":\"bye\",\"m\":{\"i\":200,\"s\":\"hello\"}}";
    stringstream ist(json);
    Json_dictionary dict;
    json >> dict;
    CHECK(dict.size() == 3);
    CHECK(dict.keys[0] == "i");
    CHECK(dict.keys[1] == "s");
    CHECK(dict.keys[2] == "m");
    CHECK(dict["i"].value=="20");
    CHECK(dict["s"].value=="bye");
    CHECK(dict["s"].require_quotes==true);
    CHECK(dict["m"].value=="{\"i\":200,\"s\":\"hello\"}");
    CHECK(dict["m"].to_dict()["i"].value=="200");
    CHECK(dict["m"].to_dict()["s"].value=="hello");
    CHECK(dict["m"].to_dict()["s"].require_quotes==true);
    CHECK(dict["m"].to_dict().keys[0] == "i");
    CHECK(dict["m"].to_dict().keys[1] == "s");
    stringstream ss;
    ss << dict;
    CHECK(ss.str()== "{\"i\":20,\"s\":\"bye\",\"m\":{\"i\":200,\"s\":\"hello\"}}");
    stringstream ss2;
    ss2 << dict["m"].to_dict();
    CHECK(ss2.str()== "{\"i\":200,\"s\":\"hello\"}");

}
