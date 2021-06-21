#pragma once
/////////////////////////////////////////////////////////////////////
//  Queries.h -This has Query class, which can take several        //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Platform:      HP EliteBook, Windows 10                        //
//  Application:   Queries on Database, CSE 687-Sp17			   //
//  Author:        Manish Gupta, Syracuse University               //
//                 (315) 412-8140, magupta@syr.edu                 //
/////////////////////////////////////////////////////////////////////

/*
Module Operations:
==================
This package has query class to help the client making any query on the NoSqlDb. It can receive
database and perform queries like finding element of key, finding keys with some specific patterns
in keys and values. It also support multiple and compound queries.


Public Interface:
=================

Queries_value:						//return value of keys
Queries_child:						//return childrens of specified keys
Queries_keyPattern:					//return set of keys by keypattern on database as well as from earlier query
Queries_categoryPattern:            //return set of keys by category pattern on database as well as from earlier query
Queries_dataPattern:                //return set of keys by data pattern on database as well as from earlier query
checkUnion:							//check if the key is already present in union set.
GetUnion:                           //return set of keys by union of queries

Build Process:
==============
Required files
- CppProperties.h; XmlDocument.h; XmlElement.h; Convert.h; StrHelper.h; NoSqlDb.h.
*  Build Command:
*  --------------
* devenv Project1.sln /rebuild debug

Maintenance History:
====================
ver 1.0

*/

//include dependency and standard libraries
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include "../CppProperties/CppProperties.h"
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../serialize/Convert.h"
#include "../Utilities/StrHelper.h"
#include "../NoSqlDb/NoSqlDb.h"

//using namespaces
using namespace XmlProcessing;
using SPtr = std::shared_ptr<AbstractXmlElement>;

/////////////////////////////////////////////////////////////////////
// Template Query class for enquiries on database helper////////////
template<typename Data>
class Queries
{
public:
	Queries(NoSqlDb<Data>& dataB) : db(dataB) {}
	using Keys = std::vector<std::string>;
	using Key = std::string;
	Element<Data> Queries_value(Key);   //return value of keys
	Keys Queries_child(Key, bool isUnionRequest = false); // return childrens of specified keys
	Keys Queries_keyPattern(Key keyP = "*", bool isUnionRequest = false); //keypattern
	Keys Queries_keyPattern(Keys, Key keyP = "*", bool isUnionRequest = false); //key pattern from earlier query
	Keys Queries_categoryPattern(Key catP, bool isUnionRequest = false); //category pattern
	Keys Queries_categoryPattern(Keys, Key catP, bool isUnionRequest = false); //category pattern from earlier  query
	Keys Queries_dataPattern(Key datatP, bool isUnionRequest = false); //data pattern
	Keys Queries_dataPattern(Keys,Key datatP, bool isUnionRequest = false); //data pattern for earlier query
	bool checkUnion(Key); 
	Keys GetUnion();//union of queries
private:
	NoSqlDb<Data>& db;
	std::vector<std::string> unionlist; //query union list
	//int dbase_data;
};
/////////////////////////////////////////////////////////////////////
//check if the key is present in union list
template<typename Data>
bool Queries<Data>::checkUnion(Key key)
{
	for (size_t i = 0; i < unionlist.size(); i++)
	{
		if (unionlist[i] == key)
			return false;
	}
	return true;
}
/////////////////////////////////////////////////////////////////////
//return list of keys for union of enquiries
template<typename Data>
typename Queries<Data>::Keys Queries<Data>::GetUnion()
{
	Keys temp = unionlist;
	unionlist.clear();
	return temp;
}
/////////////////////////////////////////////////////////////////////
//return values of element
template<typename Data>
Element<Data> Queries<Data>::Queries_value(Key key)
{
	return db.value(key);
}
/////////////////////////////////////////////////////////////////////
//return childs of key
template<typename Data>
typename Queries<Data>::Keys Queries<Data>::Queries_child(Key key,  bool isUnionRequest)
{
	Element<Data> temp = db.value(key);
	for (auto it = temp.children.begin(); it != temp.children.end(); it++)
	{
		if (checkUnion(*it) && isUnionRequest)
			unionlist.push_back(*it);
	}
	return temp.children;
}
/////////////////////////////////////////////////////////////////////
//return set of keys with key pattern
template<typename Data>
typename Queries<Data>::Keys Queries<Data>::Queries_keyPattern(Key keyP, bool isUnionRequest)
{
	Keys keys = db.keys();
	Keys QueryResult;
	if (keyP == "*")
		return keys;
	else
	{
		for (auto it = keys.begin(); it != keys.end(); it++)
		{
			std::size_t found = it->find(keyP);
			if (found != std::string::npos)
			{
				QueryResult.push_back(*it);
				if (checkUnion(*it) && isUnionRequest)
					unionlist.push_back(*it);
			}
		}
		return QueryResult;	
	}
}
/////////////////////////////////////////////////////////////////////
//return set of keys from earlier queries
template<typename Data>
typename Queries<Data>::Keys Queries<Data>::Queries_keyPattern(Keys earlierQuery, Key keyP, bool isUnionRequest)
{
	Keys QueryResult;
	if (keyP == "*")
		return earlierQuery;
	else
	{
		for (auto it = earlierQuery.begin(); it != earlierQuery.end(); it++)
		{
			std::size_t found = it->find(keyP);
			if (found != std::string::npos)
			{
				QueryResult.push_back(*it);
				if (checkUnion(*it) && isUnionRequest)
					unionlist.push_back(*it);
			}
		}
		return QueryResult;
	}
}
/////////////////////////////////////////////////////////////////////
//return set of keys from pattern in category
template<typename Data>
typename Queries<Data>::Keys Queries<Data>::Queries_categoryPattern(Key catP,  bool isUnionRequest)
{
	Keys keys = db.keys();
	Keys QueryResult;
	for (auto it = keys.begin(); it != keys.end(); it++)
		{
		std::string tempCategory = db.value(*it).category;
		std::size_t found = tempCategory.find(catP);
			if (found != std::string::npos)
			{
				QueryResult.push_back(*it);
				if (checkUnion(*it) && isUnionRequest)
					unionlist.push_back(*it);
			}
		}
	return QueryResult;
}
/////////////////////////////////////////////////////////////////////
//return set of keys from pattern in category in earlier query
template<typename Data>
typename Queries<Data>::Keys Queries<Data>::Queries_categoryPattern(Keys earlierQuery, Key catP, bool isUnionRequest)
{
	Keys QueryResult;
	for (auto it = earlierQuery.begin(); it != earlierQuery.end(); it++)
	{
		std::string tempCategory = db.value(*it).category;
		std::size_t found = tempCategory.find(catP);
		if (found != std::string::npos)
		{
			QueryResult.push_back(*it);
			if (checkUnion(*it) && isUnionRequest)
				unionlist.push_back(*it);
		}
	}
	return QueryResult;
}
/////////////////////////////////////////////////////////////////////
//return set of keys from pattern in data (if data is string)
template<typename Data>
typename Queries<Data>::Keys Queries<Data>::Queries_dataPattern(Key dataP, bool isUnionRequest)
{
	Keys keys = db.keys();
	Keys QueryResult;
	if(!std::is_same<Data, std::string>::value)
		QueryResult.push_back("This Query only check for string template.");
	else
	{
		for (auto it = keys.begin(); it != keys.end(); it++)
		{
			std::string tempData = db.value(*it).data;
			std::size_t found = tempData.find(dataP);
			if (found != std::string::npos)
			{
				QueryResult.push_back(*it);
				if (checkUnion(*it) && isUnionRequest)
					unionlist.push_back(*it);
			}
		}
	}
	return QueryResult;
}
/////////////////////////////////////////////////////////////////////
//return set of keys from pattern in category in earlier query
template<typename Data>
typename Queries<Data>::Keys Queries<Data>::Queries_dataPattern(Keys earlierQuery, Key dataP, bool isUnionRequest)
{
	Keys QueryResult;
	if (!std::is_same<Data, std::string>::value)
		QueryResult.push_back("This Query only check for string template.");
	else
	{
		for (auto it = earlierQuery.begin(); it != earlierQuery.end(); it++)
		{
			std::string tempData = db.value(*it).data;
			std::size_t found = tempData.find(dataP);
			if (found != std::string::npos)
			{
				QueryResult.push_back(*it);
				if (checkUnion(*it) && isUnionRequest)
					unionlist.push_back(*it);
			}
		}
	}
	return QueryResult;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

