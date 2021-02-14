#include <string_view>
#include <iostream>
#include "stats.h"

using namespace std;

Stats::Stats() {
  method_stats["GET"] = 0;
  method_stats["POST"] = 0;
  method_stats["PUT"] = 0;
  method_stats["DELETE"] = 0;
  method_stats["UNKNOWN"] = 0;
  uri_stats["/"] = 0;
  uri_stats["/order"] = 0;
  uri_stats["/product"] = 0;
  uri_stats["/basket"] = 0;
  uri_stats["/help"] = 0;
  uri_stats["unknown"] = 0;
}

void Stats::AddMethod(string_view method) {
  if (method == "GET") {
    method_stats["GET"]++;
  } else if (method == "POST") {
    method_stats["POST"]++;
  } else if (method == "PUT") {
    method_stats["PUT"]++;
  } else if (method == "DELETE") {
    method_stats["DELETE"]++;
  } else {
    method_stats["UNKNOWN"]++;
  }
}

void Stats::AddUri(string_view uri) {
  if (uri == "/") {
    uri_stats["/"]++;
  } else if (uri == "/order") {
    uri_stats["/order"]++;
  } else if (uri == "/product") {
    uri_stats["/product"]++;
  } else if (uri == "/basket") {
    uri_stats["/basket"]++;
  } else if (uri == "/help") {
    uri_stats["/help"]++;
  } else {
    uri_stats["unknown"]++;
  }
}

const map<string_view, int>& Stats::GetMethodStats() const {
  return method_stats;
}

const map<string_view, int>& Stats::GetUriStats() const {
  return uri_stats;
}

HttpRequest ParseRequest(string_view line) {
  size_t first_not_space = line.find_first_not_of(" ");
  line.remove_prefix(min(line.size(), first_not_space));
  
  HttpRequest http_r;

  size_t pos = 0;
  size_t space = line.find(' ');

  http_r.method = line.substr(pos, space - pos);

  if (space == line.npos) {
    throw out_of_range("");
  }

  pos = space + 1;
  space = line.find(' ', pos);

  http_r.uri = line.substr(pos, space - pos);

  if (space == line.npos) {
    throw out_of_range("");
  }

  pos = space + 1;
  http_r.protocol = line.substr(pos);

  return http_r;
}
