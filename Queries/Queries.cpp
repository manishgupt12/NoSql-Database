/////////////////////////////////////////////////////////////////////
//  Queries.cpp -This has Query class, which can take several      //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Platform:      HP EliteBook, Windows 10                        //
//  Application:   Queries on Database, Sp17				       //
//  Author:        Manish Gupta, Syracuse University               //
//                 (315) 412-8140, magupta@syr.edu                 //
/////////////////////////////////////////////////////////////////////


#include "Queries.h"

/////////////////////////////////////////////////////////////////////
//print set of keys
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
//print database
template<typename Data>
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
//test simple queries on databse
template<typename Data>
void simpleQuery(Queries<Data> Query)
{
	using StrData = std::string;
	using intData = int;
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;
	std::cout << "\n Value of a Specified Key. (NoSqlDb) \n";
	Element<StrData> ElemQ1 = Query.Queries_value("NoSqlDb");
	std::cout << ElemQ1.show();
	std::cout << "\n childrens of Specified Key. (Queries) \n";
	Keys QueryChild = Query.Queries_child("Queries");
	print(QueryChild);
	std::cout << "\n Set of all key with key/Item name pattern. (RandomElem) \n";
	Keys keyPattern = Query.Queries_keyPattern("RandomElem");
	print(keyPattern);
	std::cout << "\n Set of all key with category pattern. (Pack) \n";
	Keys categoryPattern = Query.Queries_categoryPattern("Pack");
	print(categoryPattern);
	std::cout << "\n Set of all key with Data check if string type. (help) \n";
	Keys dataPattern = Query.Queries_dataPattern("help");
	print(dataPattern);
}
/////////////////////////////////////////////////////////////////////
//Queries on set of keys received from previous queries
template<typename Data>
void multipleQuery(Queries<Data> Query)
{
	using StrData = std::string;
	using intData = int;
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;
	std::cout << "\n Queries on the set of keys returned earlier. \n";
	std::cout << "\n Any key set can be used with other queries. \n";

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
}
/////////////////////////////////////////////////////////////////////
//Union of queries on database
template<typename Data>
void unionQuery(Queries<Data> Query)
{
	using StrData = std::string;
	using intData = int;
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n Requirement 9 \n";
	std::cout << "\n Union of Queries \n";
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
}

#ifdef QUERIES
/////////////////////////////////////////////////////////////////////
//test queries executive
int main()
{
	using StrData = std::string;
	using intData = int;
	using Key = NoSqlDb<StrData>::Key;
	using Keys = NoSqlDb<StrData>::Keys;
	NoSqlDb<StrData> db = db.fromXml("../XML_files/InputXml.xml");
	print(db);
	std::cout << "\n -------------------------------------------------------\n";
	std::cout << "\n Testing Queries";
	Queries<StrData> Query(db);
	simpleQuery(Query);
	multipleQuery(Query);
	unionQuery(Query);
	system("pause");
}
#endif // QUERIES