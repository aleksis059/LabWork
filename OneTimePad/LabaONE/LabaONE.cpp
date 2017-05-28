
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <windows.h>
#include <time.h>
#define Reding std::ios::in | std::ios::binary
#define Writing std::ios::binary | std::ios::out | std::ios::trunc


class Files
{
private:

	std::fstream Readingfile;
	std::fstream Writingfile;
	std::vector<char> _data;


public:
	std::string	_fileone;
	Files(std::string &fileone)
		:_fileone(fileone)
	{
	}
	~Files()
	{
	}



	int _reading()
	{
		bool a = false;
		Readingfile.open(_fileone, Reding);
		if (!Readingfile.is_open())
			a = true;
		else
		{
			char temp;
			while (!Readingfile.eof())
			{
				Readingfile.get(temp);
				if (Readingfile.eof()) break;
				_data.push_back(temp);
			}
			Readingfile.close();
			a = false;
		}

		return(a);
	}


	int _writing()
	{
		bool b = false;
		Writingfile.open(_fileone, Writing);
		char temp;
		if (!Writingfile.is_open())
			b = true;
		else
		{
			for (unsigned int i = 0; i < _data.size(); i++)
			{
				temp = _data.at(i);
				Writingfile << temp;
			}
			Writingfile.close();
			b = false;
		}


		return(b);
	}

	void GenerationKey(int _sizekey)
	{
		srand(time(NULL));
		for (int i = 0; i < _sizekey; i++)
		{
			_data.push_back(0 + rand() % 255);
		}
	}
	std::vector<char> &GetData() { return _data; }

};
	void Shifr(Files &key, Files &file, Files &ShifrFile)
	{
		ShifrFile.GetData().clear();
		for (unsigned int i = 0; i < file.GetData().size(); i++)
			ShifrFile.GetData().push_back(file.GetData().at(i) ^ key.GetData().at(i));
		if (ShifrFile._writing())
		{
			std::cout << "No FIle   ";
			system("pause");
			return;
		}
	}


	void Deshifr(Files &key, Files &ShifrFile, Files &SourceFile)
	{
		return Shifr(ShifrFile, key, SourceFile);
	}


void main()
{
	std::string fileone = "Ishodnik.docx";
	std::string filetwo = "fileKey.docx";
	std::string filetthree = "CriptoFile.docx";
	std::string filefour = "Rasshifrovka.docx";


	Files fileKey(filetwo), 
		SourceFile(fileone), 
		ShifrFile(filetthree), 
		ShifrFile2(filefour);
	if (SourceFile._reading())
	{
		std::cout << "No FIle   ";
		system("pause");
		return;
	}
	fileKey.GenerationKey(SourceFile.GetData().size());
	fileKey._writing();
	fileKey.GetData().clear();
	if (fileKey._reading())
	{
		std::cout << "No FIle   ";
		system("pause");
		return;
	}
	
	Shifr(fileKey, SourceFile, ShifrFile);
	Deshifr(fileKey, ShifrFile, ShifrFile2);

}