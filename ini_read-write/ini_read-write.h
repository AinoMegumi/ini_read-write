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
