#include <fstream>
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <conio.h>
#define ReadMode std::ios::in | std::ios::binary
#define WriteMode std::ios::binary | std::ios::out | std::ios::trunc
class File
{
    private:
         std::vector<unsigned char>_data;
         std::fstream _read;
         std::fstream _write;
         std::string _way;
	
    public:
         File(std::string &way)
               :_way(way)
         {

         }
         ~File()
         {

         }
    bool ChekingFile();
    bool ReadData();
    bool WriteData();
    int GetSize();
    std::vector<unsigned char> &GetData()
    {   
            return _data;

    }
};




class KeyGeneration
{
    public:
        KeyGeneration()
        {

        }
        unsigned char *RC4(int size);
};
