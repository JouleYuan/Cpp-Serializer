# Cpp-Serializer

This is a simple C++ serialization and deserialization library, which support binary, XML and base64 coded XML serialization and deserialization. 

At the present, the library can serialize and deserialize the following types: arithmetic (see [std::is_arithmetic](https://en.cppreference.com/w/cpp/types/is_arithmetic)), C++ string type (`std::string`), STL containers (`std::pair`, `std::vector`, `std::list`, `std::set`, and `std::map`), smart pointer (`std::shared_ptr` and `std::unique_ptr`) and user-defined types (`struct` and `class`).

Besides, the implementation of XML and base64 coded XML serialization and deserialization uses the [tinyxml2](https://github.com/leethomason/tinyxml2) library.

Please note that this library is only available for C++17 or higher version. Moreover, since it has only been tested with MSVC compiler, it is possible that this library does not work well with other compiler.

## Quick Start

First, you have to import the library.

```c++
#include "serialize.h"
```

For binary serialization, use `bin::serialize(object, file_path)` to serialize the object in binary form and store the data in the file which is specified by the file_path. After that, you can use `bin::deserialize(object, file_path)` to deserialize the data from file in the file_path and store the deserialized data in the object. 

For XML serialization and deserialization, use `xml::serialize_xml(object, lable_name, file_path)` and `xml::deserialize_xml(object, label_name, file_path)` respectively. The label_name is used to specify the root label in the XML file.

For base64 coded XML serialization and deserialization, use `xml_base64::serialize_xml_base64(object, label_name, file_path)` and `xml_base64::serialize_xml_base64(object, label_name, file_path)` respectively.

And here's a simple demo.

```c++
list<char> list0, list1, list2, list3;
list0.push_back('A');
list0.push_back('B');
list0.push_back('#');

bin::serialize(list0, "list.data");
bin::deserialize(list1, "list.data");

xml::serialize_xml(list0, "std_list", "list.xml");
xml::deserialize_xml(list2, "std_list", "list.xml");

xml_base64::serialize_xml_base64(list0, "std_list", "list_base64.xml");
xml_base64::deserialize_xml_base64(list3, "std_list", "list_base64.xml");
```

If you want to serialize user-defined types, including `struct` and `class`, add a claim `ENABLE_SER(__VA_ARGS__)` in the definition.

```c++
class UserDefinedType {
public:
    int idx;
	string name;
	vector<double> data;

	ENABLE_SER(idx, name, data);
};
```

## About

This library is developed by Yuan Haoran and Wang Chenlu. If you have any new idea about this library, you can create a new issue or  your pull request at any time.
