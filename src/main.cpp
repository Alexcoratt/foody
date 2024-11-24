#include <bits/types/error_t.h>
#include <cerrno>

#include <cstdio>
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
#include <pqxx/pqxx>

#define STATUS_SUCCESS 0
#define DEFAULT_BUFSIZE 1024

int writeConnString(std::string &connString, const nlohmann::json &config, std::size_t bufsize = DEFAULT_BUFSIZE);

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config>\n";
        return EINVAL;
    }

    std::ifstream ifile(argv[1]);
    auto config = nlohmann::json::parse(ifile);
    ifile.close();

    auto sqlConfig = config.at("sql");

    std::string connString;
    auto writeRes = writeConnString(connString, sqlConfig);
    if (writeRes != STATUS_SUCCESS) {
        if (writeRes == ERANGE)
            std::cerr << "error: connection string is too long:\n" << connString << '\n';
        else
            std::cerr << "error: error occured while building connection string: " << strerror(writeRes) << '\n';
        return writeRes;
    }
     
    pqxx::connection conn(connString);
    if (conn.is_open())
        std::cout << "connection established\n";
    else
        std::cout << "connection failed\n";

    return STATUS_SUCCESS;
}

int writeConnString(std::string &connString, const nlohmann::json &config, std::size_t bufsize) {
    char connBuffer[bufsize];
    auto end = snprintf(
        connBuffer,
        bufsize,
        "postgresql://%s:%s@%s:%d/%s",
        ((std::string)config.at("username")).c_str(),
        ((std::string)config.at("password")).c_str(),
        ((std::string)config.value("host", "localhost")).c_str(), 
        (int)config.at("port"),
        ((std::string)config.at("db-name")).c_str()
    );
    
    connString = connBuffer;

    if (end <= 0) return errno;
    if (end >= DEFAULT_BUFSIZE) return ERANGE;

    return STATUS_SUCCESS;
}
