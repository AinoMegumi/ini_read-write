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
	try {
		{
			wchar_t dir[MAX_PATH];
			if (!GetCurrentDirectory(MAX_PATH, dir)) std::wcerr << "getcurrentdirctory err." << std::endl;
			IniStream ini(dir + (L"\\" + filename));//フルパスを渡す方法、2文字目は":"のはず
			ini.edit(L"Test", L"Test1", std::to_wstring(test_num));
			ini.edit(L"Test", L"Test2", std::to_wstring(test_num + 1));
		}
		{
			IniStream ini2(filename);//ファイル名を渡す方法、Current Directryから捜索
			ini2.edit(L"Test", L"Test3", std::to_wstring(test_num + 2));
		}
	}
	catch (std::exception er) {
		std::cerr << er.what() << std::endl;
	}
	return 0;
}
