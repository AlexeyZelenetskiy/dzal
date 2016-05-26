#pragma once
#include "folder.h"
#include "file.h"
class siml :
	public folder
{
public:
	file* item;

	siml(void);
	siml(user* u, string name);
	~siml(void);
};

