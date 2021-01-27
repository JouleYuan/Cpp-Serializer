#pragma once
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <typeinfo>
#include <sstream>
#include <filesystem>
#include "tinyxml2.h" 
using namespace std;
using namespace tinyxml2;

namespace xml {
	// arithmetic
	template<typename T> void serialize_process(T& object, XMLDocument& doc, XMLElement* root, const char* labelName, typename enable_if<is_arithmetic<T>::value>::type* = 0) {
		XMLElement* newNode = doc.NewElement(labelName);

		newNode->SetAttribute("val", object);
		root->InsertEndChild(newNode);
	}

	template<typename T> void deserialize_process(T& object, bool isClass, XMLElement*& root, typename enable_if<is_arithmetic<T>::value>::type* = 0) {
		if (!root) {
			cout << "ERROR: Data type mismatch." << endl;
		}

		// get the value
		const char* v = root->Attribute("val");
		bool b = true;
		if (v) {
			string value(v);

			// if the object is char
			if (typeid(object).name() == typeid('c').name()) {
				object = atoi(value.c_str());
			}
			// if the object is bool
			else if (typeid(object).name() == typeid(b).name()) {
				if (value == "true") object = true;
				else object = false;
			}
			else {
				istringstream iss(value);
				iss >> object;
			}

			if (isClass) {
				root = root->NextSiblingElement();
			}
		}
		else {
			cout << "ERROR: Data type mismatch." << endl;
		}
	}

	// string
	void serialize_process(string& object, XMLDocument& doc, XMLElement* root, const char* labelName) {
		XMLElement* newNode = doc.NewElement(labelName);

		newNode->SetAttribute("val", object.c_str());
		root->InsertEndChild(newNode);
	}

	void deserialize_process(string& object, bool isClass, XMLElement*& root) {
		if (!root) {
			cout << "ERROR: Data type mismatch." << endl;
		}

		// get the value
		const char* v = root->Attribute("val");
		if (v) {
			string value(v);
			object = value;

			if (isClass) {
				root = root->NextSiblingElement();
			}
		}
		else {
			cout << "ERROR: Data type mismatch." << endl;
		}
	}

	// pair
	template <typename T1, typename T2> void serialize_process(pair<T1, T2>& object, XMLDocument& doc, XMLElement* root, const char* labelName) {
		XMLElement* newNode = doc.NewElement(labelName);
		root->InsertEndChild(newNode);

		xml::serialize_process(object.first, doc, newNode, "first");
		xml::serialize_process(object.second, doc, newNode, "second");
	}

	template <typename T1, typename T2> void deserialize_process(pair<T1, T2>& object, bool isClass, XMLElement*& root) {
		if (!root) {
			cout << "ERROR: Data type mismatch." << endl;
		}

		XMLElement* first = root->FirstChildElement("first");
		XMLElement* second = root->FirstChildElement("second");

		xml::deserialize_process(object.first, false, first);
		xml::deserialize_process(object.second, false, second);

		if (isClass) {
			root = root->NextSiblingElement();
		}
	}

	// vector
	template <typename T> void serialize_process(vector<T>& object, XMLDocument& doc, XMLElement* root, const char* labelName) {
		int size = object.size();

		XMLElement* newNode = doc.NewElement(labelName);
		newNode->SetAttribute("size", size);
		root->InsertEndChild(newNode);

		for (typename vector<T>::iterator iter = object.begin(); iter != object.end(); iter++) {
			xml::serialize_process(*iter, doc, newNode, "vector_item");
		}
	}

	template <typename T> void deserialize_process(vector<T>& object, bool isClass, XMLElement*& root) {
		if (!root) {
			cout << "ERROR: Data type mismatch." << endl;
		}

		XMLElement* child = root->FirstChildElement();
		T item;
		while (child != NULL) {
			xml::deserialize_process(item, false, child);
			object.push_back(item);
			child = child->NextSiblingElement();
		}

		if (isClass) {
			root = root->NextSiblingElement();
		}
	}

	// list
	template <typename T> void serialize_process(list<T>& object, XMLDocument& doc, XMLElement* root, const char* labelName) {
		int size = object.size();

		XMLElement* newNode = doc.NewElement(labelName);
		newNode->SetAttribute("size", size);
		root->InsertEndChild(newNode);

		for (typename list<T>::iterator iter = object.begin(); iter != object.end(); iter++) {
			xml::serialize_process(*iter, doc, newNode, "list_item");
		}
	}

	template <typename T> void deserialize_process(list<T>& object, bool isClass, XMLElement*& root) {
		if (!root) {
			cout << "ERROR: Data type mismatch." << endl;
		}

		XMLElement* child = root->FirstChildElement();
		T item;
		while (child != NULL) {
			xml::deserialize_process(item, false, child);
			object.push_back(item);
			child = child->NextSiblingElement();
		}

		if (isClass) {
			root = root->NextSiblingElement();
		}
	}

	// set
	template <typename T> void serialize_process(set<T>& object, XMLDocument& doc, XMLElement* root, const char* labelName) {
		int size = object.size();

		XMLElement* newNode = doc.NewElement(labelName);
		newNode->SetAttribute("size", size);
		root->InsertEndChild(newNode);

		for (typename set<T>::iterator iter = object.begin(); iter != object.end(); iter++) {
			xml::serialize_process(*iter, doc, newNode, "set_item");
		}
	}

	template <typename T> void deserialize_process(set<T>& object, bool isClass, XMLElement*& root) {
		if (!root) {
			cout << "ERROR: Data type mismatch." << endl;
		}

		XMLElement* child = root->FirstChildElement();
		T item;
		while (child != NULL) {
			xml::deserialize_process(item, false, child);
			object.insert(item);
			child = child->NextSiblingElement();
		}

		if (isClass) {
			root = root->NextSiblingElement();
		}
	}

	// map
	template <typename K, typename V> void serialize_process(map<K, V>& object, XMLDocument& doc, XMLElement* root, const char* labelName) {
		int size = object.size();

		XMLElement* newNode = doc.NewElement(labelName);
		newNode->SetAttribute("size", size);
		root->InsertEndChild(newNode);

		for (typename map<K, V>::iterator iter = object.begin(); iter != object.end(); iter++) {
			XMLElement* pairNode = doc.NewElement("map_item");
			newNode->InsertEndChild(pairNode);

			xml::serialize_process(iter->first, doc, newNode->LastChildElement(), "first");
			xml::serialize_process(iter->second, doc, newNode->LastChildElement(), "second");
		}
	}

	template <typename K, typename V> void deserialize_process(map<K, V>& object, bool isClass, XMLElement*& root) {
		if (!root) {
			cout << "ERROR: Data type mismatch." << endl;
		}

		XMLElement* child = root->FirstChildElement();
		K key;
		V value;

		while (child != NULL) {
			XMLElement* first = child->FirstChildElement("first");
			XMLElement* second = child->FirstChildElement("second");

			xml::deserialize_process(key, false, first);
			xml::deserialize_process(value, false, second);
			object.insert(map<K, V>::value_type(key, value));

			child = child->NextSiblingElement();
		}

		if (isClass) {
			root = root->NextSiblingElement();
		}
	}

	// user-dedoced types
	template<typename T> void serialize_process(T& object, XMLDocument& doc, XMLElement* root, const char* labelName, typename enable_if<is_class<T>::value>::type* = 0) {
		XMLElement* newNode = doc.NewElement(labelName);
		root->InsertEndChild(newNode);

		object.serialize_xml(doc, newNode, "class_member");
	}

	template<typename T> void deserialize_process(T& object, bool isClass, XMLElement* root, typename enable_if<is_class<T>::value>::type* = 0) {
		XMLElement* newNode = root->FirstChildElement();
		object.deserialize_xml(true, newNode);
	}

	template <typename... T> void enable_xml_serialize(XMLDocument& doc, XMLElement* root, const char* labelName, T... object) {
		(xml::serialize_process(object, doc, root, labelName), ...);
	}

	template <typename... T> void enable_xml_deserialize(bool isClass, XMLElement*& root, T&... object) {
		(xml::deserialize_process(object, isClass, root), ...);
	}

	// smart pointer
	template <typename T> void serialize_process(unique_ptr<T>& object, XMLDocument& doc, XMLElement* root, const char* labelName) {
		serialize_process(*(object.get()), doc, root, labelName);
	}

	template <typename T> void deserialize_process(unique_ptr<T>& object, bool isClass, XMLElement*& root) {
		object.reset(new T);
		deserialize_process(*(object.get()), false, root);
	}

	template <typename T> void serialize_process(shared_ptr<T>& object, XMLDocument& doc, XMLElement* root, const char* labelName) {
		serialize_process(*(object.get()), doc, root, labelName);
	}

	template <typename T> void deserialize_process(shared_ptr<T>& object, bool isClass, XMLElement*& root) {
		object.reset(new T);
		deserialize_process(*(object.get()), false, root);
	}

	// interface
	template <typename T> int serialize_xml(T& object, const char* labelName, const char* xmlPath) {
		XMLDocument doc;
		if (doc.LoadFile(xmlPath) != 3) {
			filesystem::remove(xmlPath);
			doc.LoadFile(xmlPath);
		}

		// add declaration
		XMLDeclaration* declaration = doc.NewDeclaration();
		doc.InsertFirstChild(declaration);

		XMLElement* root = doc.NewElement("serialization");
		doc.InsertEndChild(root);

		xml::serialize_process(object, doc, root, labelName);

		return doc.SaveFile(xmlPath);
	}

	template <typename T> int deserialize_xml(T& object, const char* labelName, const char* xmlPath) {
		XMLDocument doc;
		if (doc.LoadFile(xmlPath) != 0) {
			cout << "ERROR: Failed to load file " << xmlPath << endl;
			return 0;
		}

		XMLElement* root = doc.RootElement();
		XMLElement* node = root->FirstChildElement(labelName);
		if (node != NULL) {
			xml::deserialize_process(object, false, node);
			return 1;
		}
		else {
			cout << "ERROR: The file '" << xmlPath << "' do not have element named '" << labelName << "'." << endl;
			return 0;
		}
	}
};