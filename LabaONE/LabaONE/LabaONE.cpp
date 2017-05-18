
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <time.h>


using namespace std;

class Files
{
private:

	fstream _Chtenie;
	fstream _write;
	vector<char> _data; //вектор для записи символов из файла


public:
	string	_fileone;		//исходник
	Files(string &fileone)
		:_fileone(fileone)
	{}~Files() {}



	int Chtenie() //чтение из файла
	{
		bool a = false;
		_Chtenie.open(_fileone, ios::in | ios::binary);
		if (_Chtenie.is_open())
		{
			char temp;
			while (!_Chtenie.eof())
			{
				_Chtenie.get(temp);
				if (_Chtenie.eof()) break;
				_data.push_back(temp);
			}
			_Chtenie.close();
			a = false;
		}
		else
			a = true;
		return(a);
	}


	int Zapis() //запись в файл
	{
		bool b = false;
		_write.open(_fileone, ios::binary | ios::out | ios::trunc);
		char temp;
		if (_write.is_open())
		{
			for (unsigned int i = 0; i < _data.size(); i++)
			{
				temp = _data.at(i);
				_write << temp;
			}
			_write.close();
			b = false;
		}
		else
			b = true;
		return(b);
	}

	void SozdanieKey(int Razmer) // генерация ключа
	{
		srand(time(NULL));
		for (int i = 0; i < Razmer; i++)
		{
			_data.push_back(0 + rand() % 255);
		}
	}
	vector<char> &GetData() { return _data; } //вектор файлов
};

void Shifr(Files &key, Files &file, Files &ShifrFile) // шифрование
{
	ShifrFile.GetData().clear();
	for (unsigned int i = 0; i < file.GetData().size(); i++)
		ShifrFile.GetData().push_back(file.GetData().at(i) ^ key.GetData().at(i));
	if (ShifrFile.Zapis())
	{
		cout << "No FIle   ";
		system("pause");
		return;
	}
}


void Raschifrovka(Files &key, Files &ShifrFile, Files &Ishodnik) // расшифровка
{
	return Shifr(ShifrFile, key, Ishodnik);
}


void main()
{
	string fileone = "D:/Cripto/Ishodnik.txt";
	string filetwo = "D:/Cripto/fileKey.txt";
	string filetthree = "D:/Cripto/CriptoFile.txt";
	string filefour = "D:/Cripto/Rasshifrovka.txt";


	Files fileKey(filetwo), Ishodnik(fileone), ShifrFile(filetthree), ShifrFile2(filefour);
	if (Ishodnik.Chtenie())
	{
		cout << "No FIle   ";
		system("pause");
		return;
	}
	fileKey.SozdanieKey(Ishodnik.GetData().size());
	fileKey.Zapis();
	fileKey.GetData().clear();
	if (fileKey.Chtenie())
	{
		cout << "No FIle   ";
		system("pause");
		return;
	}
	Shifr(fileKey, Ishodnik, ShifrFile);
	Raschifrovka(fileKey, ShifrFile, ShifrFile2);

}