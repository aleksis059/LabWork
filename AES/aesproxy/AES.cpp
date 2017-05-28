#include <clocale>
#include "AESmode.h"
#include <conio.h>
int main()
{	setlocale(LC_CTYPE,"Russian");
    unsigned char key[] = "asdcfgjrsuhfnrh";
    std::string path1 = "Ishodnik.docx";
    std::string path2 = "Shifr.docx";
    std::string path3 = "deshifr.docx";
    File plain(path1);
    File cypher(path2);
    File decrypted(path3);
    AesProxy crypter;
    bool cont = true;
    int mode;
    while (cont)
    {
        std::cout << "Âûáåðèòå ðåæèì: 1=OFB, 2=CFB, 3=CTR ,  4=CBC,  5=ECB\n";
        std::cin >> mode;
        if (mode > 5 || mode < 1)
        {
            system("cls");
            std::cout << "Îøèáêà, âîçìîæíûå íîìåðà ðåæèìîâ 1-5";
            _getch();
        }
        else cont = false;
        system("cls");
    }

    std::cout << "Èäåò ñ÷èòûâàíèå Ishodnik.docx...";
    plain.ReadData();
    system("cls");
    std::cout << "Èäåò Øèôðîâàíèå Ishodnik.docx...";
    
	switch (mode)
    {
	case 1:crypter.EnOFB(plain.GetData(), key); break;
    case 2:crypter.EnCFB(plain.GetData(), key); break;
	case 3:crypter.EnCTR(plain.GetData(), key); break;
    case 4:crypter.EnCBC(plain.GetData(), key); break;
	case 5:crypter.EnECB(plain.GetData(), key); break;
    }
    system("cls");
    std::cout << "Èäåò çàïèñü Shifr.docx";
    cypher.GetData() = crypter.GetEncData();
    cypher.WriteData();
    system("cls");
    std::cout << "Èäåò äåøèôðîâàíèå Shifr.docx";
    
	switch (mode)
    {
	case 1:crypter.DeOFB(cypher.GetData(), key); break;
    case 2:crypter.DeCFB(cypher.GetData(), key); break;
    case 3:crypter.DeCTR(cypher.GetData(), key); break;
    case 4:crypter.DeCBC(cypher.GetData(), key); break;
	case 5:crypter.DeECB(cypher.GetData(), key); break;
    
    }
    system("cls");
    std::cout << "Çàïèñü äåøèôðîâàíèÿ deshifr.docx";
    decrypted.GetData() = crypter.GetDecData();
    decrypted.WriteData();
    system("cls");
    system("pause");
}
