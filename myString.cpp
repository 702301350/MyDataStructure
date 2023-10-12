#include "myString.hpp"

//
// 初始化空串
//
String::String() {
	data = new char[1];
	*data = '\0';
}

//
// 初始化一个C字符串
//
String::String(const char* str) {
	if ( str != nullptr ) {
		data = new char[strlen(str) + 1];
		strcpy(data, str);
	}
	else {
		data = new char[1];
		*data = '\0';
	}
}

//
// 初始化复制一个字符串
//
String::String(const String& str) {
	data = new char[str.length() + 1];
	strcpy(data, str.data);
}

//
// 初始化移动一个字符串
//
String::String(String&& str) {
	data = str.data;
	str.data = nullptr;
}

//
// 析构函数
//
String::~String() {
	if ( data != nullptr ) {
		delete [] data;
	}
	data = nullptr;
}

//
// = 赋值重载
//
// @param str 赋值字符串值
//
String& String::operator=(const String& str) {
	if ( this != &str ) {
		if ( data != nullptr ) {
			delete [] data;
		}
		data = new char[str.length() + 1];
		strcpy(data, str.data);
	}
	return *this;
}

//
// = 赋值重载
//
// @param str 赋值常量C字符串
//
String& String::operator=(const char* str) {
	if ( data != nullptr ) {
		delete [] data;
	}
	data = new char [strlen(str) + 1];
	strcpy(data, str);
	return *this;
}

//
// == 判断重载
//
// @param str 待比较的字符串
//
bool String::operator==(const String& str) {
	return strcmp(data, str.data) == 0;
}

//
// == 判断重载
//
// @param str 带比较的常量C字符串
//
bool String::operator==(const char* str) {
	return strcmp(data, str) == 0;
}

//
// + 拼接重载
//
// @param str 待拼接字符串
const String String::operator+(const String& str) const {
	int len_this = length(), len_str = str.length();
	int len = len_this + len_str;
	char* tmp = new char[len + 1];

	for (int i = 0; i < len_this ;i ++) {
		tmp[i] = data[i];
	}
	for (int j = 0, i = len_this; j < len_str ;j ++) {
		tmp[i + j] = str.data[j];
	}

	tmp[len] = '\0';
	return String(tmp);
}

//
// + 拼接重载
//
// @param str 待拼接常量C字符串
//
const String String::operator+(const char* str) const {
	int len_this = length(), len_c = strlen(str);
	int len = len_this + len_c;
	char* tmp = new char[len + 1];
	
	for (int i = 0; i < len_this ;i ++) {
		tmp[i] = data[i];
	}
	for (int j = 0, i = len_this; j < len_c ;j ++) {
		tmp[i + j] = str[j];
	}

	tmp[len] = '\0';
	return String(tmp);
}

//
// += 拼接重载
//
// @param str 待拼接字符串
//
String& String::operator+=(const String& str) {
	int len_this = length(), len_str = str.length();
	int len = len_this + len_str;

	char* tmp = new char[len + 1];

	for (int i = 0;i < len_this;i ++) {
		tmp[i] = data[i];
	}
	for (int j = 0, i = len_this;j < len_str;j ++) {
		tmp[i + j] = str.data[j];
	}

	tmp[len] = '\0';

	delete [] data;
	data = tmp;
	return *this;
}

//
// += 拼接重载
//
// @param str 待拼接常量C字符串
//
String& String::operator+=(const char* str) {
	int len_this = length(), len_c = strlen(str);
	int len = len_this + len_c;
	char* tmp = new char[len + 1];

	for (int i = 0;i < len_this;i ++) {
		tmp[i] = data[i];
	}
	for (int j = 0, i = len_this;j < len_c;j ++) {
		tmp[i + j] = str[j];
	}

	tmp[len] = '\0';

	delete [] data;
	data = tmp;
	return *this;
}

//
// [] 查询重载
//
// @param idx 查询下标对应的元素
//
char& String::operator[](int idx) {
	if ( idx >= length() || idx < 0 ) {
		throw std::out_of_range("[String]: Idx Out Of Range!\n");
	}
	return data[idx];
}

//
// substr 截取字符串函数
//
// @param  idx 截取开始下标    len 截取长度
//
const String String::substr(int idx, int len) {
	if ( idx >= length() || idx < 0 ) {
		throw std::out_of_range("[String]: Idx Out Of Range!\n");
	}
	if ( idx + len >= length() || idx + len < 0 ) {
		throw std::out_of_range("[String]: Vaild Len!\n");
	}

	char* tmp = new char[len + 1];
	for (int i = 0;i < len;i ++) {
		tmp[i] = data[idx + i];
	}
	tmp[len] = '\0';
	return String(tmp);
}

//
// clear 清空字符串
//
void String::clear() {
	if ( data != nullptr ) {
		delete [] data;
	}
	data = new char[1];
	*data = '\0';
}

//
// pop_back 弹出最后一个元素
//
void String::pop_back() {
	if ( length() == 0 ) {
		throw std::out_of_range("[String]: Try To Pop An Empty String!\n");
	}

	data[length() - 1] = '\0';
}

//
// erase 删除字符段函数
//
// @param idx 删除开始下标      len删除长度
//
void String::erase(int idx, int len) {
	if ( idx >= length() || idx < 0 ) {
		throw std::out_of_range("[String]: Idx Out Of Range!\n");
	}
	if ( idx + len >= length() || idx + len < 0 ) {
		throw std::out_of_range("[String]: Vaild Len!\n");
	}
	
	int len_this = length();	
	int n = len_this - len;
	char* tmp = new char[n + 1];

	for (int i = 0, j = 0;j < len_this;j ++) {
		if ( j < idx || j >= idx + len ) {
			tmp[i ++] = data[j];
		}
	}

	tmp[n] = '\0';
	delete [] data;
	data = tmp;		
}

//
// c_str 获取C字符串
//
const char* String::c_str() const {
	return data;
}

//
// length 获取字符串长度函数
//
const size_t String::length() const {
	return strlen(data); 
}

//
// begin 获取第一个元素的位置
//
String::iterator String::begin() {
	return data;
}

//
// begin const 常量获取第一个元素位置
//
String::const_iterator String::begin() const {
	return data;
}

//
// begin 获取边界
//
String::iterator String::end() {
	return data + length();
}

//
// end const 常量获取边界
//
String::const_iterator String::end() const {
	return data + length();
}