#pragma once
namespace Utility
{
	wstring GetExtention(wstring path);

	string ToString(wstring str);
	wstring ToWString(string str);

	wstring GetProjectDir();
	wstring GetTextureDir();
	wstring GetTextDataDir();

	bool StartsWith( string str,  string start);
	bool StartsWith(wstring str, wstring start);

	vector<string> SplitString(string origin, string token);

	string GetFileName(string path);
	string GetFileNameWithoutExtention(string path);


	void CreateFolder(string path);
};

