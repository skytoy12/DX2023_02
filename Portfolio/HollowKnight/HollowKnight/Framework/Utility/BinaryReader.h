#pragma once
class BinaryReader
{
public :
	BinaryReader(wstring path);
	~BinaryReader();

	int Int();
	UINT UInt();
	float Float();
	string String();
	wstring WString();

	Vector2 Float2();

	void Byte(OUT void** data, UINT dataSize);

private :
	HANDLE _file;
	DWORD _size;
};

