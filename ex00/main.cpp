#include "BitcoinExchange.hpp"


int main(int argc, char const *argv[])
{
    if (argc == 2)
    {

        std::ifstream dataFile("data.csv");

        if (!dataFile)
        {
            std::cerr << "Cant open data file!\n";
            return 1;
        }

        std::map<std::string, float> dataSet;
        std::string line;

        getline(dataFile, line);
        while (getline(dataFile, line))
            dataSet.insert(make_pair(line.substr(0, line.find(",")), atof(line.substr(line.find(",") + 1, line.length()).c_str())));

        std::ifstream inputFile(argv[1]);
        if (!inputFile)
        {
            std::cerr << "Cant open input file!\n";
            return 1;
        }

        getline(inputFile, line);
        if (!isValidFirstLine(line))
        {
            std::cerr << "Error: Invalid first line =>" << line << '\n';
            return 1;
        }
        while (getline(inputFile, line))
        {
            if (line.empty())
                continue;
            try
            {
                parseLine(line);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error: " << e.what() << '\n'; // ? not writing error msgs for now
                continue;
            }
            printOutput(trim(line.substr(0, line.find("|"))), trim(line.substr(line.find("|") + 1, line.length())), dataSet);
        }
    }
    else
        std::cout << "Usage : ./btc inputFile.txt" << std::endl;

    return 0;
}