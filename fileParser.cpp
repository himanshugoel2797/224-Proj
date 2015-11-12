#include <iostream>
#include <fstream>
#include <string>
#include "fileParser.h"

using namespace std;

DataManager::AppData DataManager::root, *DataManager::last;
const string dataFile = "ese224_users.dat";

bool DataManager::Load()
{
	ifstream inData(dataFile);

	if(!inData.is_open())
		return false;

	//Parse the file and fill the data structures
	AppData *ptr = &root, *prev = NULL;

	while(!inData.eof())
	{
		inData >> ptr->username;
		inData >> ptr->password;
		inData >> ptr->balance;

		ptr->next = new AppData();
		
		prev = ptr;
		ptr = ptr->next;
		ptr->prev = prev;
	}

	delete ptr;
	prev->next = NULL;

	last = prev;

	inData.close();
	return true;
}

bool DataManager::Save()
{
	ofstream outData(dataFile);

	if(!outData.is_open())
		return false;

	//Save the data structures to 
	AppData *ptr = &root;
	while(ptr != NULL)
	{
		outData << ptr->username;
		outData << ptr->password;
		outData << ptr->balance;

		ptr = ptr->next;
	}

	outData.close();
	return true;
}

bool DataManager::UserExists(string username)
{
	AppData *ptr = &root;
	do{
		if(ptr->username == username)return true;
		ptr = ptr->next;
	}while(ptr->next != NULL);
	return false;
}

double DataManager::GetUserBalance(string username, string password)
{
	AppData *ptr = &root;
	do{
		if(ptr->username == username && ptr->password == password)return ptr->balance;
		ptr = ptr->next;
	}while(ptr->next != NULL);
	return 0;	
}

bool DataManager::SetUserBalance(string username, string password, double balance)
{
	AppData *ptr = &root;
	do{
		if(ptr->username == username && ptr->password == password)
		{
			ptr->balance = balance;
			return true;
		}
		ptr = ptr->next;
	}while(ptr->next != NULL);
	return false;
}

string DataManager::RetrieveUserPassword(string username)
{
	AppData *ptr = &root;
	do{
		if(ptr->username == username)return ptr->password;
		ptr = ptr->next;
	}while(ptr->next != NULL);
	return 0;		
}

void DataManager::CreateUser(string username, string password)
{
	AppData *data = new AppData;
	data->username = username;
	data->password = password;
	data->balance = 0;
	last->next = data;
	data->prev = last;
	last = data;
}

void DataManager::RemoveUser(string username)
{
	AppData *ptr = &root;
	do{
		if(ptr->username == username)
		{
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
			delete ptr;
		}
		ptr = ptr->next;
	}while(ptr->next != NULL);
}