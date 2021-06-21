/////////////////////////////////////////////////////////////////////
//  NoSqlDb.cpp - key/value pair in-memory database                //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Platform:      HP EliteBook, Windows 10                        //
//  Application:   Key/value on Database, CSE 687- Sp17			   //
//  Author:        Manish Gupta, Syracuse University               //
//                 (315) 412-8140, magupta@syr.edu                 //
/////////////////////////////////////////////////////////////////////

#include "NoSqlDb.h"

/////////////////////////////////////////////////////////////////////
//Test executive for NoSqlDb.h 

#ifdef NoSql
int main()
{
  std::cout << "\n  Demonstrating NoSql Helper Code";
  std::cout << "\n =================================\n";
  std::cout << "\n  Creating and saving NoSqlDb elements with string data";
  using StrData = std::string;
  using intData = int;
  using Key = NoSqlDb<StrData>::Key;
  using Keys = NoSqlDb<StrData>::Keys;
  NoSqlDb<StrData> db;
  Element<std::string> elem1; //write an  element
  elem1.name = "Football";
  elem1.category = "Sport";
  time_t now = time(0);
  char str[26];
  ctime_s(str, sizeof str, &now);
  *std::remove(str, str + 26, '\n') = '\0';
  elem1.timeDate = str;
  elem1.description = "American football";
  elem1.data = "Team names";
  db.save(elem1.name, elem1);
  Keys keys = db.keys();
  for (Key key : keys)  //priting db
  {
    std::cout << "\n  " << key << ":";
    std::cout << db.value(key).show();
  }
  std::cout << "\n  Saving database to xml file";  //writing to xml file
  std::string xml = db.toxml(db);
  std::cout << "\n ------------------------------------------\n";
  std::cout << "\n  Reading xml file";            //reading from xml
  NoSqlDb<StrData> newDb = newDb.fromXml("../XML_files/xmlsave.xml");
  std::cout << "\n ------------------------------------------\n";
  keys = newDb.keys();
  for (Key key : keys)        //priting new db 
  {
	  std::cout << "\n  " << key << ":";
	  std::cout << newDb.value(key).show();
  }
}
#endif // NoSql