#pragma once
#include "folder.h"
class file :
	public folder
{
private:
	string data;
public:
	file(void);
	~file(void);
	file(user* u, string name);
	void set_data(); // ��������� ���������� � ����
	string get_data();
};

