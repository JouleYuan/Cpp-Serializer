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
#include "base64.h"
#include "tinyxml2.h" 
using namespace std;
using namespace tinyxml2;

namespace xml_base64 {
	// arithmetic
	template<typename T> void serialize_process(T& object, XMLDocument& doc, XMLElement* root, const char* labelName, typename enable_if<is_arithmetic<T>::value>::type* = 0) {
		XMLElement* newNode = doc.NewElement(labelName);
		ostringstream oss;
		oss << object;
		string str = encode_base64(oss.str());

		newNode->SetAttribute("val", str.c_str());
		root->InsertEndChild(newNode);
	}

	template<typename T> void deserialize_process(T& object, bool isClass, XMLElement*& root, typename enable_if<is_arithmetic<T>::value>::type* = 0) {
		if (!root) {
			cout << "ERROR: Data type mismatch." << endl;
		}

		// get the value
		const char* v = root->Attribute("val");
		if (v) {
			bool b = true;
			string str(v);
			string value = decode_base64(str);

			// if object is char
			if (typeid(object).name() == typeid('c').name()) {
				object = value.at(0);
			}
			// if object is bool
			else if (typeid(object).name() == typeid(b).name()) {
				if (value.at(0) == '1')
					object = true;
				else 
					object = false;
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
		string str = encode_base64(object);

		newNode->SetAttribute("val", str.c_str());
		root->InsertEndChild(newNode);
	}

	void deserialize_process(string& object, bool isClass, XMLElement*& root) {
		if (!root) {
			cout << "ERROR: Data type mismatch." << endl;
		}

		// get the value
		const char* v = root->Attribute("val");
		if (v) {
			string str(v);
			string value = decode_base64(str);
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

		xml_base64::serialize_process(object.first, doc, newNode, "first");
		xml_base64::serialize_process(object.second, doc, newNode, "second");
	}

	template <typename T1, typename T2> void deserialize_process(pair<T1, T2>& object, bool isClass, XMLElement*& root) {
		if (!root) {
			cout << "ERROR: Data type mismatch." << endl;
		}

		XMLElement* first = root->FirstChildElement("first");
		XMLElement* second = root->FirstChildElement("second");

		xml_base64::deserialize_process(object.first, false, first);
		xml_base64::deserialize_process(object.second, false, second);

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
			xml_base64::serialize_process(*iter, doc, newNode, "vector_item");
		}
	}

	template <typename T> void deserialize_process(vector<T>& object, bool isClass, XMLElement*& root) {
		if (!root) {
			cout << "ERROR: Data type mismatch." << endl;
		}

		XMLElement* child = root->FirstChildElement();
		T item;
		while (child != NULL) {
			xml_base64::deserialize_process(item, false, child);
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
			xml_base64::serialize_process(*iter, doc, newNode, "list_item");
		}
	}

	template <typename T> void deserialize_process(list<T>& object, bool isClass, XMLElement*& root) {
		if (!root) {
			cout << "ERROR: Data type mismatch." << endl;
		}

		XMLElement* child = root->FirstChildElement();
		T item;
		while (child != NULL) {
			xml_base64::deserialize_process(item, false, child);
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
			xml_base64::serialize_process(*iter, doc, newNode, "set_item");
		}
	}

	template <typename T> void deserialize_process(set<T>& object, bool isClass, XMLElement*& root) {
		if (!root) {
			cout << "ERROR: Data type mismatch." << endl;
		}

		XMLElement* child = root->FirstChildElement();
		T item;
		while (child != NULL) {
			xml_base64::deserialize_process(item, false, child);
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

			xml_base64::serialize_process(iter->first, doc, newNode->LastChildElement(), "first");
			xml_base64::serialize_process(iter->second, doc, newNode->LastChildElement(), "second");
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

			xml_base64::deserialize_process(key, false, first);
			xml_base64::deserialize_process(value, false, second);
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

		object.serialize_xml_base64(doc, newNode, "class_member");
	}

	template<typename T> void deserialize_process(T& object, bool isClass, XMLElement* root, typename enable_if<is_class<T>::value>::type* = 0) {
		XMLElement* newNode = root->FirstChildElement();
		object.deserialize_xml_base64(true, newNode);
	}

	template <typename... T> void enable_xml_base64_serialize(XMLDocument& doc, XMLElement* root, const char* labelName, T... object) {
		(xml_base64::serialize_process(object, doc, root, labelName), ...);
	}

	template <typename... T> void enable_xml_base64_deserialize(bool isClass, XMLElement*& root, T&... object) {
		(xml_base64::deserialize_process(object, isClass, root), ...);
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
	template <typename T> int serialize_xml_base64(T& object, const char * labelName, const char* xmlPath) {
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

		xml_base64::serialize_process(object, doc, root, labelName);

		return doc.SaveFile(xmlPath);
	}

	template <typename T> int deserialize_xml_base64(T& object, const char * label_name, const char* file_path) {
		XMLDocument doc;
		if (doc.LoadFile(file_path) != 0) {
			cout << "ERROR: Failed to load file " << file_path << endl;
			return 0;
		}

		XMLElement* root = doc.RootElement();
		XMLElement* node = root->FirstChildElement(label_name);
		if (node != NULL) {
			xml_base64::deserialize_process(object, false, node);
			return 1;
		}
		else {
			cout << "ERROR: The file '" << file_path << "' do not have element named '" << label_name << "'." << endl;
			return 0;
		}
	}
};