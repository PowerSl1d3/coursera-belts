#include "phone_number.h"
#include <iostream>
#include <exception>
#include <sstream>

PhoneNumber::PhoneNumber(const string& international_number) {
  istringstream input(international_number);
  int country_code, city_code;
  char c;
  input >> c;
  if (c != '+') {
    throw invalid_argument("");
  }
  input >> country_code;
  if (!input) {
    throw invalid_argument("");
  }
  input >> c;
  if (c != '-') {
    throw invalid_argument("");
  }
  input >> city_code;
  if (!input) {
    throw invalid_argument("");
  }
  input.ignore(1);
  input >> local_number_;
  if (!input) {
    throw invalid_argument("");
  }
  country_code_ = to_string(country_code);
  city_code_ = to_string(city_code);
}

string PhoneNumber::GetCountryCode() const {
  return country_code_;
}

string PhoneNumber::GetCityCode() const {
  return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
  return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
  return "+" + country_code_ + "-" + city_code_ + "-"  + local_number_;
}

