#include "RC42.h"
void RC4::Meta(unsigned char *key)
{
    for (int n = 0; n < 256; n++)
    {
        mass[n] = n;
    }
    size = sizeof(key);
    j = 0;
    for (i = 0; i < 256; i++)
    {
        j = (j + mass[i] + key[i%size]) % 256;
        tmp = mass[i];
        mass[i] = mass[j];
        mass[j] = tmp;
    }
    i = 0;
    j = 0;
}
unsigned char RC4::get()
{
    i = (i + 1) % 256;
    j = j + mass[i] % 256;
    tmp = mass[i];
    mass[i] = mass[j];
    mass[j] = tmp;
    Ki = mass[(mass[i] + mass[j]) % 256];
    return (mass[Ki]);
}
void RC4::Enc(unsigned char *key, std::vector<unsigned char> DataVector)
{
    Meta(key);
    for (unsigned int i = 0; i < DataVector.size(); i++)
    {
        EnData.push_back(DataVector.at(i) ^ get());
    }

}
void RC4::Dec(unsigned char *key, std::vector<unsigned char> DataVector)
{
    Meta(key);
    for (unsigned int i = 0; i < DataVector.size(); i++)
    {
        DeData.push_back(DataVector.at(i) ^ get());
    }
}
std::vector<unsigned char> & RC4::EncData()
{
    return EnData;
}
std::vector<unsigned char>& RC4::DecData()
{
    return DeData;
}