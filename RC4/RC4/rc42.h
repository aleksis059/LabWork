#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <math.h>
#include "../../files/MyLib.h"
class RC4
{
public:
    RC4(){}
    unsigned char mass[256];
    unsigned int size, i, j;
    unsigned char tmp;
    int Ki;
    std::vector<unsigned char>EnData;
    std::vector<unsigned char>DeData;
    void Dec(unsigned char *key, std::vector<unsigned char> DataVector);
    void Enc(unsigned char *key, std::vector<unsigned char> DataVector);
    unsigned char get();
    void Meta(unsigned char *key);
    std::vector<unsigned char>&EncData();
    std::vector<unsigned char>&DecData();
   
    
    
    

};
