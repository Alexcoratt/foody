#include <cerrno>
#include <iostream>
#include <fstream>
#include <pqxx/connection.hxx>
#include <sstream>

#include <termios.h>
#include <unistd.h>

#include <nlohmann/json.hpp>
#include <pqxx/pqxx>

#define STATUS_SUCCESS 0

// auxillary function declarations

std::string makeConnString(const nlohmann::json &config);
std::string getPasswordFromConfig(const nlohmann::json &config);
std::string readPassword(const std::string &prompt);

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <config>\n";
        return EINVAL;
    }

    std::ifstream ifile(argv[1]);
    auto config = nlohmann::json::parse(ifile);
    ifile.close();

    auto sqlConfig = config.at("sql");

    pqxx::connection conn(makeConnString(sqlConfig));
    std::cout << "connection:\t" << (conn.is_open() ? "OK" : "FAIL") << std::endl;

    pqxx::work pqwork(conn);

    std::cout << "query results:\n";
    auto res = pqwork.exec("SELECT * FROM users;");
    for (auto row : res)
        std::cout << row["id"] << ' ' << row["login"] << ' ' << row["bio"] << std::endl;

    return STATUS_SUCCESS;
}

// definitions

std::string makeConnString(const nlohmann::json &config) {
    const std::string username = config.at("username");

    std::stringstream res;
    res << "postgresql://" << username;
    
    std::string password = getPasswordFromConfig(config);
    if (!password.empty())
        res << ':' << password;
    
    res << '@' 
        << config.value("host", "localhost") << ':'
        << config.value("port", 5432) << '/'
        << config.value("db-name", username)
    ;

    return res.str();
}

std::string getPasswordFromConfig(const nlohmann::json &config) {
    const auto noPass = config.value("no-pass", false);
    if (!noPass) {
        const auto found = config.find("password");
        if (found != config.end())
            return *found;
        return readPassword("password: ");
    }

    return std::string();
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
