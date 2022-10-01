#include <catch.h>
#include <json_cpp/python/json_python_object.h>
#include <json_cpp/python/json_python_value.h>
#include <iostream>
#include <cstring>

using namespace json_cpp;
using namespace std;

TEST_CASE("Json_value_bool"){
    Python_value v(json_cpp::Python_type::Bool, true);
    CHECK(v.mandatory == true);
    CHECK(v.get_python_type() == "bool");
    CHECK(v.bool_value == false);
}