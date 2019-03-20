#ifndef BRC_CRYPTO_H
#define BRC_CRYPTO_H

#include <cstring>
#include <fstream>
#include <sstream>

#include <iostream>

std::string readHeader(const std::string &);

bool decrypt(std::string, const std::basic_string<char> &fileName="decryptedText");

unsigned long readFooter(const std::string &);

char getRandomChar();

std::string generateHeader(const std::string &, std::fstream &);

bool encrypt(std::string, const std::basic_string<char> &fileName="encryptedText");

void generateFooter(unsigned long &, std::fstream &);


#endif //BRС_CRYPTO_H
