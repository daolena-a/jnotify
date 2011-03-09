#include <stdio.h>
#include "Win32FSHook.h"

int c1 = 0;
int c2 = 0;
int c3 = 0;
void callback(int watchID, int action, const WCHAR* rootPath, const WCHAR* filePath)
{
	switch(action)
	{
	case 1:
		c1++;
		break;
	case 2:
		c2++;
		break;
	case 3:
		c3++;
		break;
	}
//	fprintf(stdout, "%d : action=%d, root=%ls, path=%ls\n", watchID, action, rootPath, filePath);
//	fflush(stdout);
}
const int NWATCHES = 5000;
const int NFILES = 2;

void CreateFiles(wchar_t *dir, int nfiles)
{
	char b[1000];
	for(int i =0;i<nfiles;i++)
	{
		sprintf(b, "%ls\\file_%d", dir, i*10);
		remove(b);
		FILE *f = fopen(b, "a");
		fwrite("abc", 3, 1, f);
		fclose(f);
	}
}
int main(char **argv, int argc)
{
	long long CHANGE_FILE_NAME   = 0x00000001;
	long long CHANGE_DIR_NAME    = 0x00000002;
	long long CHANGE_ATTRIBUTES  = 0x00000004;
	long long CHANGE_SIZE        = 0x00000008;
	long long CHANGE_LAST_WRITE  = 0x00000010;
	long long CHANGE_LAST_ACCESS = 0x00000020;
	long long CHANGE_CREATION    = 0x00000040;
	long long CHANGE_SECURITY    = 0x00000100;

	Win32FSHook *hook = new Win32FSHook();
	hook->init(callback);
	Sleep(1000);
	DWORD error;
	int w[NWATCHES];
//	Sleep(3000);
	printf("adding watches\n");fflush(stdout);
	for(size_t i =0;i<sizeof(w) / sizeof(int);i++)
	{
		wchar_t b[1000];
		swprintf(b, L"%ls%d",L"c:\\Users\\omry\\tmp\\", i);
		CreateDirectoryW(b, 0);
		w[i] = hook->add_watch(b, CHANGE_SECURITY
				| CHANGE_CREATION
				| CHANGE_LAST_ACCESS
				| CHANGE_LAST_WRITE
				| CHANGE_SIZE
				| CHANGE_ATTRIBUTES
				| CHANGE_DIR_NAME
				| CHANGE_FILE_NAME,
				true,
				error);
		CreateFiles(b, NFILES);
	}

	Sleep(1000);
	printf("removing watches\n");fflush(stdout);
	for(size_t i =0;i<sizeof(w) / sizeof(int);i++)
	{
		hook->remove_watch(w[i]);
	}

	printf("removed\n");fflush(stdout);
	printf("c1 : %d, c2 = %d, c3 = %d\n", c1, c2 ,c3);fflush(stdout);
//	printf("deleting Win32FSHook\n");fflush(stdout);
//	delete hook;.
//	printf("deleted\n");fflush(stdout);
}
