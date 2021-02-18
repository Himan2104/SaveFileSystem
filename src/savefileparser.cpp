/*****************************
Written by Himanshu Parchand - https://himan2104.github.io
To be used freely as the user intends. 
Implements a basic savefile system for C++ based games.
TODO:
-> Add a constructor/function for loading custom save input.
-> Modify values being added to the save file according to your game.
-> Modify the encryption code.

The encryption code is a very simple and basic implementation
and is expected to be replaced by something much more competent.

Give credits if you want to, no pressure :)
*****************************/
#include<fstream>
#include<iostream>
#include<string>
#include"stringEncryptor.hpp"

class Save
{
    public:
        Save()
        {
            name = "Lodu Lalith";
            level = 2;
            points = 920;
            hp = 69;
            ammo = 300;
        };
        ~Save()
        {};

        void Write()
        {
            std::string save;
            save = name + ";";
            save +=  std::to_string(level) + ";";
            save +=  std::to_string(points) + ";";
            save +=  std::to_string(hp) + ";";
            save +=  std::to_string(ammo) + ";";
            encrypt(save);
            std::ofstream savefile;
            savefile.open("save.sv");
            savefile << save;

            savefile.close();
        }

        void Load()
        {
            std::string save;
            std::ifstream savefile;
            savefile.open("save.sv");
            std::getline(savefile, save);
            decrypt(save);
            int sidx = 0;
            int dataidx = 0;
            for(int i = 0; i < save.length(); i++)
            {
                if(save[i] == ';') 
                {
                    std::string newstr = "";
                    for(int j = sidx; j < i; j++)
                    {
                        newstr += save[j];
                    }

                    std::string _name;
                    int _level;
                    int _points;
                    float _hp;
                    int _ammo;

                    switch (dataidx)
                    {
                    case 0:
                        _name = newstr;
                        std::cout << "Name : " << _name << std::endl;
                        break;
                    case 1: 
                        _level = std::stoi(newstr);
                        std::cout << "Level : " << _level + 3<< std::endl;
                        break;
                    case 2: 
                        _points = std::stoi(newstr);
                        std::cout << "Points : " << _points + 4 << std::endl;
                        break;
                    case 3: 
                        _hp = std::stof(newstr);
                        std::cout << "HP : " << _hp + 120.54f << std::endl;
                        break;
                    case 4: 
                        _ammo = std::stoi(newstr);
                        std::cout << "Ammo : " << _ammo + 300<< std::endl;
                        break;
                    default:
                        break;
                    }
                    sidx = i+1;
                    dataidx++;
                } 
            }
            savefile.close();
        }

        void Delete()
        {
            std::cout << "Deleting...";
            std::ofstream savefile;
            savefile.open("save.sv");
            savefile << "";
            savefile.close();
            std::cout << "Done\n";
        }
    private:
        std::string name;
        int level;
        int points;
        float hp;
        int ammo;
};

int main()
{    
    std::string input;
    Save save;
    do
    {
        std::cout << ">>";
        std::cin >> input;
        if(input == "write") save.Write();
        else if(input == "read") save.Load();
        else if(input == "del") save.Delete();
        else if(input == "exit") std::cout << "Exiting...";
        else std::cout << "ERR!\n";
    }while(input!="exit"); 
    return 0;
}