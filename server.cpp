#include <fstream>
#include <cstdarg>
#include <cstdlib>
#include "include/httplib.h"
#include <iostream>
#include "include/json.hpp"
#include "hiredis/hiredis.h"
#include "redis-plus-plus/src/sw/redis++/redis++.h"

std::string read_file(const std::string &path) {
    std::ifstream ifs(path);
    if (ifs) {
        return std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    } else {
        return "";
    }
}


int main() {
    
    httplib::Server svr;
    
    // Create an Redis object, which is movable but NOT copyable.
    auto redis = sw::redis::Redis("tcp://127.0.0.1:6379");

    // ***** STRING commands *****

    redis.set("yarak", "ata");
    auto val = redis.get("yarak");    // val is of type OptionalString. See 'API Reference' section for details.
    if (val) {
        // Dereference val to get the returned value of std::string type.
        std::cout << *val << std::endl;
    }   // else key doesn't exist.

  

    svr.Get("/", [](const httplib::Request& /*req*/, httplib::Response& res) {
        std::cout << "Helloget" << std::endl;
        res.set_content(read_file("public/index.html"), "text/html");
    });

    svr.Get("/404.html", [](const httplib::Request& /*req*/, httplib::Response& res) {
        res.set_content(read_file("public/404.html"), "text/html");
    });

    svr.Get("/script.js", [](const httplib::Request& /*req*/, httplib::Response& res) {
        res.set_content(read_file("public/script.js"), "text/javascript");
    });

    svr.Get("/styles.css", [](const httplib::Request& /*req*/, httplib::Response& res) {
        res.set_content(read_file("public/styles.css"), "text/css");
    });

    svr.Get("/favicon.ico", [](const httplib::Request& /*req*/, httplib::Response& res) {
        res.set_content(read_file("public/favicon.ico"), "image/x-icon");
    });

    svr.Post("/post", [](const httplib::Request& req, httplib::Response& res) {
        std::cout << "Hellopost" << std::endl;
        std::cout << "json: " << req.body << std::endl;
        // Parse the JSON payload
        nlohmann::json data = nlohmann::json::parse(req.body);

        // Retrieve the field values from the JSON
        std::string name = data["name"];
        std::string email = data["email"];
        std::string password = data["password"];
        std::string role = data["role"];


        // Print the form field values to the console
        
        std::cout << "Name: " << name << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "Password: " << password << std::endl;
        std::cout << "Role: " << role << std::endl;
        

    
        res.set_content("done", "text/plain");

    });

    svr.listen("localhost", 8082);
    return 0;
}
