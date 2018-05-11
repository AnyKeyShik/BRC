#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <cstring>
#include <sstream>

void usage(char*);

template<typename T> void printElement(T t);

std::string readHeader(const std::string &);

bool decrypt(std::string, const std::basic_string<char> &);

long readFooter(const std::string &);

char getRandomChar();

std::string genereateHeader(const std::string &, std::fstream&);

bool encrypt(std::string, const std::basic_string<char> &);

void genereateFooter(long &, std::fstream &);

int main(int argc, char** argv) {
    std::string inputText;

    switch(argc) {
        case 3: {
            std::ifstream ifs(argv[2]);
            if (!ifs) {
                std::cerr << "File not found!" << std::endl;

                return 1;
            }

            ifs >> std::noskipws;
            std::copy(std::istream_iterator<char>(ifs), std::istream_iterator<char>(), std::back_inserter(inputText));

            if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--decrypt") == 0) {
                if (decrypt(inputText, "decryptedText")) {
                    std::cout << "Decrypted successfully!" << std::endl;
                } else {
                    std::cout << "Write not allowed!" << std::endl;
                }
            } else if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "--encrypt") == 0){
                if (encrypt(inputText, "encryptedText")) {
                    std::cout << "Encrypted successfully!" << std::endl;
                } else {
                    std::cout << "Write not allowed!" << std::endl;
                }
            } else {
                usage(argv[0]);
            }

            break;
        }
        case 4: {
            std::ifstream ifs(argv[2]);
            if (!ifs) {
                std::cerr << "File not found!" << std::endl;

                return 1;
            }

            ifs >> std::noskipws;
            std::copy(std::istream_iterator<char>(ifs), std::istream_iterator<char>(), std::back_inserter(inputText));

            if (strcmp(argv[1], "-d") != 0 || strcmp(argv[1], "--decrypt") != 0) {
                if (!decrypt(inputText, std::string(argv[3]))) {
                    std::cerr << "Write not allowed!" << std::endl;
                }
            } else if (strcmp(argv[1], "-e") != 0 || strcmp(argv[1], "--encrypt") != 0) {
                if (encrypt(inputText, std::string(argv[3]))) {
                    std::cerr << "Write not allowed!" << std::endl;
                }
            }

            break;
        }
        default: {
            usage(argv[0]);

            break;
        }
    }

    return 0;
}

void usage(char *name) {
    std::cout << "Usage: " << name << " -[de] input file name <output file name>" << std::endl;

    printElement("-d, --decrypt\tdecrypt file\n");
    printElement("-e, --encrypt\tencrypt file\n");

}

template<typename T> void printElement(T t) {
    std::cout << std::left << std::setw(8) << std::setfill(' ') << t;
}

std::string readHeader(const std::string &text) {
    std::string key = text.substr(0, text.find("[Bc]"));

    return key;
}

bool decrypt(std::string text, const std::string &fileName) {
    std::fstream ofs(fileName, std::fstream::out);
    if (!ofs.is_open()) {
        return false;
    }

    std::string key = readHeader(text);
    long charNumber = readFooter(text);

    text = text.substr(text.find("[Bc]") + 4);
    text = text.substr(0, text.find("[/Bc]"));

    std::string decrypted;

    for (int i = 0; i < charNumber - 1; ++i) {
        char ch;

        if (text[0] != '-') {
            ch = static_cast<char>(text.find(key));
        } else {
            ch = static_cast<char>(static_cast<int>(text.find(key) - 1) * -1);
        }

        decrypted.append(&ch);

        text = text.substr(text.find(key) + key.length());
    }

    decrypted.resize(static_cast<unsigned long>(charNumber - 1));
    for (int j : decrypted);

    ofs << decrypted;

    return true;
}

long readFooter(const std::string &text) {
    std::string number = text.substr(text.find("[/Bc]") + 5);
    long charNumber;

    std::stringstream(number) >> charNumber;

    return charNumber;
}

char getRandomChar() {
    auto ch = static_cast<char>((random() % 127) - 33);

    while (ch == '-') {
        ch = static_cast<char>((random() % 127) - 33);
    }

    return ch;
}

std::string genereateHeader(const std::string &text, std::fstream &ofs) {
    unsigned long keyLength;
    std::string key;

    if (text.length() <= 50) {
        keyLength = 20;
    } else {
        keyLength = (text.length() / 10 + 5) * 4;
    }

    for (int i = 0; i < keyLength; ++i) {
        key += getRandomChar();
    }

    ofs << key << "[Bc]";

    return key;
}

bool encrypt(std::string text, const std::string &fileName) {
    std::fstream ofs(fileName, std::fstream::out);
    if (!ofs.is_open()) {
        return false;
    }

    std::string key = genereateHeader(text, ofs);
    long charCounter = 0;

    for (int i = 0; i < text.length(); i++) {
        if (static_cast<int>(text[i]) > 0) {
            for (int k = 0; k < static_cast<int>(text[i]); k++) {
                ofs << getRandomChar();
            }
        } else {
            ofs << "-";

            for (int k = 0; k < static_cast<int>(text[i]) * -1; k++) {
                ofs << getRandomChar();
            }
        }

        if (i < text.length() - 1) {
            ofs << key;
        }

        charCounter++;
    }

    genereateFooter(charCounter, ofs);

    return true;
}

void genereateFooter(long &counter, std::fstream &ofs) {
    ofs << "[/Bc]" << counter;
}