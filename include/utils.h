#ifndef BRC_UTILS_H
#define BRC_UTILS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <cstring>


void usage(char*);

template<typename T> void printElement(T t);

bool readFile(const std::string &, std::string &);

bool decryptCheck(const char *);

bool encryptCheck(const char *);

#endif //BRС_UTILS_H
