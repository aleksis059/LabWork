#include "../../files/MyLib.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "../../files/openssl/md5.h"

std::vector<unsigned char>Func(std::vector<unsigned char> &Hash1)
{
    std::vector<unsigned char> hash;
    for (int i = 0; i < 64; i++)
    {
        hash.push_back(Hash1.at(i));
        hash.at(i) += (hash.at(i)<<2);
        hash.at(i) ^= (hash.at(i) >>4);
        hash.at(i) += (hash.at(i) << 3);
        hash.at(i) ^=(hash.at(i)>>7);
        hash.at(i) +=(hash.at(i)<<6);
       
    }
    
    
    return hash;
}

std::vector<unsigned char>MyHash(std::vector<unsigned char> &TMP)
{
    std::vector<unsigned char> PrevHash;
    
    int size = TMP.size();
    int size2 = (size + 63) / 64 * 64;
    int sizemod = abs(size2);
    for (int i = 0; i < sizemod - size; i++)
    {
        TMP.push_back('w');
    }
    for (int i = 0; i < sizemod; i = i + 64)
    {
       
            
            for (int j = i; j < i + 64; j++)
            {
                PrevHash.push_back(TMP.at(j));
            }
            PrevHash = Func(PrevHash);

       
    }
    return PrevHash;


}
void MD5(File &f1, File &fmd5)
{   
    MD5_CTX md5Handler;
    MD5_Init(&md5Handler);
    unsigned char md5digest[MD5_DIGEST_LENGTH];
    std::vector<unsigned char>tmp;
    int size=f1.GetData().size();
    MD5_Init(&md5Handler);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i += 64)
    {   
        for (int j = i; j < size && j < i + 64; j++)
        {
            tmp.push_back(f1.GetData().at(j));
        }
    MD5_Update(&md5Handler,&tmp,64);
    MD5_Final(md5digest,&md5Handler);
    for (int j = 0; j < 32; j++)
    {
        fmd5.GetData().push_back(md5digest[j]);
    }   
    tmp.clear();
    }
    fmd5.WriteData();
    

}
void MHash(File &Input, File &MyOut, std::vector<unsigned char> IV)
{
    unsigned int size=Input.GetData().size();
    std::vector<unsigned char> tmp;
    for (int i = 0; i < size; i += 64)
    {
        for (int j = i; j < size && j < i + 64; j++)
        {
            tmp.push_back(Input.GetData().at(j));
        }
        tmp=MyHash(tmp);
        for (int i = 0; i < 32; i++)
        {
            MyOut.GetData().push_back(tmp.at(i));
        }
    }
    MyOut.WriteData();
}

void main()
{
    
    std::string file1 = "../../files/Ishodnik.docx";
    std::string file2 = "md5output.docx";
    std::string file3 = "myhash.docx";
    std::vector<unsigned char> IV;
    File fileone(file1);
    File filetwo(file2);
    File filefree(file3);
    fileone.ReadData();
    unsigned char b;
    for (int i = 0; i < 64; i++)
    {
        b = (unsigned char)i;
        IV.push_back(b);
    }
    MD5(fileone, filetwo);
    MHash(fileone, filefree,IV);
    
  
}
