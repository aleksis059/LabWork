#include "ProxyDES.h"
bool File::FileExist()
{
    bool check = false;
    _reading.open(Path, RBinary);
    check = _reading.is_open();
    return !check;
}
bool File::Read()
{
    bool eof = true;
    _reading.open(Path, RBinary);
    char temp = ' ';      
    if (_reading.is_open())   
    { 
        while (eof)
        {
            _reading.get(temp);
            if (_reading.eof())
            {
                eof = false;
            }
            if (eof)
            {
                _data.push_back(temp);
            }
        }
        _reading.close();
        return false;
    }
    else
        return true;
}
bool File::WriteData()
{
    _writing.open(Path, WBinary);
    char temp = ' ';
    if (_writing.is_open())
    {
        for (unsigned int i = 0; i < _data.size(); i++)
        {
            temp = _data.at(i);
            _writing << temp;
        }
        _writing.close();
        return false;
    }
    else
        return true;
}




void DesProxy::en_ofb_cfb_cbc(std::vector<unsigned char> &Data, int Mode, int CFBorOFBorCBC,bool TripleCheck)
{
    

DES_cblock IV = { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 };
    unsigned int Size = Data.size();
    unsigned int TwoSize = (Size + 7) / 8 * 8;
    unsigned char *In = new unsigned char[Size];
    unsigned char *Out = new unsigned char[Size];
    unsigned char *InCBC = new unsigned char[TwoSize];
    unsigned char *OutCBC = new unsigned char[TwoSize];
    int num=0;
    if (CFBorOFBorCBC != CBC)
    {
        for (unsigned int i = 0; i < Size; i++)
        {
            In[i] = Data.at(i);
        }
    }
    else
    {
        for (unsigned int i = 0; i < Size; i++)
        {
            if (i < Size)
            {
                InCBC[i] = Data.at(i);
            }
            else
            {
                InCBC[i] = NULL;
            }
        }
    }
    if (CFBorOFBorCBC == 0)
    {
        if (TripleCheck)
        {
            DES_ede3_cfb64_encrypt(In, Out, Size, &_ks1, &_ks2, &_ks3, &IV, &num, Mode);
        }
        else
        {
            DES_cfb_encrypt(In, Out, 8, Size, &_Shedul_key, &IV, Mode);
        }
    }
    else if (CFBorOFBorCBC == 1)
    {
        if (TripleCheck)
        {
            DES_ede3_ofb64_encrypt(In,Out,Size,&_ks1,&_ks2,&_ks3,&IV,&num);
        }
        else
        {
            DES_ofb_encrypt(In, Out, 8, Size, &_Shedul_key, &IV);
        }
    }
    else
    {
        if (TripleCheck)
        {
            DES_ede3_cbc_encrypt(InCBC,OutCBC,Size,&_ks1,&_ks2,&_ks3,&IV,Mode);
        }
        else
        {
            DES_ncbc_encrypt(InCBC, OutCBC, Size, &_Shedul_key, &IV, Mode);
        }
    }
    if (CFBorOFBorCBC != CBC)
    {
        for (unsigned int i = 0; i < Size; i++)
        {
            if (Mode)
            {
                _EncData.push_back(Out[i]);
            }
            else
            {
                _DecData.push_back(Out[i]);
            }
        }
    }
    else
    {
        for (unsigned int i = 0; i < TwoSize; i++)
        {
            if (Mode)
            {
                _EncData.push_back(OutCBC[i]);
            }
            else
            {
                _DecData.push_back(OutCBC[i]);
            }
        }
    }
    delete In;
    delete Out;
}
void DesProxy::encr_ecb(std::vector<unsigned char> &Data, int Mode,bool TripleCheck)
{
    DES_cblock In;
    DES_cblock Out;
    unsigned int Size = Data.size();
    unsigned int TwoSize = (Data.size() + 7) / 8 * 8;
    unsigned int k = 0;
    for (unsigned int i = 0; i <TwoSize; i++)
    {
        if (i<Size)
        {
            In[k] = Data.at(i);
        }
        else
        {
            In[k] = NULL;
        }
        k++;
        if (k == 8)
        {
            if (TripleCheck)
            {
                DES_ecb3_encrypt(&In, &Out, &_ks1, &_ks2, &_ks3, Mode);
            }
            else
            {
                DES_ecb_encrypt(&In, &Out, &_Shedul_key, Mode);
            }
            for (unsigned int j = 0; j < 8; j++)
            {
                if (Mode)
                {
                    _EncData.push_back(Out[j]);
                }
                else
                {
                    _DecData.push_back(Out[j]);
                }
                In[j] = NULL;
            }
            k = 0;
        }
    }
}
void DesProxy::EnOFB(std::vector<unsigned char> &Data, const char *key)
{
    DES_string_to_key(key, &_key);
    DES_set_key_checked(&_key, &_Shedul_key);
    en_ofb_cfb_cbc(Data, DES_ENCRYPT, OFB, Des);
}
void DesProxy::DeOFB(std::vector<unsigned char> &Data, const char *key)
{
    DES_string_to_key(key, &_key);
    DES_set_key_checked(&_key, &_Shedul_key);
    en_ofb_cfb_cbc(Data, DES_DECRYPT, OFB, Des);
}
void DesProxy::EnCFB(std::vector<unsigned char> &Data, const char *key)
{
    DES_string_to_key(key, &_key);
    DES_set_key_checked(&_key, &_Shedul_key);
    en_ofb_cfb_cbc(Data, DES_ENCRYPT, CFB, Des);
}
void DesProxy::DeCFB(std::vector<unsigned char> &Data, const char *key)
{
    DES_string_to_key(key, &_key);
    DES_set_key_checked(&_key, &_Shedul_key);
    en_ofb_cfb_cbc(Data, DES_DECRYPT, CFB, Des);
}
void DesProxy::EnECB(std::vector<unsigned char>& Data, const char *key)
{
    DES_string_to_key(key, &_key);
    DES_set_key_checked(&_key, &_Shedul_key);
    encr_ecb(Data, DES_ENCRYPT, Des);
}
void DesProxy::DeECB(std::vector<unsigned char> &Data, const char *key)
{
    DES_string_to_key(key, &_key);
    DES_set_key_checked(&_key, &_Shedul_key);
    encr_ecb(Data, DES_DECRYPT, Des);
}
void DesProxy::EnCBC(std::vector<unsigned char> &Data, const char *key)
{
    DES_string_to_key(key, &_key);
    DES_set_key_checked(&_key, &_Shedul_key);
    en_ofb_cfb_cbc(Data, DES_ENCRYPT, CBC, Des);
}
void DesProxy::DeCBC(std::vector<unsigned char> &Data, const char *key)
{
    DES_string_to_key(key, &_key);
    DES_set_key_checked(&_key, &_Shedul_key);
    en_ofb_cfb_cbc(Data, DES_DECRYPT, CBC, Des);
}
void  DesProxy::En3DesOFB(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3)
{
    DES_string_to_key(key1, &_key1);
    DES_string_to_key(key2, &_key2);
    DES_string_to_key(key3, &_key3);
    DES_set_key_checked(&_key1, &_ks1);
    DES_set_key_checked(&_key2, &_ks2);
    DES_set_key_checked(&_key3, &_ks3);
    en_ofb_cfb_cbc(Data, DES_ENCRYPT, OFB, TrDes);
};
void  DesProxy::De3DesOFB(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3)
{
    DES_string_to_key(key1, &_key1);
    DES_string_to_key(key2, &_key2);
    DES_string_to_key(key3, &_key3);
    DES_set_key_checked(&_key1, &_ks1);
    DES_set_key_checked(&_key2, &_ks2);
    DES_set_key_checked(&_key3, &_ks3);
    en_ofb_cfb_cbc(Data, DES_DECRYPT, OFB, TrDes);
}; 
void  DesProxy::En3DesCFB(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3)
{
    DES_string_to_key(key1, &_key1);
    DES_string_to_key(key2, &_key2);
    DES_string_to_key(key3, &_key3);
    DES_set_key_checked(&_key1, &_ks1);
    DES_set_key_checked(&_key2, &_ks2);
    DES_set_key_checked(&_key3, &_ks3);
    en_ofb_cfb_cbc(Data, DES_ENCRYPT, CFB, TrDes);
};
void  DesProxy::De3DesCFB(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3)
{
    DES_string_to_key(key1, &_key1);
    DES_string_to_key(key2, &_key2);
    DES_string_to_key(key3, &_key3);
    DES_set_key_checked(&_key1, &_ks1);
    DES_set_key_checked(&_key2, &_ks2);
    DES_set_key_checked(&_key3, &_ks3);
    en_ofb_cfb_cbc(Data, DES_DECRYPT, CFB, TrDes);
};

void  DesProxy::En3DesCBC(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3)
{
    DES_string_to_key(key1, &_key1);
    DES_string_to_key(key2, &_key2);
    DES_string_to_key(key3, &_key3);
    DES_set_key_checked(&_key1, &_ks1);
    DES_set_key_checked(&_key2, &_ks2);
    DES_set_key_checked(&_key3, &_ks3);
    en_ofb_cfb_cbc(Data, DES_ENCRYPT, CBC, TrDes);
}; 
void  DesProxy::De3DesCBC(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3)
{
    DES_string_to_key(key1, &_key1);
    DES_string_to_key(key2, &_key2);
    DES_string_to_key(key3, &_key3);
    DES_set_key_checked(&_key1, &_ks1);
    DES_set_key_checked(&_key2, &_ks2);
    DES_set_key_checked(&_key3, &_ks3);
    en_ofb_cfb_cbc(Data, DES_DECRYPT, CBC, TrDes);
};
void  DesProxy::En3DesECB(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3)
{
    DES_string_to_key(key1, &_key1);
    DES_string_to_key(key2, &_key2);
    DES_string_to_key(key3, &_key3);
    DES_set_key_checked(&_key1, &_ks1);
    DES_set_key_checked(&_key2, &_ks2);
    DES_set_key_checked(&_key3, &_ks3);
    encr_ecb(Data, DES_ENCRYPT, TrDes);
};
void  DesProxy::De3DesECB(std::vector<unsigned char>& Data, const char *key1, const char *key2, const char *key3)
{
    DES_string_to_key(key1, &_key1);
    DES_string_to_key(key2, &_key2);
    DES_string_to_key(key3, &_key3);
    DES_set_key_checked(&_key1, &_ks1);
    DES_set_key_checked(&_key2, &_ks2);
    DES_set_key_checked(&_key3, &_ks3);
    encr_ecb(Data, DES_DECRYPT, TrDes);
};
