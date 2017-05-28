#include "../openssl/aes.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#define RBinary  std::ios::in | std::ios::binary
#define WBinary std::ios::binary | std::ios::out | std::ios::trunc
#define CFB 0
#define OFB 1
#define CBC 2
#define CTR 3
class AesProxy
{
private:
    AES_KEY _EKey;
    AES_KEY _DKey;
    
	std::vector<unsigned char> _EncData;
    std::vector<unsigned char> _DecData;
    
	void en_cfb_ofb_cbc_ctr(std::vector<unsigned char> &Data, int Mode, int CFBorOFBorCBCorCTR);
    void en_ecb(std::vector<unsigned char> &Data, int Mode);
public:
    AesProxy(){}
    
	
	void EnCTR(std::vector<unsigned char> &Data, const unsigned char *key);
    void DeCTR(std::vector<unsigned char> &Data, const unsigned char *key);
    
	void EnECB(std::vector<unsigned char> &Data, const unsigned char *key);
    void DeECB(std::vector<unsigned char> &Data, const unsigned char *key);
    
	void EnCBC(std::vector<unsigned char> &Data, const unsigned char *key);
    void DeCBC(std::vector<unsigned char> &Data, const unsigned char *key);
   
    void EnCFB(std::vector<unsigned char> &Data, const unsigned char *key);
    void DeCFB(std::vector<unsigned char> &Data, const unsigned char *key);
   
    void EnOFB(std::vector<unsigned char> &Data, const unsigned char *key);
    void DeOFB(std::vector<unsigned char> &Data, const unsigned char *key);
    
	std::vector<unsigned char> &GetEncData(){ return _EncData; }
    std::vector<unsigned char> &GetDecData(){ return _DecData; };
};
class File
{
private:
    std::vector<unsigned char> _data;
    std::fstream reading;
    std::fstream writing;
public:
    std::string	Path;
    File(std::string &path) :Path(path){}
    ~File(){}
   
    bool CheckFile();
    bool ReadData();
    bool WriteData();
    std::vector<unsigned char> &GetData() { return _data; }
};