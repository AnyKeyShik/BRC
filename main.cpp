#include "utils.h"
#include "crypto.h"

int main(int argc, char** argv)
{
    std::string inputText;

    switch(argc)
    {
        case 3:
        {
            if ( !readFile(argv[2], inputText) )
            {
                return -1;
            }

            if ( decryptCheck(argv[1]) )
            {
                if ( decrypt(inputText) )
                {
                    std::cout << "Decrypted successfully!" << std::endl;
                }
                else
                {
                    std::cout << "Write not allowed!" << std::endl;
                }
            }
            else if (encryptCheck(argv[1]) )
            {
                if ( encrypt(inputText) )
                {
                    std::cout << "Encrypted successfully!" << std::endl;
                }
                else
                {
                    std::cout << "Write not allowed!" << std::endl;
                }
            }
            else
            {
                usage(argv[0]);
            }

            break;
        }
        case 4:
        {
            if ( !readFile(argv[2], inputText) )
            {
                return -1;
            }

            if ( decryptCheck(argv[1]) )
            {
                if ( decrypt(inputText, std::string(argv[3])) )
                {
                    std::cout << "Decrypted successfully!" << std::endl;
                }
                else
                {
                    std::cerr << "Write not allowed!" << std::endl;
                }
            }
            else if (encryptCheck(argv[1]) )
            {
                if ( encrypt(inputText, std::string(argv[3])) )
                {
                    std::cout << "Encrypted successfully!" << std::endl;
                }
                else
                {
                    std::cerr << "Write not allowed!" << std::endl;
                }
            }
            else
            {
                usage(argv[0]);
            }

            break;
        }
        default:
        {
            usage(argv[0]);

            break;
        }
    }

    return 0;
}


