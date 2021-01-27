#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <memory>
#include "../serialize.h"
using namespace std;

// user defined type
class student {
public:
	int id;
	string name;
	char province;
	double height;
	bool gender;
	vector<string> courses;
	map<int, float> grades;

	ENABLE_SER(id, name, province, height, gender, courses, grades);
};

struct UserDefinedType {
	int idx;
	string name;
	vector<double> data;

	ENABLE_SER(idx, name, data);
};

void testUserDefinedType();
void testSTLContainer();
void testSmartPointer();
void testBase64Code();

int main() {
	testUserDefinedType();
	testSTLContainer();
	testSmartPointer();
	testBase64Code();

	system("PAUSE");
	return 0;
}

void testUserDefinedType() {
	// test for class
	student s, t, u;
	s.id = 1;
	s.name = "ZhangSan";
	s.province = 'Z';
	s.height = 1.80;
	s.gender = true;
	s.courses.push_back("OOP");
	s.courses.push_back("Foundation of Software Engineering");
	s.grades[1] = 4.5;
	s.grades[2] = 4.2;
	s.grades[3] = 4.2;

	xml::serialize_xml(s, "class", "class.xml");
	xml::deserialize_xml(t, "class", "class.xml");

	bin::serialize(s, "class.data");
	bin::deserialize(u, "class.data");


	cout << "======= test user-defined types =======" << endl;

	cout << "Original data content of  class: " << endl;
	cout << "s.id: " << s.id << "\ts.name: " << s.name << "\ts.province: " << s.province << "\ts.height: " << s.height << "\ts.gender: " << s.gender << endl;
	cout << "s.courses: ";
	for (auto iter = s.courses.begin(); iter != s.courses.end(); iter++) cout << *iter << "\t";
	cout << endl;
	cout << "s.grades: \n";
	for (auto iter = s.grades.begin(); iter != s.grades.end(); iter++) cout << iter->first << " " << iter->second << endl;
	cout << endl << endl;

	cout << "The result of binary deserialize:" << endl;
	cout << "u.id: " << u.id << "\tu.name: " << u.name << "\tu.province: " << u.province << "\tu.height: " << u.height << "\tu.gender: " << u.gender << endl;
	cout << "u.courses: ";
	for (auto iter = u.courses.begin(); iter != u.courses.end(); iter++) cout << *iter << "\t";
	cout << endl;
	cout << "u.grades: \n";
	for (auto iter = u.grades.begin(); iter != u.grades.end(); iter++) cout << iter->first << " " << iter->second << endl;
	cout << endl << endl;

	cout << "The result of xml deserialize:" << endl;
	cout << "t.id: " << t.id << "\tt.name: " << t.name << "\tt.province: " << t.province << "\tt.height: " << t.height << "\tt.gender: " << t.gender << endl;
	cout << "t.courses: ";
	for (auto iter = t.courses.begin(); iter != t.courses.end(); iter++) cout << *iter << "\t";
	cout << endl;
	cout << "t.grades: \n";
	for (auto iter = t.grades.begin(); iter != t.grades.end(); iter++) cout << iter->first << " " << iter->second << endl;
	cout << endl << endl;

	// test for struct
	struct UserDefinedType l, m, n;
	l.idx = 1;
	l.name = "Peter";
	l.data.push_back(1.111);
	l.data.push_back(2.222);

	bin::serialize(l, "class.data");
	bin::deserialize(m, "class.data");

	xml::serialize_xml(l, "student", "student.xml");
	xml::deserialize_xml(n, "student", "student.xml");

	cout << "Original data content of  struct: " << endl;
	cout << "l.idx: " << l.idx << "\tl.name: " << l.name << endl;
	cout << "l.data: ";
	for (auto iter = l.data.begin(); iter != l.data.end(); iter++) cout << *iter << "\t";
	cout << endl << endl;

	cout << "The result of binary deserialize:" << endl;
	cout << "m.idx: " << m.idx << "\tm.name: " << m.name << endl;
	cout << "m.data: ";
	for (auto iter = m.data.begin(); iter != m.data.end(); iter++) cout << *iter << "\t";
	cout << endl << endl;

	cout << "The result of xml deserialize:" << endl;
	cout << "n.id: " << n.idx << "\tn.name: " << n.name << endl;
	cout << "t.courses: ";
	for (auto iter = n.data.begin(); iter != n.data.end(); iter++) cout << *iter << "\t";
	cout << endl << endl;
}

void testSTLContainer() {
	// other STL containers
	pair<string, int> pair0 = { "Peter", 1 }, pair1, pair2;

	bin::serialize(pair0, "pair.data");
	bin::deserialize(pair1, "pair.data");

	xml::serialize_xml(pair0, "std_pair", "pair.xml");
	xml::deserialize_xml(pair2, "std_pair", "pair.xml");

	list<char> list0, list1, list2;
	list0.push_back('A');
	list0.push_back('B');
	list0.push_back('#');

	bin::serialize(list0, "list.data");
	bin::deserialize(list1, "list.data");

	xml::serialize_xml(list0, "std_list", "list.xml");
	xml::deserialize_xml(list2, "std_list", "list.xml");

	set<double> set0, set1, set2;
	set0.insert(100.1);
	set0.insert(200.22);
	set0.insert(300.333);

	bin::serialize(set0, "set.data");
	bin::deserialize(set1, "set.data");

	xml::serialize_xml(set0, "std_set", "set.xml");
	xml::deserialize_xml(set2, "std_set", "set.xml");

	cout << "======= test STL container: pair, list, set =======" << endl;
	cout << "Original data content of pair0, list0, set0: " << endl;
	cout << "pair0: " << pair0.first << ", " << pair0.second << endl;
	cout << "list0: ";
	for (auto iter = list0.begin(); iter != list0.end(); iter++) cout << *iter << " ";
	cout << endl;
	cout << "set0: ";
	for (auto iter = set0.begin(); iter != set0.end(); iter++) cout << *iter << " ";
	cout << endl << endl;

	cout << "The result of binary deserialize:" << endl;
	cout << "pair1: " << pair1.first << ", " << pair1.second << endl;
	cout << "list1: ";
	for (auto iter = list1.begin(); iter != list1.end(); iter++) cout << *iter << " ";
	cout << endl;
	cout << "set1: ";
	for (auto iter = set1.begin(); iter != set1.end(); iter++) cout << *iter << " ";
	cout << endl << endl;

	cout << "The result of xml deserialize:" << endl;
	cout << "pair2: " << pair2.first << ", " << pair2.second << endl;
	cout << "list2: ";
	for (auto iter = list2.begin(); iter != list2.end(); iter++) cout << *iter << " ";
	cout << endl;
	cout << "set2: ";
	for (auto iter = set2.begin(); iter != set2.end(); iter++) cout << *iter << " ";
	cout << endl << endl;
}

void testSmartPointer() {
	shared_ptr<student> sp1(new student);
	shared_ptr<student> sp2, sp3;

	unique_ptr<student> up1(new student);
	unique_ptr<student> up2, up3;

	// share_ptr
	sp1->id = 1;
	sp1->name = "ZhangSan";
	sp1->province = 'Z';
	sp1->height = 1.80;
	sp1->gender = true;
	sp1->courses.push_back("OOP");
	sp1->courses.push_back("Foundation of Software Engineering");
	sp1->grades[1] = 4.5;
	sp1->grades[2] = 4.2;
	sp1->grades[3] = 4.2;

	bin::serialize(sp1, "shared_p.data");
	bin::deserialize(sp2, "shared_p.data");

	xml::serialize_xml(sp1, "shared_ptr", "shared_p.xml");
	xml::deserialize_xml(sp3, "shared_ptr", "shared_p.xml");

	cout << "======= test smart pointer =======" << endl;
	cout << "Original data content of shared_ptr: " << endl;
	cout << "id: " << sp1->id << "\tname: " << sp1->name << "\tprovince: " << sp1->province << "\theight: " << sp1->height << "\tgender: " << sp1->gender << endl;
	cout << "courses: ";
	for (auto iter = sp1->courses.begin(); iter != sp1->courses.end(); iter++) cout << *iter << "\t";
	cout << endl;
	cout << "grades: \n";
	for (auto iter = sp1->grades.begin(); iter != sp1->grades.end(); iter++) cout << iter->first << " " << iter->second << endl;
	cout << endl << endl;

	cout << "The result of binary deserialize:" << endl;
	cout << "id: " << sp2->id << "\tname: " << sp2->name << "\tprovince: " << sp2->province << "\theight: " << sp2->height << "\tu.gender: " << sp2->gender << endl;
	cout << "courses: ";
	for (auto iter = sp2->courses.begin(); iter != sp2->courses.end(); iter++) cout << *iter << "\t";
	cout << endl;
	cout << "grades: \n";
	for (auto iter = sp2->grades.begin(); iter != sp2->grades.end(); iter++) cout << iter->first << " " << iter->second << endl;
	cout << endl << endl;

	cout << "The result of xml deserialize:" << endl;
	cout << "id: " << sp3->id << "\tname: " << sp3->name << "\tprovince: " << sp3->province << "\theight: " << sp3->height << "\tu.gender: " << sp3->gender << endl;
	cout << "courses: ";
	for (auto iter = sp3->courses.begin(); iter != sp3->courses.end(); iter++) cout << *iter << "\t";
	cout << endl;
	cout << "grades: \n";
	for (auto iter = sp3->grades.begin(); iter != sp3->grades.end(); iter++) cout << iter->first << " " << iter->second << endl;
	cout << endl << endl;

	// unique_ptr
	up1->id = 2;
	up1->name = "LiSi";
	up1->province = 'J';
	up1->height = 1.70;
	up1->gender = false;
	up1->courses.push_back("Principles of Information security");
	up1->courses.push_back("Computer Organization");
	up1->grades[1] = 5.0;
	up1->grades[2] = 3;
	up1->grades[3] = 3.3;

	bin::serialize(up1, "unique_p.data");
	bin::deserialize(up2, "unique_p.data");

	xml::serialize_xml(up1, "unique_ptr", "unique_p.xml");
	xml::deserialize_xml(up3, "unique_ptr", "unique_p.xml");

	cout << "Original data content of unique_ptr: " << endl;
	cout << "id: " << up1->id << "\tname: " << up1->name << "\tprovince: " << up1->province << "\theight: " << up1->height << "\tgender: " << up1->gender << endl;
	cout << "courses: ";
	for (auto iter = up1->courses.begin(); iter != up1->courses.end(); iter++) cout << *iter << "\t";
	cout << endl;
	cout << "grades: \n";
	for (auto iter = up1->grades.begin(); iter != up1->grades.end(); iter++) cout << iter->first << " " << iter->second << endl;
	cout << endl << endl;

	cout << "The result of binary deserialize:" << endl;
	cout << "id: " << up2->id << "\tname: " << up2->name << "\tprovince: " << up2->province << "\theight: " << up2->height << "\tu.gender: " << up2->gender << endl;
	cout << "courses: ";
	for (auto iter = up2->courses.begin(); iter != up2->courses.end(); iter++) cout << *iter << "\t";
	cout << endl;
	cout << "grades: \n";
	for (auto iter = up2->grades.begin(); iter != up2->grades.end(); iter++) cout << iter->first << " " << iter->second << endl;
	cout << endl << endl;

	cout << "The result of xml deserialize:" << endl;
	cout << "id: " << up3->id << "\tname: " << up3->name << "\tprovince: " << up3->province << "\theight: " << up3->height << "\tu.gender: " << up3->gender << endl;
	cout << "courses: ";
	for (auto iter = up3->courses.begin(); iter != up3->courses.end(); iter++) cout << *iter << "\t";
	cout << endl;
	cout << "grades: \n";
	for (auto iter = up3->grades.begin(); iter != up3->grades.end(); iter++) cout << iter->first << " " << iter->second << endl;
	cout << endl << endl;
}

void testBase64Code() {
	student s, t;
	s.id = 3;
	s.name = "WangWu";
	s.province = 'H';
	s.height = 1.66;
	s.gender = true;
	s.courses.push_back("Database System");
	s.courses.push_back("Linear Algebra");
	s.grades[1] = 4;
	s.grades[2] = 4.1;
	s.grades[3] = 0.0001;

	xml_base64::serialize_xml_base64(s, "base64", "base64.xml");
	xml_base64::deserialize_xml_base64(t, "base64", "base64.xml");

	cout << "======= test binary-to-text encoding/decoding (base64) =======" << endl;
	cout << "Original data content of  class: " << endl;
	cout << "s.id: " << s.id << "\ts.name: " << s.name << "\ts.province: " << s.province << "\ts.height: " << s.height << "\ts.gender: " << s.gender << endl;
	cout << "s.courses: ";
	for (auto iter = s.courses.begin(); iter != s.courses.end(); iter++) cout << *iter << "\t";
	cout << endl;
	cout << "s.grades: \n";
	for (auto iter = s.grades.begin(); iter != s.grades.end(); iter++) cout << iter->first << " " << iter->second << endl;
	cout << endl << endl;

	cout << "The result of xml deserialize:" << endl;
	cout << "t.id: " << t.id << "\tt.name: " << t.name << "\tt.province: " << t.province << "\tt.height: " << t.height << "\tt.gender: " << t.gender << endl;
	cout << "t.courses: ";
	for (auto iter = t.courses.begin(); iter != t.courses.end(); iter++) cout << *iter << "\t";
	cout << endl;
	cout << "t.grades: \n";
	for (auto iter = t.grades.begin(); iter != t.grades.end(); iter++) cout << iter->first << " " << iter->second << endl;
	cout << endl << endl;
}