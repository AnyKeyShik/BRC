#include "crypto.h"


std::string readHeader(const std::string &text)
{
    std::string key = text.substr(0, text.find("[Bc]"));

    return key;
}

bool decrypt(std::string text, const std::string &fileName)
{
    std::fstream ofs(fileName, std::fstream::out);

    if ( !ofs.is_open() )
    {
        return false;
    }

    std::string key = readHeader(text);
    unsigned long charNumber = readFooter(text);

    text = text.substr(text.find("[Bc]") + 4);
    text = text.substr(0, text.find("[/Bc]"));

    std::string decrypted;

    for (int i = 0; i < charNumber; ++i)
    {
        auto ch = static_cast<char>( text.find(key) );

        decrypted.push_back(ch);

        text = text.substr( text.find(key) + key.length() );
    }

    ofs << decrypted;

    return true;
}

unsigned long readFooter(const std::string &text)
{
    std::string number = text.substr(text.find("[/Bc]") + 5);
    unsigned long charNumber;

    std::stringstream(number) >> charNumber;

    return charNumber;
}


char getRandomChar()
{
    auto ch = static_cast<char>( (random() % 127) - 33 );

    while (ch == '-')
    {
        ch = static_cast<char>( (random() % 127) - 33 );
    }

    return ch;
}


std::string generateHeader(const std::string &text, std::fstream &ofs) {
    unsigned long keyLength;
    std::string key;

    if ( text.length() <= 50 )
    {
        keyLength = 20;
    }
    else
    {
        keyLength = (text.length() / 10 + 5) * 4;
    }

    for (unsigned long i = 0; i < keyLength; ++i)
    {
        key += getRandomChar();
    }

    ofs << key << "[Bc]";

    return key;
}

bool encrypt(std::string text, const std::string &fileName)
{
    std::fstream ofs(fileName, std::fstream::out);

    if (!ofs.is_open())
    {
        return false;
    }

    std::string key = generateHeader(text, ofs);
    unsigned long charCounter = 0;

    for (char i : text)
    {
        for (unsigned long k = 0; k < static_cast<unsigned long>(i); k++)
        {
            ofs << getRandomChar();
        }

        ofs << key;

        charCounter++;
    }

    generateFooter(charCounter, ofs);

    return true;
}

void generateFooter(unsigned long &counter, std::fstream &ofs)
{
    ofs << "[/Bc]" << counter;
}
