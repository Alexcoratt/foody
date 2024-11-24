#include <cerrno>
#include <iostream>
#include <fstream>
#include <sstream>

#include <nlohmann/json.hpp>
#include <pqxx/pqxx>

#define STATUS_SUCCESS 0

void printConnString(std::ostream &out, const nlohmann::json &config);

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config>\n";
        return EINVAL;
    }

    std::ifstream ifile(argv[1]);
    auto config = nlohmann::json::parse(ifile);
    ifile.close();

    auto sqlConfig = config.at("sql");

    std::stringstream connStr;
    printConnString(connStr, sqlConfig);
     
    pqxx::connection conn(connStr.str());
    if (conn.is_open())
        std::cout << "connection established\n";
    else
        std::cout << "connection failed\n";

    return STATUS_SUCCESS;
}

void printConnString(std::ostream &out, const nlohmann::json &config) {
    const std::string username = config.at("username");
    out
        << "postgresql://"
        << username << ':'
        << "fdyadmn@"
        << config.value("host", "localhost") << ':'
        << config.value("port", 5432) << '/'
        << config.value("db-name", username)
    ;
}
