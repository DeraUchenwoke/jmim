#include "../include/parse_csv.hpp"
#include <string>

int main() {
    const std::string file_path = "../../test/data/AAPL.csv";
    ReadCSV(file_path);
}