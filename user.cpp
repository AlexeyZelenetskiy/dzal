#include "stdafx.h"
#include "user.h"


user::user(void)
{
	this->admin=nullptr;
}


user::user(string name)
{
	this->admin=false;
	this->name=name;
}

user::~user(void)
{
}


void user::set_rignts()
{
	this->admin=true;
}

bool user::get_adm()
{
	return this->admin;
}
