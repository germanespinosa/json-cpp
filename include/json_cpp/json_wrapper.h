#pragma once
#include <iostream>
#include <json_cpp/json_util.h>
#include <json_cpp/json_base.h>
#include <memory>
#include <optional>

#define Json_wrap(X) std::move(json_cpp::Json_wrapper<decltype(X)>(X).get_unique_ptr())

namespace json_cpp {

    struct Json_wrapped : Json_base{
        virtual std::unique_ptr<Json_wrapped> get_unique_ptr() = 0;
        virtual std::unique_ptr<Json_wrapped> get_unique_ptr() const = 0;
    };

    template <class T>
    struct Json_wrapper : Json_wrapped{
        explicit Json_wrapper<T>(T &value) : _value (value), _cvalue (value){}
        explicit Json_wrapper<T>(const T &value) : _cvalue (value){}

        void json_parse(std::istream &i) override{
            if (!_value) throw std::logic_error("cannot write a const variable");
            auto &r = _value.value().get();
            if constexpr (std::is_same_v<T, std::string>) {
                r = Json_util::read_string(i);
            } else {
                Json_util::skip_blanks(i);
                i >> r;
            }
        }
        void json_write(std::ostream &o) const override{
            auto &r = _cvalue.get();
            if constexpr (std::is_same_v<T, std::string>) {
                o << '"' << r << '"';
            } else {
                o << r;
            }
        }
        std::unique_ptr<Json_wrapped> get_unique_ptr() const override {
            return std::make_unique<Json_wrapper<T>>(*this);
        }
        std::unique_ptr<Json_wrapped> get_unique_ptr() override {
            return std::make_unique<Json_wrapper<T>>(*this);
        }
    private:
        std::optional<std::reference_wrapper<T>> _value ;
        std::reference_wrapper<const T> _cvalue;
    };
}