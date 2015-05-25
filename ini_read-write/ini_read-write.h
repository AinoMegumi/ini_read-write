#pragma once
#include <string>
class IniStream
{
public:
	IniStream(std::wstring const& filepath_or_name);
	bool is_now_created() const;
	void edit(std::wstring const& section, std::wstring const& key, std::wstring const& str);
private:
	void create_UTF16_file();
	std::wstring filefullpath;
	bool was_no_exist;
};
class IniStreamException : public std::exception
{
private:
	std::string s;
public:
	IniStreamException(std::string ss) : s(ss) {}
	~IniStreamException() throw () {} // Updated
	const char* what() noexcept(true) {
		const std::string tmp = "IniStream:" + s;
		return tmp.c_str();
	}
};
