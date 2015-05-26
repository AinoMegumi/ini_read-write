#include "ini_read-write.h"
#include <Shlwapi.h>
#include <string>
#include <fstream>
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "Kernel32.lib")
std::string getLastErrorText();
static inline void clearErr();
IniStream::IniStream(std::wstring const& filepath_or_name) {
	if (L':' != filepath_or_name.at(1)) {
		wchar_t dir[MAX_PATH];
		if (!GetCurrentDirectory(MAX_PATH, dir)) throw "getcurrentdirctory err.";
		this->filefullpath = dir + (L"\\" + filepath_or_name);
	}
	else {
		this->filefullpath = filepath_or_name;
	}
	this->was_no_exist = (!PathFileExists(filefullpath.c_str()));
	if (was_no_exist) {
		create_UTF16_file();
	}
}
bool IniStream::is_now_created() const {
	return this->was_no_exist;
}
void IniStream::create_UTF16_file() {
	if (this->was_no_exist || !PathFileExists(this->filefullpath.c_str())) {
		constexpr wchar_t BOM = 0xFEFF;
		std::wofstream wfout;
		wfout.open(this->filefullpath, std::ios_base::binary);
		wfout << BOM;
	}
}
void IniStream::edit(std::wstring const& section, std::wstring const& key, std::wstring const& str) {
	clearErr();
	if (false == WritePrivateProfileString(section.c_str(), key.c_str(), str.c_str(), this->filefullpath.c_str())) {
		throw std::runtime_error("IniStream::edit : " + getLastErrorText());
	}
}
static inline void clearErr() {
	SetLastError(NO_ERROR);
}
std::string getLastErrorText(){
	char* buf = nullptr;
	const auto lasterr = GetLastError();
	const auto len = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ARGUMENT_ARRAY,
		nullptr,
		lasterr,
		LANG_NEUTRAL,
		(LPSTR)&buf,
		0,
		nullptr
	);
	auto i = len - 3;
	for (; '\r' != buf[i] && '\n' != buf[i] && '\0' != buf[i]; i++);//改行文字削除
	buf[i] = '\0';
	std::string ret = buf + ("(" + std::to_string(lasterr)) + ")";//エラーメッセージ作成
	LocalFree(buf);//FormatMessageAでFORMAT_MESSAGE_ALLOCATE_BUFFERを指定したので必ず開放
	return ret;
}