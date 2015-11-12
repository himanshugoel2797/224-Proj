#ifndef _FILE_PARSER_H_
#define _FILE_PARSER_H_

#include <iostream>
#include <string>
#include <list>

class DataManager
{
public:
	static bool Load();
	static bool Save();
	static void CreateUser(std::string username, std::string password);
	static void RemoveUser(std::string username);
	static std::string RetrieveUserPassword(std::string username);
	static bool UserExists(std::string username);
	static double GetUserBalance(std::string username, std::string password);
	static bool SetUserBalance(std::string username, std::string password, double balance);

private:
	typedef struct AppData
	{
		std::string username;
		std::string password;
		double balance;
		struct AppData *prev;
		struct AppData *next;
	} AppData;
	static AppData root;
	static AppData *last;
};

#endif