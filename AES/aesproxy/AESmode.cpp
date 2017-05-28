#include "AESmode.h"

bool File::ReadData()
{
    bool eof = true;
    reading.open(Path, RBinary);
    char temp = ' ';
    if (reading.is_open())
    {
        while (eof)
        {
            reading.get(temp);
            if (reading.eof())
            {
                eof = false;
            }
            if (eof)
            {
                _data.push_back(temp);
            }
        }
        reading.close();
        return false;
    }
    else
        return true;
}


bool File::WriteData()
{
    writing.open(Path, WBinary);
    char temp = ' ';
    if (writing.is_open())
    {
        for (unsigned int i = 0; i < _data.size(); i++)
        {
            temp = _data.at(i);
            writing << temp;
        }
        writing.close();
        return false;
    }
    else
        return true;
}


bool File::CheckFile()
{
	bool check = false;
	reading.open(Path, RBinary);
	check = reading.is_open();
	return !check;
}


void AesProxy::EnCTR(std::vector<unsigned char> &Data, const unsigned char *key)
{
    AES_set_encrypt_key(key, 128, &_EKey);
    en_cfb_ofb_cbc_ctr(Data, AES_ENCRYPT, CTR);
}

void AesProxy::DeCTR(std::vector<unsigned char> &Data, const unsigned char *key)
{
    AES_set_encrypt_key(key, 128, &_DKey);
    en_cfb_ofb_cbc_ctr(Data, AES_DECRYPT, CTR);
}

void AesProxy::EnECB(std::vector<unsigned char> &Data, const unsigned char *key)
{
    AES_set_encrypt_key(key, 128, &_EKey);
    en_ecb(Data, AES_ENCRYPT);
}

void AesProxy::DeECB(std::vector<unsigned char> &Data, const unsigned char *key)
{
    AES_set_decrypt_key(key, 128, &_DKey);
    en_ecb(Data, AES_DECRYPT);
}

void AesProxy::EnCBC(std::vector<unsigned char> &Data, const unsigned char *key)
{
    AES_set_encrypt_key(key, 128, &_EKey);
    en_cfb_ofb_cbc_ctr(Data, AES_ENCRYPT, CBC);
}
void AesProxy::DeCBC(std::vector<unsigned char> &Data, const unsigned char *key)
{
    AES_set_decrypt_key(key, 128, &_DKey);
    en_cfb_ofb_cbc_ctr(Data, AES_DECRYPT, CBC);
}
void AesProxy::EnCFB(std::vector<unsigned char> &Data, const unsigned char *key)
{
    AES_set_encrypt_key(key, 128, &_EKey);
    en_cfb_ofb_cbc_ctr(Data, AES_ENCRYPT,CFB);
}
void AesProxy::DeCFB(std::vector<unsigned char> &Data, const unsigned char *key)
{
    AES_set_encrypt_key(key, 128, &_DKey);
    en_cfb_ofb_cbc_ctr(Data, AES_DECRYPT,CFB);
}
void AesProxy::EnOFB(std::vector<unsigned char> &Data, const unsigned char  *key)
{
    AES_set_encrypt_key(key, 128, &_EKey);
    en_cfb_ofb_cbc_ctr(Data, AES_ENCRYPT, OFB);
}
void AesProxy::DeOFB(std::vector<unsigned char> &Data, const unsigned char *key)
{
    AES_set_encrypt_key(key, 128, &_DKey);
    en_cfb_ofb_cbc_ctr(Data, AES_DECRYPT, OFB);
}
void AesProxy::en_ecb(std::vector<unsigned char> &Data, int Mode)
{
    unsigned int SizeData = Data.size();
    unsigned int TwoSize = ((SizeData + 15) / 16) * 16;
	unsigned char Out[16];
    unsigned char In[16];
    unsigned k = 0;
    for (int i = 0; i < TwoSize; i++)
    {
        if (i < SizeData)
        {
            In[k] = Data.at(i);
        }
        else
        {
            In[k] = NULL;
        }
        k++;
        if (k == 16)
        {
            if (Mode == 1)
            {
                AES_ecb_encrypt(In, Out, &_EKey, Mode);
            }
            else 
            {
                AES_ecb_encrypt(In, Out, &_DKey, Mode);
            }
            for (int i = 0; i < 16; i++)
            {
                if (Mode == 1)
                {
                    _EncData.push_back(Out[i]);
                }
                else
                {
                    _DecData.push_back(Out[i]);
                }
            }
            k = 0;
        }
    }
}

void AesProxy::en_cfb_ofb_cbc_ctr(std::vector<unsigned char> &Data, int Mode, int CFBorOFBorCBCorCTR)
{
    unsigned int DataSize = Data.size();
    unsigned int TwoSize = (DataSize + 15) / 16 * 16;
    unsigned char *In= new unsigned char[DataSize];
    unsigned char *Out = new unsigned char[DataSize];
    unsigned char *OutCBC = new unsigned char[TwoSize];
    unsigned char *InCBC = new unsigned char[TwoSize];
    
	unsigned char IV[AES_BLOCK_SIZE] = "648qau*62$g+ú5";
    unsigned char ecount[AES_BLOCK_SIZE] = "Y}÷v3d2151+-^'-";
    unsigned int numberCTR = 0;
    int num = 0;
    
	if (CFBorOFBorCBCorCTR == CBC)
    {
		for (int i = 0; i < TwoSize; i++)
		{
			if (i < DataSize)
			{
				InCBC[i] = Data.at(i);
			}
			else
			{
				InCBC[i] = NULL;
			}
		}
       
    }
    else
    {
		for (int i = 0; i < DataSize; i++)
		{
			In[i] = Data.at(i);
		}
        
    }
    if (Mode == 1)
    {
        switch (CFBorOFBorCBCorCTR)
        {
		case CTR:AES_ctr128_encrypt(In, Out, DataSize, &_EKey, IV, ecount, &numberCTR); break;
        case CFB:AES_cfb128_encrypt(In, Out, DataSize, &_EKey, IV, &num, Mode); break;
		case CBC:AES_cbc_encrypt(InCBC, OutCBC, TwoSize, &_EKey, IV, Mode); break;
		case OFB:AES_ofb128_encrypt(In, Out, DataSize, &_EKey, IV, &num); break;
       
        
        }
    }
    else
    {
        switch (CFBorOFBorCBCorCTR)
        {
		case CTR:AES_ctr128_encrypt(In, Out, TwoSize, &_DKey, IV, ecount, &numberCTR); break;
        case CFB:AES_cfb128_encrypt(In, Out, DataSize, &_DKey, IV, &num, Mode); break;
		case CBC:AES_cbc_encrypt(InCBC, OutCBC, TwoSize, &_DKey, IV, Mode); break;
	    case OFB:AES_ofb128_encrypt(In, Out, TwoSize, &_DKey, IV, &num); break;
        
        
        }
    }
    if (CFBorOFBorCBCorCTR == CBC)
    {
		for (int i = 0; i < TwoSize; i++)
		{
			if (Mode == 1)
			{
				_EncData.push_back(OutCBC[i]);
			}
			else
			{
				_DecData.push_back(OutCBC[i]);
			}
		}
    }
    else
    {
		for (int i = 0; i < TwoSize; i++)
		{
			if (Mode == 1)
			{
				_EncData.push_back(Out[i]);
			}
			else
			{
				_DecData.push_back(Out[i]);
			}
		}
       
    }
}