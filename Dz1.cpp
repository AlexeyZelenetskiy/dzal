// Dz1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "file.h"
#include "folder.h"
#include "user.h"



int _tmain(int argc, _TCHAR* argv[])
{
	string cmd;
	string name;
	string nf;
	user* u; // new user
	char a;
	vector<user*>p;

	cout<<"HELLO:)"<<endl;
	cout<<"create a new user: enter the name:   ";
	cin>>name;
	cout<<"enter his rights(admin(T) or not)     ";
	cin>>a;
	if(a == 'T')
	{
	    u=new user(name);   // new user with adm rights
		u->set_rignts();
	}
	else
	u=new user(name);  // new user without adm rights
    
	folder* root=new folder(u, "root"); // root directory
	folder* item=root;
	p.push_back(u);


	cin>>cmd;


	while(cmd != "end")
	{
		if(cmd == "CRD")    // to create the folder
		{
			cout<<"enter the name of the directory:   ";
			cin>>name;
			try
			{
              item->create_folder(name);
			}
			catch(int k)
			{
				cout<<"error code: "<<k<<"  uncorrect name"<<endl;
			}
		}
		else
		if(cmd == "CRF") // to create the file
		{
		  cout<<"enter the name of the file:   "; 
		  cin>>name;
		  try
		  {
            item->create_file(name); 
		  }
		  catch(int k)
		  {
            cout<<"error code: "<<k<<"  uncorrect name"<<endl;
		  }		  
		}
		else
		if(cmd == "CRS")  // to create the siml
		{
			cout<<"enter the name of the siml:  ";
			cin>>name;
			cout<<"enter the name of the file:  ";
			cin>>nf;
			try
			{
			  item->create_siml(name, nf);
			}
			catch(int k)
			{
              cout<<"error code:  "<<k<<"  uncorrect name"<<endl;
			}
		}
		else
		if(cmd == "GB") // to go back
		{
			try
			{
				item=item->previous();
			}
			catch(int k)
			{
				cout<<"error code:  "<<k<<"  this folder is the root  "<<endl;
			}
		}
		else
	    if(cmd == "GI") // to move into one of internal folders
		{
			cout<<"enter the name of the folder: ";
			cin>>name;
			try
			{
				item=item->change_folder(name);
			}
		    catch(int k)
			{
				cout<<"error code:  "<<k<<"  there are not folder with this name in this folder"<<endl;
			}
		}
		else
		if(cmd == "DEF") // to delete the file
		{
			cout<<"enter the name of the file:  ";
			cin>>name;
			try
			{
				item->delete_file(name);
			}
			catch(int k)
			{
			   cout<<"error code: "<<k<<"  uncorrect name"<<endl;
			}
		}
		else
		if(cmd == "DED")  // to delete the folder
		{
			cout<<"enter the name of the folder:  ";
			cin>>name;
			try
			{
				item->delete_folder(name);
			}
			catch(int k)
			{
				cout<<"error code:  "<<k<<"  there are not folder with this name in this folder"<<endl;
			}
		}
		else
		if(cmd == "DES") // to delete the siml
		{
			cout<<"enter the name of the siml:  ";
			cin>>name;
			try
			{
				item->delete_siml(name);
			}
			catch(int k)
			{
				cout<<"error code:  "<<k<<"  there are not siml with this name in this folder"<<endl;
			}
		}
		else
		if(cmd == "RF") // to read the file
		{
			cout<<"enter the name of the file:  ";
			cin>>name;
			try
			{
				item->read_file(name);
			}
			catch(int k)
			{
                cout<<"error code:  "<<k<<"   there are not the file with this name in this folder"<<endl;
			}
		}
		else
		if(cmd == "WF") // to write in the file
		{
			cout<<"enter the name of the file:  ";
			cin>>name;
			try
			{
				item->write_file(name);
			}
			catch(int k)
			{
				cout<<"error code: "<<k<<"  there are not the file with this name in this folder"<<endl;
			}
		}
		else
		if(cmd == "OS")  // to open the siml
		{
			cout<<"enter the name of the siml:  ";
			cin>>name;
			try
			{
				item->open_siml(name);
			}
			catch(int k)
			{
				cout<<"error code:  "<<k<<"  there are not the siml with this name in this folder"<<endl;
			}
		}
		else
		if(cmd == "CRU")  // to create the user
		{
			cout<<"enter the name of new user:  ";
			cin>>name;
			try
			{
				for(unsigned int i=0; i<p.size(); i++)
				  if(p[i]->name == name)
				    throw 10;
				user* ptr=new user(name);
				cout<<"enter his rights(admin(T) or not)     ";
	            cin>>a;
	            if(a == 'T')
				  ptr->set_rignts();
				p.push_back(ptr);
			}
			catch(int k)
			{
				cout<<"error code:  "<<k<<"  there are user with this name"<<endl;
			}
		}
		else
		if(cmd == "CHU")  // to change the user
		{
			cout<<"enter the name of the user:  ";
			cin>>name;
			try
			{
			  unsigned int k=0;
		      for(unsigned int i=0; i<p.size(); i++)
				  if(p[i]->name == name)
				  {
			        item->change_user(p[i], root);
					k++;
				  }
			  if(k == 0)
				throw 9;
			}
			catch(int k)
			{
				cout<<"error code:  "<<k<<"  there are not users with this name"<<endl;
			}
		}
		else
		if(cmd == "PRA") // to print all system
		{
			item->print_all(root);
		}
		else
		if(cmd == "FF") // to find the file(all system)
		{
			cout<<"enter the name of the file:  ";
			cin>>name;
		    try
		    {
			   root->find_file(name);
		    }
			catch(int k)
			{
				cout<<"error code: "<<k<<"there are not files with this name"<<endl;
			}
		}
		else
		if(cmd == "CD") // to cope the folder
		{
	       cout<<"enter the name of the folder:  ";
		   cin>>name;
		   item->copy_folder(name);
		}
		else
		{
			cout<<"enter the correct command"<<endl;
		}
		if(item->parrent != nullptr)
		   cout<<"you are in "<<item->name<<"("<<item->parrent->name<<")"<<" folder"<<endl;
		else
		   cout<<"you are in root folder"<<endl;

		cin>>cmd;
	}
	root->print_all(root);
	system("pause");
	return 0;
}

