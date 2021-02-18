#include<string>
#include<iostream>
#include<time.h>

void encrypt(std::string& str)
{
    srand(time(NULL));
    int seed  = rand()%4294967295;
    srand(seed);
    int random = rand()%2147483647;
    for(int  i = 0; i < str.length(); i++)
        str[i] = int(str[i]) + random;

    str = std::to_string(seed) + "." + str;

    std::cout << "Encrypted String : "  << str << std::endl;
}

void decrypt(std::string& str)
{
    int seed = 0;
    int random = 0;
    bool flag = false;
    std::string sub = "";
    for(int  i = 0; i < str.length(); i++)
    {
        if(!flag) 
        {
            if(str[i] == '.') 
            {
                std::string temp = "";
                for(int j = 0; j < i; j++) temp += str[j];
                seed = std::stoi(temp);
                srand(seed);
                random = rand()%2147483647;
                flag = true;  
            }
        }
        else sub += int(str[i]) - random;
    }

    str = sub;

    std::cout << "Decrypted String : "  << str << std::endl;
}

