#pragma once
 /////////////////////////////////////////////////////////////////////
 //  NoSqlDb.h - key/value pair in-memory database                  //
 //  ver 1.0                                                        //
 //  Language:      Visual C++ 2015, SP1                            //
 //  Platform:      HP EliteBook, Windows 10                        //
 //  Application:   Key/value Database, CSE 687- Sp17			    //
 //  Author:        Manish Gupta, Syracuse University               //
 //                 (315) 412-8140, magupta@syr.edu                 //
 /////////////////////////////////////////////////////////////////////

 /*
 Module Operations:
 ==================
 This package contains Element as well as NoSqlDb classes. Element class creates an object of one 
 element of database. This package can creates key/value pair in-memory database. This template also enables
 user to write database to xml and read it again. It containes several functions to edit and modify database. 
 The persistance to/from xml is based on parsing from xmldocuments. The data associated with key can be
 of typename specified by user. 


 Public Interface:
 =================
 Element class:
 show:							//print element on the screen
 NoSqlDb class:
 save:								//add element to database
 deletekey:							//delete element from databse
 editvalues:					    //edit values of an element
 deletechild:					    //delete dependency
 addchild:						    //add dependency
 value:				                //return element of db
 count:								//count the number of elements in  db
 writeElement:						//Write one element to xml
 toxml:						        //write xml file for complete database
 fromXml:					        //read xml file
 autosave:					        //autosave file to xml after "counter" number of writes.
 getcounter:						//gives number of unsaved elements.
 resetcounter:						//reset the unsaved elements.

 Build Process:
 ==============
 Required files
 - CppProperties.h; XmlDocument.h; XmlElement.h; Convert.h; StrHelper.h
 *  Build Command:
 *  --------------
 * devenv Project1.sln /rebuild debug

 Maintenance History:
 ====================
 ver 1.0

 */


 /////////////////////////////////////////////////////////////////////
//Include dependency and c++ libraries
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include "../CppProperties/CppProperties.h"
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../serialize/Convert.h"
#include "../Utilities/StrHelper.h"

/////////////////////////////////////////////////////////////////////
//using namespaces
using namespace XmlProcessing;
using SPtr = std::shared_ptr<AbstractXmlElement>;

/////////////////////////////////////////////////////////////////////
// Element class represents a data record in our NoSql database
// - in our NoSql database that is just the value in a key/value pair

template<typename Data>
class Element
{
public:
  using Name = std::string;
  using Category = std::string;
  using TimeDate = std::string;
  using Description = std::string;

  Property<Name> name;					//Key
  Property<Category> category;			// metadata
  Property<TimeDate> timeDate;			// metadata
  Property<Description> description;    // metadata
  Property<Data> data;					// data
  std::vector<std::string> children;   //children
  std::string show();					//print element on the screen
};

/////////////////////////////////////////////////////////////////////
//Print function for element//
template<typename Data>
std::string Element<Data>::show()
{
  std::ostringstream out;
  out.setf(std::ios::adjustfield, std::ios::left);
  out << "\n    " << std::setw(8) << "name"     << " : " << name;
  out << "\n    " << std::setw(8) << "category" << " : " << category;
  out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
  out << "\n    " << std::setw(8) << "data"     << " : " << data;
  out << "\n    " << std::setw(8) << "descrip" << " : " << description;
  out << "\n    " << std::setw(8) << "Childs" << " : ";
  for (size_t i = 0; i < children.size(); i++)
  {
	  out << children[i];
	  if (i < children.size() - 1)
		  out << "; ";
	  else
		  out << ".";
  }
  out << "\n";
  return out.str();
}

/////////////////////////////////////////////////////////////////////
// NoSqlDb class is a key/value pair in-memory database
// - stores and retrieves xml document
// - Edit/add/delete elements in DB

template<typename Data>
class NoSqlDb
{
public:
  using Key = std::string;
  using Keys = std::vector<Key>;
  Keys keys();
  bool save(Key key, Element<Data> elem); 
  bool deletekey(Key key);					
  bool editvalues(Key key, Element<Data> elem); 
  bool deletechild(Key parentkey, Key childkey);
  bool addchild(Key parentkey, Key childkey); 
  Element<Data> value(Key key);             
  size_t count();							
  std::string toxml(NoSqlDb<Data>&); 
  NoSqlDb<Data> fromXml(const std::string);
  void autosave(); 
  SPtr writeElement(Element<Data>); 
  int getcounter();
  void resetcounter(int reset =0);
private:
	using Item = std::pair<Key, Element<Data>>;
	static int counter;		//counter for autosave
	std::unordered_map<Key, Element<Data>> store;
};

/////////////////////////////////////////////////////////////////////
//Initialize counter///
template<typename Data>
int NoSqlDb<Data>::counter = 0;

////////////////////////////////////////////////////////////////////
template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
	Keys keys;
	for (Item item : store)
	{
		keys.push_back(item.first);
	}
	return keys;
}

/////////////////////////////////////////////////////////////////////
//add element to databse
template<typename Data>
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
{
	if (store.find(key) != store.end())
		return false;
	store[key] = elem;
	counter++;
	if (counter % 4 == 0)
		autosave();
	return true;
}

/////////////////////////////////////////////////////////////////////
//return element values 
template<typename Data>
Element<Data> NoSqlDb<Data>::value(Key key)
{
	if (store.find(key) != store.end())
		return store[key];
	return Element<Data>();
}
/////////////////////////////////////////////////////////////////////
//get the number of added element
template<typename Data>
int NoSqlDb<Data>::getcounter()
{
	return counter;
}
/////////////////////////////////////////////////////////////////////
//reset counter
template<typename Data>
void NoSqlDb<Data>::resetcounter(int reset)
{
	counter = reset;
}
/////////////////////////////////////////////////////////////////////
//number of elements
template<typename Data>
size_t NoSqlDb<Data>::count()
{
	return store.size();
}
/////////////////////////////////////////////////////////////////////
//Add dependency
template<typename Data>
bool NoSqlDb<Data>::addchild(Key parentkey, Key childkey)
{
	bool addchildFlag = true;
	if (store.find(parentkey) != store.end())
	{
		std::vector<std::string> childrenlist = this->value(parentkey).children;
		for (size_t i = 0; i < childrenlist.size(); i++)
		{
			if (childrenlist[i] == childkey)
				addchildFlag = false;
		}
		if (addchildFlag)
		{
			store[parentkey].children.push_back(childkey);
		}
	}
	else
		addchildFlag = false;
	return addchildFlag;
}
/////////////////////////////////////////////////////////////////////
//delete dependency
template<typename Data>
bool NoSqlDb<Data>::deletechild(Key parentkey, Key childkey)
{
	bool deletechildFlag = false;
	std::vector<std::string> childrenlist = this->value(parentkey).children;
	for (size_t i = 0; i< childrenlist.size(); i++)
	{
		if (childrenlist[i] == childkey)
		{
			store[parentkey].children.erase(store[parentkey].children.begin() + i);
			deletechildFlag = true;
		}
	}
	return deletechildFlag;
}

/////////////////////////////////////////////////////////////////////
//delete element by key
template<typename Data>
bool NoSqlDb<Data>::deletekey(Key key)
{
	if (store.find(key) != store.end())
	{
		store.erase(key);
		return true;
	}
	else
		return false;
}

/////////////////////////////////////////////////////////////////////
//edit key values  by key
template<typename Data>
bool NoSqlDb<Data>::editvalues(Key key, Element<Data> elem)
{
	if (store.find(key) != store.end())
	{
		store[key].category = elem.category;
		store[key].description = elem.description;
		store[key].timeDate = elem.timeDate;
		store[key].data = elem.data;
		store[key].children = elem.children;
		return true;
	}
	else
		return false;
}

/////////////////////////////////////////////////////////////////////
//autosave file after 4 writes
template<typename Data>
void NoSqlDb<Data>::autosave()
{
	this->toxml(*this);
}

/////////////////////////////////////////////////////////////////////
//write an element to database
template<typename Data>
SPtr NoSqlDb<Data>::writeElement(Element<Data> elem)
{
	SPtr pRoot = makeTaggedElement("Element");				//make "Element as root
	SPtr pNameElem = makeTaggedElement("name");				// make Property<string> name element and add to root
	pRoot->addChild(pNameElem);								
	SPtr pTextElem = makeTextElement(elem.name);
	pNameElem->addChild(pTextElem);
	SPtr pCategoryElem = makeTaggedElement("category");     // make Property<string> category element and add to root
	pRoot->addChild(pCategoryElem);
	pTextElem = makeTextElement(elem.category);
	pCategoryElem->addChild(pTextElem);
	SPtr pTimedateElem = makeTaggedElement("timeDate");		// make Property<string> timeDate element and add to root
	pRoot->addChild(pTimedateElem);
	pTextElem = makeTextElement(elem.timeDate);
	pTimedateElem->addChild(pTextElem);
	SPtr pdescriptionElem = makeTaggedElement("description");//make property<string> description element and add to root
	pRoot->addChild(pdescriptionElem);
	pTextElem = makeTextElement(elem.description);
	pdescriptionElem->addChild(pTextElem);
	SPtr pdataElem = makeTaggedElement("data");				// make Property<data> data element and add to root
	pRoot->addChild(pdataElem);
	std::string dataString = Convert<Data>::toString(elem.data);	//convert <Data> to string
	pTextElem = makeTextElement(dataString);
	pdataElem->addChild(pTextElem);
	SPtr pchildrenElem = makeTaggedElement("children");		// make children element and add to root
	std::vector<std::string> pchildData = elem.children;
	for (size_t i = 0; i < pchildData.size(); i++)
	{
		SPtr pchild = makeTaggedElement("child");
		pTextElem = makeTextElement(pchildData[i]);
		pchild->addChild(pTextElem);
		pchildrenElem->addChild(pchild);
	}
	pRoot->addChild(pchildrenElem);						
	return pRoot;									//return root of element
}

/////////////////////////////////////////////////////////////////////
//Write to xml file
template<typename Data>
std::string NoSqlDb<Data>::toxml(NoSqlDb<Data>& db)
{
	std::string xml;
	using Keys = NoSqlDb<Data>::Keys;
	Keys keys = db.keys();
	SPtr pDocRoot = makeTaggedElement("db");   //make root name db.
	XmlDocument doc(XmlProcessing::makeDocElement(pDocRoot));
	for (auto it = keys.begin(); it != keys.end(); it++)
	{
		//element of db with key *it
		Element<Data> elem = db.value(*it);
		SPtr pRoot = writeElement(elem);     //write element
		pDocRoot->addChild(pRoot);			//add element to databse
		xml = doc.toString();
	}
	std::ofstream myfile;
	myfile.open("../XML_files/xmlsave.xml");     //save to file
	myfile << xml;
	myfile.close();
	return xml;
}

/////////////////////////////////////////////////////////////////////
//read database from xml
template<typename Data>
 typename NoSqlDb<Data> NoSqlDb<Data>::fromXml(const std::string xml)
 {
	 NoSqlDb<Data> db;
	 try
	 {
		 XmlDocument doc(xml, XmlDocument::file);
		 std::vector<SPtr> desc = doc.descendents("Element").select(); //find descendents "Elements"
		 for (size_t i = 0; i < desc.size(); i++)
		 {
			 XmlDocument elementDoc(makeDocElement(desc[i]));
			 std::vector<SPtr> desc_element = elementDoc.descendents("name").select();  // fetch the name string from XML element
			 std::string name_value = desc_element[0]->children()[0]->value();
			 name_value = trim(name_value);
			 desc_element = elementDoc.descendents("category").select();				// fetch the category string from XML element 
			 std::string category_value = desc_element[0]->children()[0]->value();
			 category_value = trim(category_value);
			 desc_element = elementDoc.descendents("timeDate").select();				// fetch the timeDate string from XML element
			 std::string timeDate_value = desc_element[0]->children()[0]->value();
			 timeDate_value = trim(timeDate_value);
			 desc_element = elementDoc.descendents("description").select();				// fetch the timeDate string from XML element
			 std::string description_value = desc_element[0]->children()[0]->value();
			 description_value = trim(description_value);
			 desc_element = elementDoc.descendents("data").select();					 // fetch the data string from XML Element and convert to data
			 std::string data_String = desc_element[0]->children()[0]->value();
			 data_String = trim(data_String);
			 Data data_value = Convert<Data>::fromString(data_String);				//convert to Data type
			 std::vector<SPtr> desc_childelement = elementDoc.descendents("child").select(); //fetch children from string from XML
			 std::vector<std::string> children_string;
			 for (size_t j = 0; j < desc_childelement.size(); j++)
				 children_string.push_back(trim(desc_childelement[j]->children()[0]->value()));
			//Write to Element
			 Element<Data> elem_fromxml;
			 elem_fromxml.name = name_value;
			 elem_fromxml.category = category_value;
			 elem_fromxml.timeDate = timeDate_value;
			 elem_fromxml.data = data_String;
			 elem_fromxml.children = children_string;
			 elem_fromxml.description = description_value;
			 db.save(name_value, elem_fromxml);
		 }
	 }
	 catch (std::exception& ex)
	 {
		 std::cout << "\n  something bad happend";
		 std::cout << "\n  " << ex.what();
	 }
	 return db;
 }
 /////////////////////////////////////////////////////////////////////