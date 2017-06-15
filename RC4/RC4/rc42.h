#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
class RC4
{
private:
    unsigned char mass[256];
    unsigned int size, i, j;
    unsigned char tmp;
    int Ki;
    std::vector<unsigned char>EnData;
    std::vector<unsigned char>DeData;
    unsigned char get();
    void Meta(unsigned char *key);
public:
    RC4(){}
    void Dec(unsigned char *key, std::vector<unsigned char> DataVector);
    void Enc(unsigned char *key, std::vector<unsigned char> DataVector);
    std::vector<unsigned char>&EncData();
    std::vector<unsigned char>&DecData();
    

};
