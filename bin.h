#pragma once
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <memory>
using namespace std;

namespace bin {
	// arithmetic
	template<typename T> void serialize_process(T& object, ofstream& fout, typename enable_if<is_arithmetic<T>::value>::type* = 0) {
		fout.write((char*)(&object), sizeof(object));
	}

	template<typename T> void deserialize_process(T& object, ifstream& fin, typename enable_if<is_arithmetic<T>::value>::type* = 0) {
		fin.read((char*)(&object), sizeof(object));
	}

	// string
	void serialize_process(string& object, ofstream& fout) {
		size_t size = object.size();
		fout.write((char*)(&size), sizeof(size));
		fout.write(object.c_str(), size);
	}

	void deserialize_process(string& object, ifstream& fin) {
		size_t size;
		fin.read((char*)(&size), sizeof(size));
		object.resize(size);
		fin.read(&object[0], size);
	}

	// string (inside container)
	template<typename T> void serialize_process(T& object, ofstream& fout, typename enable_if<is_same<string, typename decay<T>::type>::value>::type* = 0) {
		size_t size = object.size();
		fout.write((char*)(&size), sizeof(size));
		fout.write(object.c_str(), size);
	}

	template<typename T> void deserialize_process(T& object, ifstream& fin, typename enable_if<is_same<string, typename decay<T>::type>::value>::type* = 0) {
		size_t size;
		fin.read((char*)(&size), sizeof(size));
		object.resize(size);
		fin.read(&object[0], size);
	}

	// pair
	template <typename T1, typename T2> void serialize_process(pair<T1, T2>& object, ofstream& fout) {
		bin::serialize_process(object.first, fout);
		bin::serialize_process(object.second, fout);
	}

	template <typename T1, typename T2> void deserialize_process(pair<T1, T2>& object, ifstream& fin) {
		bin::deserialize_process(object.first, fin);
		bin::deserialize_process(object.second, fin);
	}

	// vector
	template <typename T> void serialize_process(vector<T>& object, ofstream& fout) {
		int size = object.size();
		fout.write((char*)(&size), sizeof(size));
		for (typename vector<T>::iterator iter = object.begin(); iter != object.end(); iter++) bin::serialize_process(*iter, fout);
	}

	template <typename T> void deserialize_process(vector<T>& object, ifstream& fin) {
		int size;
		T item;
		fin.read((char*)(&size), sizeof(size));
		for (int i = 0; i < size; i++) {
			bin::deserialize_process(item, fin);
			object.push_back(item);
		}
	}

	// list
	template <typename T> void serialize_process(list<T>& object, ofstream& fout) {
		int size = object.size();
		fout.write((char*)(&size), sizeof(size));
		for (typename list<T>::iterator iter = object.begin(); iter != object.end(); iter++) bin::serialize_process(*iter, fout);
	}

	template <typename T> void deserialize_process(list<T>& object, ifstream& fin) {
		int size;
		T item;
		fin.read((char*)(&size), sizeof(size));
		for (int i = 0; i < size; i++) {
			bin::deserialize_process(item, fin);
			object.push_back(item);
		}
	}

	// set
	template <typename T> void serialize_process(set<T>& object, ofstream& fout) {
		int size = object.size();
		fout.write((char*)(&size), sizeof(size));
		for (typename set<T>::iterator iter = object.begin(); iter != object.end(); iter++) bin::serialize_process(*iter, fout);
	}

	template <typename T> void deserialize_process(set<T>& object, ifstream& fin) {
		int size;
		T item;
		fin.read((char*)(&size), sizeof(size));
		for (int i = 0; i < size; i++) {
			bin::deserialize_process(item, fin);
			object.insert(item);
		}
	}

	// map
	template <typename K, typename V> void serialize_process(map<K, V>& object, ofstream& fout) {
		int size = object.size();
		fout.write((char*)(&size), sizeof(size));
		for (typename map<K, V>::iterator iter = object.begin(); iter != object.end(); iter++) {
			bin::serialize_process(iter->first, fout);
			bin::serialize_process(iter->second, fout);
		}
	}

	template <typename K, typename V> void deserialize_process(map<K, V>& object, ifstream& fin) {
		int size;
		K key;
		V value;
		fin.read((char*)(&size), sizeof(size));
		for (int i = 0; i < size; i++) {
			bin::deserialize_process(key, fin);
			bin::deserialize_process(value, fin);
			object.insert(map<K, V>::value_type(key, value));
		}
	}

	// user-defined types
	template <typename T> void serialize_process(T& object, ofstream& fout, typename enable_if<is_class<T>::value>::type* = 0) {
		object.serialize(fout);
	}

	template <typename T> void deserialize_process(T& object, ifstream& fin, typename enable_if<is_class<T>::value>::type* = 0) {
		object.deserialize(fin);
	}

	template <typename... T> void enable_serialize(ofstream& fout, T... object) {
		(bin::serialize_process(object, fout), ...);
	}

	template <typename... T> void enable_deserialize(ifstream& fin, T&... object) {
		(bin::deserialize_process(object, fin), ...);
	}

	// smart pointer
	template <typename T> void serialize_process(unique_ptr<T>& object, ofstream& fout) {
		serialize_process(*(object.get()), fout);
	}

	template <typename T> void deserialize_process(unique_ptr<T>& object, ifstream& fin) {
		object.reset(new T);
		deserialize_process(*(object.get()), fin);
	}

	template <typename T> void serialize_process(shared_ptr<T>& object, ofstream& fout) {
		serialize_process(*(object.get()), fout);
	}

	template <typename T> void deserialize_process(shared_ptr<T>& object, ifstream& fin) {
		object.reset(new T);
		deserialize_process(*(object.get()), fin);
	}

	// interface
	template <typename T> void serialize(T& object, string file) {
		ofstream fout(file, ios::out | ios::binary);
		bin::serialize_process(object, fout);
		fout.close();
	}

	template <typename T> void deserialize(T& object, string file) {
		ifstream fin(file, ios::in | ios::binary);
		bin::deserialize_process(object, fin);
		fin.close();
	}
};