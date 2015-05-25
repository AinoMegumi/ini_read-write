#include<tchar.h>
#include<Windows.h>
#include "ini_read-write.h"
#include<iostream>
#include<string>

int main(void){
	const int test_num = [](){
		int tmp;
		std::cout << "値を入力してください。" << std::endl;
		std::cin >> tmp;
		return tmp;
	}();
	const std::wstring filename = L"Test.ini";
	wchar_t dir[MAX_PATH];
	if (!GetCurrentDirectory(MAX_PATH, dir)) std::wcerr << "getcurrentdirctory err." << std::endl;
	try {
		IniStream ini(dir + (L"\\" + filename));
		ini.edit(L"Test", L"Test1", std::to_wstring(test_num));
		ini.edit(L"Test", L"Test2", std::to_wstring(test_num + 1));
	}
	catch (std::exception er) {
		std::cerr << er.what() << std::endl;
	}
	return 0;
}
