#include "MyLib.h"
#include <random>
#include <ctime>
unsigned char *KeyGeneration::RC4(int size)
{
    srand(time(NULL));
    unsigned char *key=new unsigned char [size];
    for (int i = 0; i < size; i++)
    {
        key[i]=(0+rand()%255);
    }
    return key;
}
int File::GetSize()
{
	return _data.size();
}
bool File::ChekingFile()
{
    bool check =false;
    _read.open(_way,ReadMode);
    check = _read.is_open();
    _read.close();
    return !check;
}
bool File::WriteData()
{
    _write.open(_way,WriteMode);
    char tmp=' ';
    if(!_write.is_open())
    return true;
    else
    {
        for (unsigned int i = 0; i < _data.size(); i++)
        {
            tmp=_data.at(i);
            _write<<tmp;
        }
        _write.close();
        return false;
    }

}
bool File::ReadData()
{
    bool eof=true;
    _read.open(_way,ReadMode);
    char tmp=' ';
    if (!_read.is_open())
    return true;
    else
    {
        while (eof)
        {
            _read.get(tmp);
            if (_read.eof())
            {
                eof=false;
            };
            if (eof)
            {
                _data.push_back(tmp);
            }
        }
        _read.close();
        return false;
    }
}

