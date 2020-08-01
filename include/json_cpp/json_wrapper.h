#pragma once
#include <iostream>
#include <json_cpp/json_util.h>
#include <json_cpp/json_base.h>
#include <memory>
#include <optional>

#define Json_wrap_object(X) json_cpp::Json_object_wrapper< std::remove_const<std::remove_reference<decltype(X)>::type>::type >(X)
#define Json_wrap_reference(X) json_cpp::Json_reference_wrapper<std::remove_const<decltype(X)>::type>(X)


namespace json_cpp {
    struct Json_wrapped : Json_base{
        virtual std::unique_ptr<Json_wrapped> get_unique_ptr() = 0;
        virtual std::unique_ptr<Json_wrapped> get_unique_ptr() const = 0;
        bool require_quotes{false};
    };

    template <class T>
    struct Json_reference_wrapper : Json_wrapped{
        explicit Json_reference_wrapper<T>(T &value) : _value (value), _cvalue (value){
            if constexpr (std::is_same_v<T, std::string>) {
                require_quotes = true;
            }
        }
        explicit Json_reference_wrapper<T>(const T &value) : _cvalue (value){
            if constexpr (std::is_same_v<T, std::string>) {
                require_quotes = true;
            }
        }
        void json_parse(std::istream &i) override{
            if (!_value) throw std::logic_error("cannot write a const variable");
            auto &r = _value.value().get();
            if constexpr (std::is_same_v<T, std::string>) {
                r = Json_util::read_string(i);
            } else if constexpr (std::is_enum<T>::value) {
                int ev;
                i >> ev;
                r = (T) ev;
            } else {
                Json_util::skip_blanks(i);
                i >> r;
            }
        }
        void json_write(std::ostream &o) const override {
            const auto &r = _cvalue.get();
            if constexpr (std::is_same_v<T, std::string>) {
                o << '"' << r << '"';
            } else {
                o << r;
            }
        }
        std::unique_ptr<Json_wrapped> get_unique_ptr() const override {
            return std::make_unique<Json_reference_wrapper<T>>(*this);
        }
        std::unique_ptr<Json_wrapped> get_unique_ptr() override {
            return std::make_unique<Json_reference_wrapper<T>>(*this);
        }
    private:
        std::optional<std::reference_wrapper<T>> _value ;
        std::reference_wrapper<const T> _cvalue;
    };

    template <class T>
    struct Json_object_wrapper : Json_wrapped{
        explicit Json_object_wrapper<T>(T &value) : _value (value), _cvalue (value){}
        explicit Json_object_wrapper<T>(const T &value) : _cvalue (value){}

        void json_parse(std::istream &i) override {
            if (!_value) throw std::logic_error("cannot write a const variable");
            auto &r = _value.value().get();
            if constexpr (std::is_same_v<T, std::string>) {
                r = Json_util::read_string(i);
            } else if constexpr (std::is_enum<T>::value) {
                int ev;
                i >> ev;
                r = (T) ev;
            } else {
                Json_util::skip_blanks(i);
                i >> r;
            }
        }
        void json_write(std::ostream &o) const override{
            const auto &r = _cvalue.get();
            if constexpr (std::is_same_v<T, std::string>) {
                o << '"' << r << '"';
            } else {
                o << r;
            }
        }
        std::unique_ptr<Json_wrapped> get_unique_ptr() const override {
            return std::make_unique<Json_object_wrapper<T>>(*this);
        }
        std::unique_ptr<Json_wrapped> get_unique_ptr() override {
            return std::make_unique<Json_object_wrapper<T>>(*this);
        }
    private:
        std::optional<std::reference_wrapper<T>> _value ;
        std::reference_wrapper<const T> _cvalue;
    };
}