#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include "../../files/MyLib.h"
#include <vector>
#include "../../files/zip.h"




double entrop8(File &InEntropFile)
{   unsigned int size8bit=256;
    unsigned int *a = new unsigned int [size8bit];
    unsigned int size=InEntropFile.GetData().size();
    double p=0;
    double entropia=0;
    for (unsigned int i = 0; i < size8bit; i++)
    {
       a[i]=0;
    }
    for (unsigned int i = 0; i < size; i++)
    {
        a[InEntropFile.GetData().at(i)]++;
    }
    for (unsigned int i = 0; i < size8bit; i++)
    {   if (a[i]!=0)
        { 
        p = a[i]*1.0/size;
        entropia +=p*log(p)/log(8);
        }
    }
    return (entropia);
}   
double entrop16(File &InEntropFile)
{
    unsigned int size16bit=65536;
    unsigned int *a = new unsigned int[size16bit];
    uint16_t size = (uint16_t)InEntropFile.GetData().size();
    uint16_t *_data=(uint16_t*)InEntropFile.GetData().data();
    double p = 0;
    double entropia = 0;
    for (unsigned int i = 0; i < size16bit; i++)
    {
        a[i] = 0;
    }
    for (unsigned int i = 0; i < size; i++)
    {
        a[_data[i]]=a[_data[i]]+1;
    }
    for (unsigned int i = 0; i < size16bit; i++)
    {
        if (a[i] != 0)
        {
            p = a[i] * 1.0 / size;
            entropia += p*log(p) / log(16);
        }
    }
    return (entropia);
}

double entropblock(File &InEntropFile)
{
    unsigned int size16bit=65536;
    unsigned int *a=new unsigned int[size16bit];
    uint16_t size=(uint16_t)InEntropFile.GetData().size();
    uint16_t *bit16=(uint16_t*)InEntropFile.GetData().data();
    uint8_t *bit8=(uint8_t*)InEntropFile.GetData().data();
    
    double p=0;
    double entropia =0;
    for (unsigned int i = 0; i < size16bit; i++)
    {
        a[i]=0;
    }
    uint16_t size2=size;
    while (size2 > 0)
    {
        bit16 = (uint16_t*)bit8;
        a[(uint16_t)*bit16]=a[(uint16_t)*bit16]+1;
        bit8++;
        size2--;
        
    }
    for (unsigned int i = 0; i < size16bit; i++)
    {
        if (a[i] != 0)
        {
            p=a[i]*1.0/size;
            entropia +=p*log(p)/log(16);
        }
    }
    return(entropia);
    
}


void Zip(TCHAR *ZipArhivName,TCHAR *ZipFileNameinArchiv, TCHAR *FirstFile)
{
    HZIP ind = CreateZip(ZipArhivName,0);
    ZipAdd(ind,ZipFileNameinArchiv,FirstFile);
    CloseZip(ind);
}

void main()
{
    std::string file1="../../files/Ishodnik.docx";
    File Fileone(file1);
    Fileone.ReadData();
    double entropia8=-entrop8(Fileone);
    std::cout<< "Entropia 8 =  "<<entropia8<<"     ";
    
    double entropia16=-entrop16(Fileone);
    std::cout<<"Entropia 16 =  "<<entropia16<<"   ";
    
    double entropiablock=-entropblock(Fileone);
    std::cout<<"EntropiaBlock =  "<<entropiablock<<"  ";
    
    TCHAR * ZipArhiv="ZipArhiv.zip";
    TCHAR * ZipNameFile="ZipFile.docx";
    TCHAR * SourceFile="../../files/Ishodnik.docx";
    Zip(ZipArhiv,ZipNameFile,SourceFile);
    
    
    double sizesource=Fileone.GetData().size();
    std::string file2="ZipArhiv.zip";
    File file2zip(file2);
    file2zip.ReadData();
    double sizezipfile=file2zip.GetData().size();
    
    std::cout<<"    sizesource=  "<<sizesource<<"  ";
    std::cout<<"  sizezipfile=  "<<sizezipfile<<"  ";
    std::cout<<" Sjatie v "<<sizesource/sizezipfile<<" raz";
    system("pause");

    
}
