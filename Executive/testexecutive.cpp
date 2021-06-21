#pragma once
/////////////////////////////////////////////////////////////////////
//  testexecutive.cpp - Test exective for NoSql and Query packages //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Platform:      HP EliteBook, Windows 10                        //
//  Application:   Project-1, CSE 687- Sp17			               //
//  Author:        Manish Gupta, Syracuse University               //
//                 (315) 412-8140, magupta@syr.edu                 //
/////////////////////////////////////////////////////////////////////

/*
Module Operations:
==================
This package exhibits the abilities of NoSqlDb, Queries and other packages in details.
It checks for template information and carry out test enquiries on different cases
for user. This is just a sample executive for various functions in this package.


Public Interface:
=================
AddStringElements:					//Add string typename elements to databse
AddintElements:						//add int typename elements to database
print:								//overloaded function print set of keys and database
MakeTestElement:					//Creats a test element
randomElementAdd:					//can add several test elements to database
requirement1:						//using c++ liberary and visual studio 2015
requirement2:						//Implement template class providing key/value pair
requirement3:						//Addition and deletion of key/value pair
requirement4:						//editing dependencies and values
requirement5:						//Persist to xml and read from xml
requirement6:						//Auto save after fix number of element write
requirement7:						//Simple queries on database
requirement8:						//multiple queries on database
requirement9:						//compound queries on database
requirement10:						//Xml input at ../XML_files/InputXml.xml
requirement11:						//Demostrate all requirements confirmation

Build Process:
==============
Required files
- NoSqlDb.h; Queries.h, ../XML_files/InputXml.xml
*  Build Command:
*  --------------
* devenv Project1.sln /rebuild debug

Maintenance History:
====================
ver 1.0
*/

#include "../NoSqlDb/NoSqlDb.h"
#include "../Queries/Queries.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

/////////////////////////////////////////////////////////////////////
//Add string typename elements to databse
void AddStringElements(NoSqlDb<std::string> *db)
{
	std::cout << "\n Adding an element to NoSqlDb<std::string> \n";
	Element<std::string> elem1;
	elem1.name = "Football";
	elem1.category = "Sport";
	time_t now = time(0);
	char str[26];
	ctime_s(str, sizeof str, &now);
	*std::remove(str, str + 26, '\n') = '\0';
	elem1.timeDate = str;
	elem1.description = "American football";
	elem1.data = "Team names";
	db->save(elem1.name, elem1);
	std::cout << " Adding an element to NoSqlDb<std::string> \n";
	Element<std::string> elem2;
	elem2.name = "Violin";
	elem2.category = "Musical Instrument";
	now = time(0);
	str[26];
	ctime_s(str, sizeof str, &now);
	*std::remove(str, str + 26, '\n') = '\0';
	elem2.timeDate = str;
	elem2.description = "Wooden and String instrument";
	elem2.data = "few Luthiers made millions by them. ";
	db->save(elem2.name, elem2);
}

/////////////////////////////////////////////////////////////////////
//add int typename elements to database
void AddintElements(NoSqlDb<int> *idb)
{
	std::cout << "\n Adding an element to NoSqlDb<int>\n";
	Element<int> ielem1;
	ielem1.name = "Cricket";
	ielem1.category = "Sports";
	time_t now = time(0);
	char str[26];
	ctime_s(str, sizeof str, &now);
	*std::remove(str, str + 26, '\n') = '\0';
	ielem1.timeDate = str;
	ielem1.description = "Kind of Baseball with data number of players";
	ielem1.data = 11;
	idb->save(ielem1.name, ielem1);
	std::cout << " Adding an element to NoSqlDb<int> \n";
	Element<int> ielem2;
	ielem2.name = "Holi";
	ielem2.category = "Festival";
	now = time(0);
	ctime_s(str, sizeof str, &now);
	*std::remove(str, str + 26, '\n') = '\0';
	ielem2.timeDate = str;
	ielem2.description = "Festival of color. ";
	ielem2.data = 12032017;
	idb->save(ielem2.name, ielem2);
}

/////////////////////////////////////////////////////////////////////
//overloaded function print database
template <typename Data>
void print(NoSqlDb<Data> db)
{
	using Keys = std::vector<std::string>;
	using Key = std::string;
	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys = db.keys();
	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	std::cout << "\n\n"; 
}
/////////////////////////////////////////////////////////////////////
//Print set of keys
void print(std::vector<std::string> keys)
{
	for (size_t k = 0; k < keys.size(); k++)
	{
		std::cout << keys[k];
		if (k < keys.size() - 1)
			std::cout << ", ";
		else
			std::cout << ".";
	}
	std::cout << "\n\n";
}

/////////////////////////////////////////////////////////////////////
//Creats a test element
Element<std::string> MakeTestElement()
{
	Element<std::string> testelem;
	testelem.name = "Test Element";
	testelem.category = "Project 1";
	time_t now = time(0);
	char str[26];
	ctime_s(str, sizeof str, &now);
	*std::remove(str, str + 26, '\n') = '\0';
	testelem.timeDate = str;
	testelem.description = "Testing element for adding element";
	testelem.data = "This is a string data base";
	return testelem;
}

/////////////////////////////////////////////////////////////////////
//can add several test elements to database
void randomElementAdd(NoSqlDb<std::string> *db, int n)
{
	for (int i = 0; i < n; i++)
	{		
		std::string strSN = std::to_string(i);
		Element<std::string> RandomElement;
		RandomElement.name = "RandomElem"+strSN;
		RandomElement.category = "RandomCategory" + strSN;
		time_t now = time(0);
		char str[26];
		ctime_s(str, sizeof str, &now);
		*std::remove(str, str + 26, '\n') = '\0';
		RandomElement.timeDate = str;
		RandomElement.description = "RandomDescription" + strSN;
		RandomElement.data = "RandomData" + strSN;
		db->save(RandomElement.name, RandomElement);
	}
}

/////////////////////////////////////////////////////////////////////
//using c++ liberary and visual studio 2015
void requirement1()
{
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n Requirement 1 is implemented in C++ using the facilities\n of the standard C++ Libraries and Visual Studio 2015, as provided in the ECS clusters.\n";
	std::cout << "\n -------------------------------------------------------\n";
}
/////////////////////////////////////////////////////////////////////
//Implement template class providing key/value pair
void requirement2()
{
	std::cout << "\n Requirement 2 is implemented for NoSqlDb <std::string> \n and noSql<int> \n";
	std::cout << "\n New databases of type string and type data are created to\n check template functionalities. \n";
	using StrData = std::string;
	using intData = int;
	NoSqlDb<StrData> *strdb = new NoSqlDb<StrData>(); //creating an instance of string data class
	AddStringElements(strdb);
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;
	std::cout << " Printing NoSqlDb <std::string> \n";
	print(*strdb);
	NoSqlDb<intData> *idb = new NoSqlDb<intData>(); //creating an instance of int data class
	AddintElements(idb);
	std::cout << "\n Printing NoSqlDb <int> \n";
	print(*idb);
	std::cout << "\n -------------------------------------------------------\n";
}

/////////////////////////////////////////////////////////////////////
//Addition and deletion of key/value pair
template<typename Data>
void requirement3(NoSqlDb<Data> *db)
{
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n Requirement 3: Addition and deletion of key/value pair\n";
	using StrData = std::string;
	using intData = int;
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;
	std::cout << "\n Current Data Base is: \n";
	print(*db);
	std::cout << "\n Addition of Test Element\n";
	Element<StrData> TestElement = MakeTestElement();
	db->save(TestElement.name, TestElement);
	print(*db);
	std::cout << "\n Deleting of Test Element\n";
	db->deletekey(TestElement.name);
	print(*db);
	std::cout << "\n -------------------------------------------------------\n";
}
///////////////////////////////////////////////////////////////////////////////////
//editing dependencies and values
template<typename Data>
void requirement4(NoSqlDb<Data>* db)
{
	std::cout << "\n -------------------------------------------------------\n";
	using StrData = std::string;
	using intData = int;
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;
	std::cout << "\n Requirement 4: editing dependencies and values \n";
	std::cout << "\n deleting relation between NoSqlDb and CppProperties\n";
	db->deletechild("NoSqlDb", "CppProperties");
	print(*db);
	std::cout << "\n Adding relation between Queries and CppProperties\n";
	db->addchild("Queries", "CppProperties");
	print(*db);
	std::cout << "\n Editing the values of Convert by values of CppProperties, W/O changing key\n";
	db->editvalues("Convert", db->value("CppProperties"));
	print(*db);
	std::cout << "\n -------------------------------------------------------\n";
}

///////////////////////////////////////////////////////////////////////////////////
//Persist to xml and read from xml
template<typename Data>
void requirement5(NoSqlDb<Data>* db)
{
	using StrData = std::string;
	using intData = int;
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n Requirement 5: Persist to xml and read from xml \n";
	std::cout << "\n Saving database to xml file in ../XML_files/xmlsave.xml .\n";
	std::cout << "\n please check the output in ../XML_files/xmlsave.xml .\n";
	std::string xml = db->toxml(*db);
	std::cout << "\n The output xml is:\n" << xml;
	std::cout << "\n Reading database newDb from xml file in ../XML_files/xmlsave.xml .\n";
	NoSqlDb<StrData> newDb = newDb.fromXml("../XML_files/xmlsave.xml");
	print(newDb);
	std::cout << "\n New Database from file is modified db from earlier operations.\n";
	std::cout << "\n -------------------------------------------------------\n";
}

///////////////////////////////////////////////////////////////////////////////////
//Auto save after fix number of element write
template<typename Data>
void requirement6(NoSqlDb<Data>* db)
{
	using StrData = std::string;
	using intData = int;
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n Requirement 6: Auto save after fix number of element write \n";
	std::cout << "\n Autosave after writing 4 elements on data base. ";
	db->resetcounter();
	std::cout << "\n Number of elements before adding extra elements: " << db->count();
	randomElementAdd(db, 4);
	std::cout << "\n Number of elements after adding 4 elements: " << db->count();
	std::cout << "\n Read Xml file again.";
	NoSqlDb<StrData> newDb = newDb.fromXml("../XML_files/xmlsave.xml");
	std::cout << "\n Number of elements in file " << newDb.count()<<"\n";
	db->resetcounter();
	std::cout << "\n Now add 5 more extra elements. it will save only 4 on xml";
	randomElementAdd(db, 9);
	std::cout << "\n Number of elements in database after adding 5 elements: " << db->count();
	std::cout << "\n Read Xml file once again";
	newDb = newDb.fromXml("../XML_files/xmlsave.xml");
	std::cout << "\n The new Db is :" << "\n";
	print(newDb);
	std::cout << "\n -------------------------------------------------------\n";
}

///////////////////////////////////////////////////////////////////////////////////
//Simple queries on database
template<typename Data>
void requirement7(NoSqlDb<Data>* db)
{
	using StrData = std::string;
	using intData = int;
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n Requirement 7: Simple queries on database \n Queries on DB";
	Queries<StrData> Query(*db);
	std::cout << "\n 7.1 Value of a Specified Key. (NoSqlDb) \n";
	Element<StrData> ElemQ1 = Query.Queries_value("NoSqlDb");
	std::cout << ElemQ1.show();
	std::cout << "\n 7.2 childrens of Specified Key. (Queries) \n";
	Keys QueryChild = Query.Queries_child("Queries");
	print(QueryChild);
	std::cout << "\n 7.3 and 7.4 Set of all key with key/Item name pattern. (RandomElem) \n";
	Keys keyPattern = Query.Queries_keyPattern("RandomElem");
	print(keyPattern);
	std::cout << "\n 7.5 Set of all key with category pattern. (Pack) \n";
	Keys categoryPattern = Query.Queries_categoryPattern("Pack");
	print(categoryPattern);
	std::cout << "\n 7.6 Set of all key with Data check if string type. (help) \n";
	Keys dataPattern = Query.Queries_dataPattern("help");
	print(dataPattern);
	std::cout << "\n -------------------------------------------------------\n";
}

///////////////////////////////////////////////////////////////////////////////////
//multiple queries on database
template<typename Data>
void requirement8(NoSqlDb<Data> *db)
{
	using StrData = std::string;
	using intData = int;
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n Requirement 8: Queries on the set of keys returned earlier \n";
	std::cout << "\n Any key set can be used with other queries. \n";
	Queries<StrData> Query(*db);
	std::cout << "\n 8.1 Query key (Quer) on set return from category pattern  \n";
	Keys categoryPattern = Query.Queries_categoryPattern("Pack");
	Keys keyrepeatPattern = Query.Queries_keyPattern(categoryPattern, "Quer");
	print(keyrepeatPattern);
	std::cout << "\n 8.2 Query category (1) on set return from keys pattern \n";
	Keys keyPattern = Query.Queries_keyPattern("RandomElem");
	Keys catrepeatPattern = Query.Queries_categoryPattern(keyPattern, "1");
	print(catrepeatPattern); 
	std::cout << "\n 8.3 Data (0) check on set return from key \n";
	Keys datarepeatPattern = Query.Queries_dataPattern(keyPattern, "0");
	print(datarepeatPattern);
	std::cout << "\n -------------------------------------------------------\n";
}

///////////////////////////////////////////////////////////////////////////////////
//compound queries on database
template<typename Data>
void requirement9(NoSqlDb<Data> *db) 
{
	using StrData = std::string;
	using intData = int;
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;
	Queries<StrData> Query(*db);
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n Requirement 9: Union of Queries \n";
	std::cout << "\n Query by data \n";
	bool unionrequest = true;
	Keys dataPattern = Query.Queries_dataPattern("class", unionrequest);
	print(dataPattern);
	std::cout << "\n Query by category \n";
	Keys categoryPattern = Query.Queries_categoryPattern("1", unionrequest);
	print(categoryPattern);
	std::cout << "\n Children of specified keys \n";
	Keys QueryChild = Query.Queries_child("NoSqlDb", unionrequest);
	print(QueryChild);
	std::cout << "\n Union of the above results \n";
	Keys unionkeys = Query.GetUnion();
	print(unionkeys);
	std::cout << "\n -------------------------------------------------------\n";
}

///////////////////////////////////////////////////////////////////////////////////
//Xml input at ../XML_files/InputXml.xml
void requirement10()
{
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n Requirement 10:  \n";
	std::cout << "\n Package structure of the project is included in initial input file. ";
	std::cout << "\n Please note that the database been modified in the earlier requirements ";
	std::cout << "\n So the current dependencies and structure maynot be correct. ";
	std::cout << "\n Please see the initial database in requirement 3 for correct dependencies. \n";
	std::cout << "\n -------------------------------------------------------\n";
}

///////////////////////////////////////////////////////////////////////////////////
//Demostrate all requirements confirmation
void requirement11()
{
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n Requirement 11 \n";
	std::cout << "\n All requirements has been displayed on the screen, based on xml provided. \n";
	std::cout << "\n -------------------------------------------------------\n";
}

///////////////////////////////////////////////////////////////////////////////////
#ifdef TESTEXECUTIVE

///////////////////////////////////////////////////////////////////////////////////
//Main executive function begins
int main()
{
	std::cout << "\n  Welcome to Project 1 for CSE 687";
	std::cout << "\n =================================\n";
	std::cout << "\n  Key/Value Database";
	using StrData = std::string;
	using intData = int;
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;

	requirement1();			//using c++ liberary and visual studio 2015
	requirement2();			//Implement template class providing key/value pair
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n For furter requirements the Input.xml file from folder \n XML_files is used.\n";
	std::cout << "\n -------------------------------------------------------\n";
	NoSqlDb<StrData> db = db.fromXml("../XML_files/InputXml.xml");
	requirement3(&db);		//Addition and deletion of key/value pair
	requirement4(&db);		//editing dependencies and values
	requirement5(&db);		//Persist to xml and read from xml
	requirement6(&db);		//Auto save after fix number of element write
	requirement7(&db);		//Simple queries on database
	requirement8(&db);		//multiple queries on database
	requirement9(&db);		//compound queries on database
	requirement10();		//Xml input at ../XML_files/InputXml.xml
	requirement11();		//Demostrate all requirements confirmation
	system("pause");
}
#endif // TESTEXECUTIVE