#include "RC42.h"
#include "../../files/MyLib.h"
void main()
{

RC4 starter;
std::string file1 = "../../files/Ishodnik.docx";
std::string file2 = "crypt.docx";
std::string file3 = "decrypt.docx";
File fileone(file1);
File filetwo(file2);
File filefree(file3);
int size = 32;
unsigned char *key = new unsigned char[size];
KeyGeneration keygen;
key = keygen.RC4(size);
fileone.ReadData();
starter.Enc(key, fileone.GetData());
filetwo.GetData() = starter.EncData();
filetwo.WriteData();
starter.Dec(key, filetwo.GetData());
filefree.GetData() = starter.DecData();
filefree.WriteData();
}