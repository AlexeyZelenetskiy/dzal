#include "stdafx.h"
#include "file.h"


file::file(void) : folder()
{
	this->data="";
	this->pref=".f";
}



file::~file(void)
{
}


file::file(user* u, string name) : folder(u, name)
{
	this->data="";
	this->pref=".f";
}


void file::set_data()
{
	if(this->uptr->get_adm() == true)
	{
	  string info;
	  cout<<"enter the information that you want to write to a file:  ";
	  cin>>info;
	  this->data=info;
	}
	else
	  cout<<"you can not change this file"<<endl;
}


string file::get_data()
{
	return this->data;	   
}
