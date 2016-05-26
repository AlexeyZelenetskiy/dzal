#include "stdafx.h"
#include "folder.h"
#include "file.h"
#include "siml.h"

folder::folder(void)
{
	this->uptr=nullptr;
	this->parrent=nullptr;
	this->pref=".d";
}


folder::folder(user* u, string name)
{
	this->uptr=u;
	this->parrent=nullptr;
	this->name=name;
	this->pref=".d";
}

folder::~folder(void)
{
	delete uptr;
	delete parrent;
	v.clear();
}

void folder::print_all(folder* root)
{
 if(root->pref == ".d")
	if(root->parrent != nullptr)
	   cout<<root->name<<root->pref<<"("<<root->parrent->name<<root->parrent->pref<<")"<<endl;
	else
	   cout<<root->name<<root->pref<<endl;
 /*else
	   cout<<"   "<<root->name<<root->pref<<"("<<root->parrent->name<<root->parrent->pref<<")"<<endl;*/
    for(unsigned int i=0; i<root->v.size(); i++)
		if(root->v[i]->pref == ".f" || root->v[i]->pref == ".&")
		  cout<<"   "<<root->v[i]->name<<root->v[i]->pref<<"("<<root->name<<root->pref<<")"<<endl;
	for(unsigned int i=0; i<root->v.size(); i++)
		if(root->v[i]->pref == ".d")
			root->print_all(root->v[i]);
}


void folder::list()
{
	if(this->parrent != nullptr)
	   cout<<this->name<<this->pref<<"("<<this->parrent->name<<this->parrent->pref<<")"<<endl;
	else
	   cout<<this->name<<this->pref<<endl;
	for(unsigned int i=0; i<this->v.size(); i++)
	   cout<<this->v[i]->name<<this->v[i]->pref<<endl;
}


void folder::create_folder(string name)
{
	for(unsigned int i=0; i<this->v.size(); i++)
	  if(this->v[i]->name == name && this->v[i]->pref == ".d")
	     throw 1; 
	folder* item=new folder(this->uptr, name);
	item->parrent=this;
    this->v.push_back(item);
}


void folder::create_siml(string name, string nf)
{
	int k=0;
	for(unsigned int i=0; i<this->v.size(); i++)
	  if(this->v[i]->name == name && this->v[i]->pref == ".&")
	     throw 13;
	siml* item=new siml(this->uptr, name);
	item->parrent=this;
	for(unsigned int i=0; i<this->v.size(); i++)
	 if(this->v[i]->name == nf && this->v[i]->pref == ".f")
	 {
	   item->item=(file*)(this->v[i]);
	   k++;
	 }
	if(k == 0)
	  cout<<"we can't find this file"<<endl;
	else
	  this->v.push_back(item);
}

void folder::create_file(string name)
{
	for(unsigned int i=0; i<this->v.size(); i++)
	 if(this->v[i]->name == name && this->v[i]->pref == ".f")
	    throw 2; 
	file* item=new file(this->uptr, name);
	item->parrent=this;
	item->set_data();
	this->v.push_back(item);
}


folder* folder::change_folder(string name)
{
	folder* item=nullptr;
	unsigned int i=0;
	while(i != this->v.size())
	{
		if(this->v[i]->name == name  && this->v[i]->pref == ".d")
		   item=v[i];
		i++;
   }
   if(item == nullptr)
	  throw 3;
   return item;
}


folder* folder::previous()
{
	if(this->parrent == nullptr)
	   throw 6;
	return this->parrent;
}


void folder::delete_file(string name)
{
	int n=this->v.size();
	for(unsigned int i=0; i<this->v.size(); i++)
	  if(this->v[i]->name == name)
		  this->v.erase(this->v.begin()+i);
	if(n == this->v.size())
		throw 4;
}


void folder::delete_folder(string name)
{
   int n=this->v.size();
   for(unsigned int i=0; i<this->v.size(); i++)
	 if(this->v[i]->name == name && this->v[i]->pref == ".d")
		this->v.erase(this->v.begin()+i);
   if(n == this->v.size())
	  throw 8;
}


void folder::delete_siml(string name)
{
	int n=this->v.size();
	for(unsigned int i=0; i<this->v.size(); i++)
	  if(this->v[i]->name == name && this->v[i]->pref == ".&")
		this->v.erase(this->v.begin()+i);
   if(n == this->v.size())
	 throw 15;
}
void folder::read_file(string name)
{
	file* item=nullptr;
	for(unsigned int i=0; i<this->v.size(); i++)
		if(this->v[i]->name == name && this->v[i]->pref == ".f")
			item=(file*)(this->v[i]);
	if(item == nullptr)
	   throw 5;
    cout<<"    "<<item->name<<item->pref<<endl;
	cout<<"data: "<<item->get_data()<<endl;
}


void folder::write_file(string name)
{
	file* item=nullptr;
	for(unsigned int i=0; i<this->v.size(); i++)
	   if(this->v[i]->name == name && this->v[i]->pref == ".f")
		  item=(file*)(this->v[i]);
	if(item == nullptr)
	  throw 11;
	item->set_data();
}


void folder::open_siml(string name)
{
	siml* item=nullptr;
	for(unsigned int i=0; i<this->v.size(); i++)
	  if(this->v[i]->name == name && this->v[i]->pref == ".&")
		  item=(siml*)(this->v[i]);
	if(item == nullptr)
	  throw 15;
	cout<<"What do you want to do with file(W or R):  ";
    char a;
	cin>>a;
    if(a == 'W')
		item->item->set_data();
    else
		cout<<"data: "<<item->item->get_data()<<endl;
}


void folder::change_user(user* u, folder* root)
{
   root->uptr=u;
   for(unsigned int i=0; i<root->v.size(); i++)
	   if(root->v[i]->pref == ".f")
		   root->v[i]->uptr=u;
	   else
		   root->change_user(u, root->v[i]);
}


void folder::find_file(string name)
{
   unsigned int k=0;
   for(unsigned int i=0; i<this->v.size(); i++)
	 if(this->v[i]->name == name && this->v[i]->pref == ".f")
	  {
		  k++;
		  cout<<"    "<<this->v[i]->name<<this->v[i]->pref<<"("<<this->v[i]->parrent->name<<this->v[i]->parrent->pref<<")"<<endl;
		  cout<<"Is this the file you were looking for?"<<endl;
		  cout<<"Y or N"<<"  ";
		  char a;
		  cin>>a;
		  if(a == 'Y')
		  {
			  cout<<"What do you want to do with file(W or R):  ";
			  cin>>a;
			  if(a == 'W')
				  this->write_file(name);
			  else
				  this->read_file(name);
			  break;
		  }
	  }
	 else
	  if(this->v[i]->pref == ".d")
		this->v[i]->find_file(name);
     if(k == 0)
	   throw 11;
}


void folder::copy_folder(string name)
{
	for(unsigned int i=0; i<this->v.size(); i++)
	  if(this->v[i]->name == name  && this->v[i]->pref == ".d")
		 this->v.push_back(this->v[i]);
}

/*void folder::find__file(string nd, string nf)
{
	file* item=nullptr;
	folder* ptr=this->change_folder(nd);
	for(unsigned int i=0; i<ptr->v.size(); i++)
	   if(ptr->v[i]->pref == ".f")
		 if(ptr->v[i]->name == nf)
			 item=(file*)ptr->v[i];
   if(item == nullptr)
	 throw 5;
   cout<<item->name<<item->pref<<endl;
   cout<<"   "<<item->get_data()<<endl;
}*/