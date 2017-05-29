#include <stdio.h>
#include "../openssl/des.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#define CFB 0
#define OFB 1
#define CBC 2
#define WBinary std::ios::binary | std::ios::out | std::ios::trunc
#define RBinary  std::ios::in | std::ios::binary
#define TrDes true
#define Des false
class DesProxy
{
private:
    DES_cblock _key;
    DES_key_schedule _Shedul_key;
    DES_key_schedule _ks1;
    DES_key_schedule _ks2;
    DES_key_schedule _ks3; 
    DES_cblock _key1;
    DES_cblock _key2;
    DES_cblock _key3;
   
    std::vector<unsigned char> _EncData;
    std::vector<unsigned char> _DecData;
    
void en_ofb_cfb_cbc(std::vector<unsigned char> &Data, int Mode, int CFBorOFBorCBC, bool TripleCheck);
    void encr_ecb(std::vector<unsigned char> &Data, int Mode, bool TripleCheck);
public:
    DesProxy(){}
    void EnECB(std::vector<unsigned char> &Data, const char *key);
    void DeECB(std::vector<unsigned char> &Data, const char *key);
    void EnCBC(std::vector<unsigned char> &Data, const char *key);
    void DeCBC(std::vector<unsigned char> &Data, const char *key);
    void EnCFB(std::vector<unsigned char> &Data, const char *key);
    void DeCFB(std::vector<unsigned char> &Data, const char *key);
    void EnOFB(std::vector<unsigned char> &Data, const char *key);
    void DeOFB(std::vector<unsigned char> &Data, const char *key);
    void En3DesECB(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3);
    void De3DesECB(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3);
    void En3DesCBC(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3);
    void De3DesCBC(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3);
    void En3DesCFB(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3);
    void De3DesCFB(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3);
    void En3DesOFB(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3);
    void De3DesOFB(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3);
    std::vector<unsigned char> &GetEncData(){ return _EncData; }
    std::vector<unsigned char> &GetDecData(){ return _DecData; };
};
class File
{
private:
    std::vector<unsigned char> _data;
    std::fstream _reading;
    std::fstream _writing;
public:
    std::string	Path;
    File(std::string &path) :Path(path){}
    ~File()
{
}
    bool FileExist();
    bool Read();
    bool WriteData();
    std::vector<unsigned char> &GetData() { return _data; }
};
