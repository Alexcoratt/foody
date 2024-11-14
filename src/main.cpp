#include <cerrno>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#define STATUS_SUCCESS 0

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config>\n";
        return E2BIG;
    }

    std::ifstream ifile(argv[1]);
    auto config = nlohmann::json::parse(ifile);
    ifile.close();

    std::cout << config << std::endl;

    return STATUS_SUCCESS;
}