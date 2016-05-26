#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "user.h"
using namespace std;
class folder
{
public:
	//поля
	string name;
	string pref;
	vector <folder*> v;
	user* uptr;
	folder* parrent;
	//методы
	folder(void);
	folder(user* u, string name);
	~folder(void);

	void print_all(folder *root);
	void list();

	void create_folder(string name);
	void create_file(string name);
	void create_siml(string name, string nf);

	folder* change_folder(string name);  // позволяет перемещаться в одной папке между папками
	folder* previous(); // для перемещения к предыдущей папке

	void delete_file(string name);
	void delete_folder(string name);
	void delete_siml(string name);

	void read_file(string name);   
	void write_file(string name);
	void open_siml(string name);

    void change_user(user* u, folder* root); // смена пользователя 
	
	void find_file(string name); // поиск файлов
	void copy_folder(string name); // рекурсивное копирование директории 
	//void find__file(string nd, string nf);
};

