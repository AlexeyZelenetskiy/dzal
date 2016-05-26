#include "stdafx.h"
#include "siml.h"


siml::siml(void) : folder()
{
	 this->pref=".&";
     this->item=NULL;
}


siml::siml(user*u, string name) : folder(u, name)
{
	this->pref=".&";
    this->item=NULL;
}
siml::~siml(void)
{
	delete item;
}
