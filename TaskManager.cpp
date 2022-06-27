#include<iostream>
#include<Windows.h>
#include<TlHelp32.h>

using namespace std;

INT ProcessList()
{
	int n=1;
	int error;
	HANDLE hProcessSnap; 
	PROCESSENTRY32 pe32; 
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return 1;
	}
	pe32.dwSize = sizeof(PROCESSENTRY32); 
	error=Process32First( hProcessSnap, &pe32 );
	if (error==ERROR_NO_MORE_FILES)
	{ 
		return 2;
	}
	do 
	{ 
		error=printf( TEXT("\n\n=====================================================" ));
		if (error < 0)
		{ 
			return 3;
		}
		error=printf( TEXT("\n %d.PROCESS NAME: %s"),n, pe32.szExeFile ); 
		if (error < 0) 
		{
			return 4;
		}
		error=printf( TEXT("\n-------------------------------------------------------" ));
		if (error < 0)
		{ 
		return 5;
		}
		error=printf( TEXT("\n Process ID = 0x%08X"), pe32.th32ProcessID );
		if (error < 0)
		{ 
		return 6;
		}
		n++; 
	} 
	while( Process32Next( hProcessSnap, &pe32 ) ); 
	error=CloseHandle(hProcessSnap);
	if (error==0) 
	{
		return 7;
	} 
	return 0;
}

int Fgets_s(char *St, int Len) 
{
	char* Ret_val;
	if (Len <= 0)
	{ 
		return 1; 
	}
	int i = 0;
	Ret_val = fgets(St, Len, stdin);
 	if (Ret_val == NULL)
 	{
  		return 2; 
	}
  	else 
  	{
    	if (St[i] == '\n' || St[i] == '\0')
    	{
      		return 3; 
      	}
    while (St[i] != '\n' && St[i] != '\0')
    {
      i++;
	}
    if (St[i] == '\n')
    {
      St[i] = '\0';
	}
    else 
      {
	  	while (getchar() != '\n')
	  	{
        	continue;
    	}
	}
    return 0;
  }
}


INT TerminateMyProcess(DWORD dwProcessId, UINT uExitCode) 
{
  int error;
  DWORD dwDesiredAccess = PROCESS_TERMINATE;
  BOOL bInheritHandle = 1;
  HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
  if (hProcess == NULL) 
  {
  	return 1;
  }
  BOOL result = TerminateProcess(hProcess, uExitCode);
  if (result == NULL)
  { 
  	return 2;
  }
  error=CloseHandle(hProcess);
  if (CloseHandle == NULL)
  { 
  	return 3;
  }
  return 0;
}


INT GetProcessId(const char * Nameprocess) 
{
  int error;
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  DWORD dwPriorityClass;
  hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (hProcessSnap == INVALID_HANDLE_VALUE) 
  {
    return 1;
  }
  pe32.dwSize = sizeof(PROCESSENTRY32);
  if (!Process32First(hProcessSnap, & pe32))
  {
    CloseHandle(hProcessSnap); 
    return 2;
  }
  do
	{
    	if (strcmp(Nameprocess, pe32.szExeFile) == 0)
    	{
    	  return pe32.th32ProcessID;
    	}
  	} 
	while (Process32Next(hProcessSnap, & pe32));
	error = CloseHandle(hProcessSnap);
	if (error==NULL)
	{ 
		return 3;
	}
	return 0;
}



int main()
{	
	int error;
	int x=ProcessList();
	if (x==1)
	{
		cout << "\nError in function ProcessList: CreateToolhelp32Snapshot error 1 ";
		return 1;
	}
	if (x==2)
	{
		cout << "\nError in function ProcessList:Process32First error 1";
		return 2;
	}
	if (x==3)
	{
		cout << "\nError in function ProcessList: printf error 1";
		return 3;
	}
	if (x==4)
	{
		cout << "\nError in function ProcessList: printf error 2";
		return 4;
	}
	if (x==5)
	{
		cout << "\nError in function ProcessList: printf error 3";
		return 5;
	}
	if (x==6)
	{
		cout << "\nError in function ProcessList: printf error 4";
		return 6;
	}
	if (x==7)
	{
		cout << "\nError in function ProcessList: CloseHandle error 1 ";
		return 7;
	}
	Again:
	BOOL result=10;
	int Re_gets=10, Re_scan;
	char * Name_path = (char *) malloc(MAX_PATH * sizeof(char));
  	if (Name_path == NULL)
  	{
    	printf("\nError in function main: malloc failed 1");
    	return 8;
  	}
	error=printf("\nInput name file exe of process: ");
	if(error<0)
	{
		printf("Error in function main: printf call error 1");
		return 9;
	}
	do
  	{
    	Re_gets = Fgets_s(Name_path, MAX_PATH);
  		while (Re_gets == 1)
    	{
    		error=printf("String lenghth must be greater than 0 ");
    		if(error<0)
    		{
    			printf("Error in function main: printf call error 2");
    			return 10;
			}
    		Re_gets = Fgets_s(Name_path, MAX_PATH);
    	}
    	if (Re_gets == 2)
    	{
    		cout << "Error in function Fgets_s: fgets error 1";
    		return 11;
    	}
    	while (Re_gets == 3)
    	{
    		error=printf("Input string can't be empty");
    		if (error<0)
    		{
    			printf("Error in function main: printf call error 3");
    			return 12;
			}
    		Re_gets = Fgets_s(Name_path, MAX_PATH);
    	}
	}
	while (Re_gets != 0);
  	int Process_id = GetProcessId(Name_path);
  	if (Process_id == 1)
  	{
    	cout << "\nError in function GetProcessList: hProcessSnap error 1 ";
    	return 13;
  	}
  	if (Process_id == 2)
  	{
    	cout << "\nError in function GetProcessList: Process32First error 1";
    	return 14;
  	}
  	if (Process_id == 3)
  	{
    	cout << "\nError in function GetProcessList: CloseHandle error 1";
    	return 15;
  	}
	result = TerminateMyProcess(Process_id, 1);
    	if (result == 0)
    	{
    		error=printf("\nProcess terminated :)");
    			if (error<0)
    			{	
    				printf("Error in function main: printf call error 4");
    				return 16;
				}
    		return 0;
		}
		if (result == 1)
    	{
    		error=printf("\nCan't find process.Try again.");
    		if (error<0)
    		{
    			printf("Error in function main: printf call error 5");
    			return 17;
			}
			goto Again;
    	}
    	if (result == 2)
    	{
    		cout << "\nError in function TerminateMyProcess: TerminateProcess error 1"<< endl;
    		return 18;
		}
    	if (result == 3)
    	{
    		cout << "\nError in function TerminateMyProcess: CloseHandle error 1"<< endl;
    		return 19;
		}
 	system("pause");
  	return 0;
}
