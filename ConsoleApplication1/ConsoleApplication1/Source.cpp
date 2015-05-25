#include<tchar.h>
#include<Windows.h>
#include<iostream>
#include<string>
#include<fstream>
#include "Shlwapi.h"
#pragma comment(lib, "shlwapi.lib")
class IniStream
{
public:
	IniStream(std::wstring const& filepath){
		filefullpath = filepath;
		was_no_exist = (!PathFileExists(filepath.c_str()));
		if (was_no_exist){
			create_UTF16_file();
		}
	}
	bool is_now_created() const {
		return was_no_exist;
	}
	bool edit(std::wstring const& section, std::wstring const& key, std::wstring const& str);
private:
	void create_UTF16_file();
	std::wstring filefullpath;
	bool was_no_exist;
};

void IniStream::create_UTF16_file(){
	if (was_no_exist || !PathFileExists(this->filefullpath.c_str())){
		constexpr wchar_t BOM = 0xFEFF;
		std::wofstream wfout;
		wfout.open(this->filefullpath, std::ios_base::binary);
		wfout << BOM;
	}
}
bool IniStream::edit(std::wstring const& section, std::wstring const& key, std::wstring const& str){
	return (false != WritePrivateProfileString(section.c_str(), key.c_str(), str.c_str(), this->filefullpath.c_str()));
}
int main(void){
	const int test_num = [](){
		int tmp;
		std::cout << "’l‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢B" << std::endl;
		std::cin >> tmp;
		return tmp;
	}();
	const std::wstring filename = L"Test.ini";
	wchar_t dir[MAX_PATH];
	if (!GetCurrentDirectory(MAX_PATH, dir)) throw "getcurrentdirctory err.";
	IniStream ini(dir + (L"\\" + filename));
	const auto err = ini.edit(L"Test", L"Test1", std::to_wstring(test_num));
	const auto err2 = ini.edit(L"Test", L"Test2", std::to_wstring(test_num + 1));
	std::wcout << err << std::endl;
	return 0;
}