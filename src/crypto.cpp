#include "crypto.h"


std::string readHeader(const std::string &text)
{
    std::string key = text.substr(0, text.find("[Bc]"));

    return key;
}

bool decrypt(std::string text, const std::string &fileName)
{
    std::wstring decrypted;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    std::string key;
    unsigned long charNumber;

    std::fstream ofs(fileName, std::fstream::out);

    if ( !ofs.is_open() )
    {
        return false;
    }

    key = readHeader(text);
    charNumber = readFooter(text);

    text = text.substr(text.find("[Bc]") + 4);
    text = text.substr(0, text.find("[/Bc]"));

    for (int i = 0; i < charNumber; ++i)
    {
        auto ch = static_cast<wchar_t>(text.find(key));

        decrypted.push_back(ch);

        text = text.substr( text.find(key) + key.length() );
    }

    ofs << converter.to_bytes(decrypted);

    return true;
}

unsigned long readFooter(const std::string &text)
{
    std::string number;
    unsigned long charNumber;

    number = text.substr(text.find("[/Bc]") + 5);
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

    keyLength = text.length() <= 50 ? 20 : (text.length() / 10 + 5) * 4;

    for (unsigned long i = 0; i < keyLength; ++i)
    {
        key += getRandomChar();
    }

    ofs << key << "[Bc]";

    return key;
}

bool encrypt(std::string text, const std::string &fileName)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring encrypted;

    std::string key;
    unsigned long charCounter;

    std::fstream ofs(fileName, std::fstream::out);

    if (!ofs.is_open())
    {
        return false;
    }

    encrypted = converter.from_bytes(text);
    key = generateHeader(text, ofs);
    charCounter = 0;

    for (wchar_t i : encrypted)
    {
        for (wchar_t k = 0; k < i; k++)
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
