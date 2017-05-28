#include <ctime>
#include <map>
#include <algorithm>
#include <iterator>
#include <windows.h>
#include <conio.h>
#include <tlhelp32.h>
#include <iostream>
#include <psapi.h> 

class TracingProc
{



private:
    HANDLE CONST _descrypt;
    std::map <DWORD, std::string> NewProcess;
    std::map  <DWORD, std::string> OldProcess;
   
	VOID WayProcess(DWORD ProcessId)
    {
        DWORD temp;
        TCHAR Buffer[MAX_PATH];
        HANDLE desryptProcces = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, FALSE, ProcessId);
        if (GetModuleFileNameEx(desryptProcces, NULL, Buffer, MAX_PATH) != 0)
        {
			wsprintf(Buffer, "%s \n", Buffer);
            
        }
        else
        {
			wsprintf(Buffer, "Hidden Directory \n");
           
        }
        
		WriteConsole(_descrypt, &Buffer, lstrlen(Buffer), &temp, NULL);
        
		CloseHandle(desryptProcces);
    }

	VOID PrintUpdatedProcess(std::map <DWORD, std::string> diff)
	{
		DWORD temp;
		TCHAR Buffer[512];

		for (auto i = diff.begin(); i != diff.end(); i++)
		{
			if (NewProcess.count(i->first) > 0)
			{
				wsprintf(Buffer, "OPEN PROCESS:NameProcess: %08X %s ", i->first, i->second.c_str());
				WriteConsole(_descrypt, &Buffer, lstrlen(Buffer), &temp, NULL);
				WayProcess(i->first);
			}


			if (OldProcess.count(i->first) > 0)
			{
				wsprintf(Buffer, "CLOSED PROCESS:NameProcess: %08X %s ", i->first, i->second.c_str());
				WriteConsole(_descrypt, &Buffer, lstrlen(Buffer), &temp, NULL);
				WayProcess(i->first);
			}
		}
	}


public:
    TracingProc(HANDLE CONST descrypt) :_descrypt(descrypt)
    {

    }
    
	
    
	VOID RestartProcces()
    {
        OldProcess = NewProcess;
        NewProcess.clear();
        ProcList();
        std::map  <DWORD, std::string> difference;
        std::set_symmetric_difference(OldProcess.begin()
			, OldProcess.end()
            , NewProcess.begin()
			, NewProcess.end()
            , inserter(difference, difference.end()));
        PrintUpdatedProcess(difference);
    }

	VOID ProcList()
	{
		PROCESSENTRY32 peProcessEntry;
		HANDLE CONST hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (INVALID_HANDLE_VALUE == hSnapshot)
			return;
		peProcessEntry.dwSize = sizeof(PROCESSENTRY32);
		Process32First(hSnapshot, &peProcessEntry);
		do
		{
			NewProcess.insert(std::pair<DWORD, std::string>(peProcessEntry.th32ProcessID, peProcessEntry.szExeFile));
		} while (Process32Next(hSnapshot, &peProcessEntry));
		CloseHandle(hSnapshot);
	}
};

int main(int argc, char* argv[])
{
	bool timer = false;
    HANDLE CONST descrypt = GetStdHandle(STD_OUTPUT_HANDLE);
    TracingProc _TracingProc(descrypt);
	_TracingProc.ProcList();
    
   
	while (!timer)
    {
        Sleep(150);
		_TracingProc.RestartProcces();
    }
}
