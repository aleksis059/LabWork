#include <stdio.h>
#include <iostream>
#include <vector>
#include "../../files/MyLib.h"
#include "../../files/openssl/pem.h"
#include "../../files/openssl/evp.h"
#include "../../files/openssl/ssl.h"
#include "../../files/openssl/rsa.h"
#include "../../files/openssl/err.h"
#include "../../files/openssl/bio.h"
class rsa1
{
	public:
		RSA * createRSA(unsigned char * key, int Public);
		int public_encrypt(unsigned char * data, int data_len, unsigned char * key, unsigned char *encrypted);
		int private_decrypt(unsigned char * enc_data, int data_len, unsigned char * key, unsigned char *decrypted);
		int private_encrypt(unsigned char * data, int data_len, unsigned char * key, unsigned char *encrypted);
		int public_decrypt(unsigned char * enc_data, int data_len, unsigned char * key, unsigned char *decrypted);
	    void Encrypt(unsigned char* publickey, File &ptext, File& ctext);
        void Decrypt(unsigned char* privatekey,File&dtext);
        std::vector<unsigned char*>EncryptVector;
};