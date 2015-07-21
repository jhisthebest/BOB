#include "stdafx.h"
#include <Windows.h>
#include <stdint.h>


void print(_In_ const char* fmt, _In_ ...)
{
        char log_buffer[2048];
    va_list args;
 
    va_start(args,fmt);
    HRESULT hRes = StringCbVPrintfA(log_buffer, sizeof(log_buffer), fmt, args);
    if (S_OK != hRes)
    {
        fprintf(
            stderr,
            "%s, StringCbVPrintfA() failed. res = 0x%08x",
            __FUNCTION__,
            hRes
            );
        return;
    }
 
    OutputDebugStringA(log_buffer);
    fprintf(stdout, "%s \n", log_buffer);
}
 
 PCHAR file_view = (PCHAR)(MapViewOfFile,
		0,
		0,
		0
		);

wchar_t strUni[256] =L"유니코드";
char strUtf8[256] ={0,};
int nLen = MultiByteToWideChar(CP_UTF8, 0, file_view, -1, NULL, 0);
WideCharToMultiByte (CP_UTF8, 0, strUni, lstrlenW(strUni), strUtf8, nLen, NULL, NULL);

bool create_bob_txt()
{
    // current directory 를 구한다.
    wchar_t *buf=NULL;
    uint32_t buflen = 0;
    buflen = GetCurrentDirectoryW(buflen, buf);
        if (0 == buflen)
        {
        print("err, GetCurrentDirectoryW() failed. gle = 0x%08x", GetLastError());
        return false;
        }
 
        buf = (PWSTR) malloc(sizeof(WCHAR) * buflen);
        if (0 == GetCurrentDirectoryW(buflen, buf))
        {
                print("err, GetCurrentDirectoryW() failed. gle = 0x%08x", GetLastError());
                free(buf);
                return false;
        }
 
    // current dir \\ bob.txt 파일명 생성
    wchar_t file_name[260];
    if (!SUCCEEDED(StringCbPrintfW(
                            file_name,
                            sizeof(file_name),
                            L"%ws\\bob.txt",
                            buf)))
    {  
        print("err, can not create file name");
        free(buf);
        return false;
    }
    free(buf); buf = NULL;
 
    if (true == is_file_existsW(file_name))
    {
        ::DeleteFileW(file_name);
    }
 
    // 파일 생성
    HANDLE file_handle = CreateFileW(
                                file_name,
                                                        GENERIC_WRITE,
                                                        FILE_SHARE_READ,
                                                        NULL,
                                                        CREATE_NEW,
                                                        FILE_ATTRIBUTE_NORMAL,
                                                        NULL); 
        if(file_handle == INVALID_HANDLE_VALUE)
        {                                              
        print("err, CreateFile(path=%ws), gle=0x%08x", file_name, GetLastError());
        return false;
        }
 
    // 파일에 데이터 쓰기
    DWORD bytes_written = 0;
    wchar_t string_buf[1024];
    if (!SUCCEEDED(StringCbPrintfW(
                        string_buf,
                        sizeof(string_buf),
                        L"동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라만세")))
    {
        print("err, can not create data to write.");
        CloseHandle(file_handle);
        return false;
    }
 
    if (!WriteFile(file_handle, string_buf, wcslen(string_buf), &bytes_written, NULL))
    {
        print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
        CloseHandle(file_handle);
        return false;
    }
 
    // 영어로 쓰기
    if (!SUCCEEDED(StringCbPrintfW(
                        string_buf,
                        sizeof(string_buf),
                        L"All work and no play makes jack a dull boy.")))
    {
        print("err, can not create data to write.");
        CloseHandle(file_handle);
        return false;
    }
 
    if (!WriteFile(file_handle, string_buf, wcslen(string_buf), &bytes_written, NULL))
    {
        print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
        CloseHandle(file_handle);
        return false;
    }
 
 
 
 
    char string_bufa[1024];
    if (!SUCCEEDED(StringCbPrintfA(
                        string_bufa,
                        sizeof(string_bufa),
                        "동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라만세")))
    {
        print("err, can not create data to write.");
        CloseHandle(file_handle);
        return false;
    }
 
    if (!WriteFile(file_handle, string_bufa, strlen(string_bufa), &bytes_written, NULL))
    {
        print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
        CloseHandle(file_handle);
        return false;
    }
 
    // 영어로 쓰기
    if (!SUCCEEDED(StringCbPrintfA(
                        string_bufa,
                        sizeof(string_bufa),
                        "All work and no play makes jack a dull boy.")))
    {
        print("err, can not create data to write.");
        CloseHandle(file_handle);
        return false;
    }
 
    if (!WriteFile(file_handle, string_bufa, strlen(string_bufa), &bytes_written, NULL))
    {
        print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
        CloseHandle(file_handle);
        return false;
    }
 
    // 파일 닫기
    CloseHandle(file_handle);
    return true;
 
}

void copy_bob_txt(wchar_t *bob_txt, wchar_t *bob2_txt)
{
	// Copy file
	CopyFile(bob_txt, bob2_txt, FALSE);



	HANDLE filehandle = CreateFileW(
		fname,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	wchar_t fname[260];
	if (!SUCCEEDED(StringCbPrintfW(
		fname,
		sizeof(fname),
		L"%ws\\bob2.txt",
		buf)))
	{
		print("err, can not create file name");
		free(buf);
		return false;
	}
	free(buf);

}

char readbuf[2048];
	WCHAR Wbuf[1024];
	DWORD dwRead;
	int r, i ;
	r = ReadFile(filehandle, read, readbuf, &dwRead, NULL);
	

int _tmain(int argc, _TCHAR* argv[])
{
	create_bob_txt();
	copy_bob_txt();

	CloseHandle(filehandle);

	DeleteFile(fname);

	return 0;
}