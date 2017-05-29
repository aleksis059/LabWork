#include "ProxyDES.h"
#include  <conio.h>
int main(int argc, char **argv)
{   setlocale(LC_CTYPE,"Russian");
    std::string path = "Ishodnik.docx";
    std::string path2 = "Shifr.docx";
    std::string path3 = "DeShifr.docx";
    File FileOne(path);
    File CriptFile(path2);
    File DeCriptFile(path3);
    int mode=0;
    int mode2=0;
    bool cont = true;
    DesProxy crypter;
    while (cont)
    {
        std::cout << "Выберите тип : 1 = 3DES , 2 = DES\n";
        std::cin >> mode;
        if (mode>2 || mode<1)
        {
            system("cls");
            std::cout << "Ошибка, возможен выбор 1 или 2\n";
            _getch();
        }
        else cont = false;
        system("cls");
    }
    cont = true;
    while (cont)
    {
        std::cout << "Выберите режим 1=OFB, 2=CFB, 3=CBC, 4=ECB\n";
        std::cin >> mode2;
        if (mode2>4 || mode2<1)
        {
            system("cls");
            std::cout << "Ошибка, возможен выбор 1-4 /n";
            _getch();
        }
        else cont = false;
        system("cls");
    }
    FileOne.Read();
    system("cls");
    switch (mode2)
    {
    case 1:
    {
        if (mode == 1)
        {
            crypter.En3DesOFB(FileOne.GetData(), "qk'ac}a4", "84*'sg!q", "`'-a62h#j");
        }
        else
        {
            crypter.EnOFB(FileOne.GetData(), "qk'ac}a4");
        }

    }break;
    case 2:
    {
        if (mode == 1)
        {
            crypter.En3DesCFB(FileOne.GetData(), "qk'ac}a4", "84*'sg!q", "`'-a62h#j");
        }
        else
        {
            crypter.EnCFB(FileOne.GetData(), "qk'ac}a4");
        }
    }break;
    case 3:
    {
        if (mode == 1)
        {
            crypter.En3DesCBC(FileOne.GetData(), "qk'ac}a4", "84*'sg!q", "`'-a62h#j");
        }
        else
        {
            crypter.EnCBC(FileOne.GetData(), "qk'ac}a4");
        }
    }break;
    case 4:
    {
        if (mode == 1)
        {
            crypter.En3DesECB(FileOne.GetData(), "qk'ac}a4", "84*'sg!q", "`'-a62h#j");
        }
        else
        {
            crypter.EnECB(FileOne.GetData(), "qk'ac}a4");
        }
    }break;
    }
    system("cls");
   
    CriptFile.GetData() = crypter.GetEncData();
    CriptFile.WriteData();
    CriptFile.GetData().clear();
    CriptFile.Read();
    system("cls");
   
    switch (mode2)
    {
    case 1:
    {
        if (mode == 1)
        {
            crypter.De3DesOFB(CriptFile.GetData(), "qk'ac}a4", "84*'sg!q", "`'-a62h#j");
        }
        else
        {
            crypter.DeOFB(CriptFile.GetData(), "qk'ac}a4");
        }

    }break;
    case 2:
    {
        if (mode == 1)
        {
            crypter.De3DesCFB(CriptFile.GetData(), "qk'ac}a4", "84*'sg!q", "`'-a62h#j");
        }
        else
        {
            crypter.DeCFB(CriptFile.GetData(), "qk'ac}a4");
        }
    }break;
    case 3:
    {
        if (mode == 1)
        {
            crypter.De3DesCBC(CriptFile.GetData(), "qk'ac}a4", "84*'sg!q", "`'-a62h#j");
        }
        else
        {
            crypter.DeCBC(CriptFile.GetData(), "qk'ac}a4");
        }
    }break;
    case 4:
    {
        if (mode == 1)
        {
            crypter.De3DesECB(CriptFile.GetData(), "qk'ac}a4", "84*'sg!q", "`'-a62h#j");
        }
        else
        {
            crypter.DeECB(CriptFile.GetData(), "qk'ac}a4");
        }
    }break;
    }
    

    system("cls");
    DeCriptFile.GetData() = crypter.GetDecData();
    DeCriptFile.WriteData();
    system("cls");
    system("pause");
    return 0;
}