
#include <fmt/format.h>
#include <iostream>
#include "httplib.h"
#include <iostream>

int main() {
  httplib::Server svr;

  svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
    res.set_content("Hello World!", "text/plain");
  });

  svr.Get("/bye", [](const httplib::Request &, httplib::Response &res) {
      res.set_content("Good bye!", "text/plain");
  });

  svr.listen("0.0.0.0", 8080);
}