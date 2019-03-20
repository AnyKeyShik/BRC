#include "utils.h"

template<typename T> void printElement(T t)
{
    std::cout << std::left << std::setw(8) << std::setfill(' ') << t;
}

void usage(char *name)
{
    std::cout << "Usage: " << name << " -[de] input file name <output file name>" << std::endl;

    printElement("-d, --decrypt\tdecrypt file\n");
    printElement("-e, --encrypt\tencrypt file\n");

}

bool readFile(const std::string &fileName, std::string &destination)
{
    std::ifstream ifs(fileName);

    if (!ifs)
    {
        std::cerr << "File not found!" << std::endl;

        return false;
    }

    ifs >> std::noskipws;
    std::copy(std::istream_iterator<char>(ifs), std::istream_iterator<char>(), std::back_inserter(destination));

    return true;
}

bool decryptCheck(const char *input)
{
    return strcmp(input, "-d") == 0 || strcmp(input, "--decrypt") == 0;
}

bool encryptCheck(const char *input)
{
    return strcmp(input, "-e") == 0 || strcmp(input, "--encrypt") == 0;
}
