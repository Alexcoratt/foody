#include <cerrno>
#include <iostream>
#include <fstream>
#include <sstream>

#include <termios.h>
#include <unistd.h>

#include <nlohmann/json.hpp>
#include <pqxx/pqxx>

#define STATUS_SUCCESS 0

void printConnString(std::ostream &out, const nlohmann::json &config, const std::string &password);
std::string readPassword(const std::string &prompt);

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
    printConnString(connStr, sqlConfig, readPassword("password: "));
     
    pqxx::connection conn(connStr.str());
    if (conn.is_open())
        std::cout << "connection established\n";
    else
        std::cout << "connection failed\n";

    return STATUS_SUCCESS;
}

std::string readPassword(const std::string &prompt) {
    std::string password;
    struct termios oldTermSettings, newTermSettings;

    tcgetattr(STDIN_FILENO, &oldTermSettings);
    newTermSettings = oldTermSettings; // get terminal settings
    newTermSettings.c_lflag &= ~(ECHO); // disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermSettings); // apply settings

    std::cout << prompt;
    std::getline(std::cin, password);
    std::cout << std::endl;

    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermSettings); // restore old settings

    return password;
}

void printConnString(std::ostream &out, const nlohmann::json &config, const std::string &password) {
    const std::string username = config.at("username");
    out
        << "postgresql://"
        << username << ':'
        << password << '@' 
        << config.value("host", "localhost") << ':'
        << config.value("port", 5432) << '/'
        << config.value("db-name", username)
    ;
}