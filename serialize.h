#pragma once
#include "bin.h"
#include "xml.h"
#include "xml_base64.h"

// enable serialize for user-defined type
#define ENABLE_SER(...)\
void serialize(ofstream& fout) {bin::enable_serialize(fout, __VA_ARGS__);}\
void deserialize(ifstream& fin) {bin::enable_deserialize(fin, __VA_ARGS__);}\
void serialize_xml(XMLDocument& doc, XMLElement* root, const char* labelName) {xml::enable_xml_serialize(doc,root,labelName, __VA_ARGS__);}\
void deserialize_xml(bool isClass,XMLElement* root) {xml::enable_xml_deserialize(isClass,root, __VA_ARGS__);}\
void serialize_xml_base64(XMLDocument& doc, XMLElement* root, const char* labelName) {xml_base64::enable_xml_base64_serialize(doc,root,labelName, __VA_ARGS__);}\
void deserialize_xml_base64(bool isClass,XMLElement* root) {xml_base64::enable_xml_base64_deserialize(isClass,root, __VA_ARGS__);}