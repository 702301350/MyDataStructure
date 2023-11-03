#ifndef MYSTRING_HPP_
#define MYSTRING_HPP_

#include "myDef.hpp"

#include <cstring>
#include <iostream>

class String {
	private:
		char* data;

		using iterator = char*;
		using const_iterator = const char*;
	public:
		String();
		String(const char* str);
		String(const String& str);
		String(String&& str);
		~String();

		// =重载
		String& operator=(const String& str);

		// =重载
		String& operator=(const char* str);

		// ==重载
		bool operator==(const String& str) const;

		// ==重载
		bool operator==(const char* str) const;

		// != 重载
		bool operator!=(const String& str) const;

		// ！= 重载
		bool operator!=(const char* str) const;

		// +重载，拼接
		const String operator+(const String& str) const;

		// +重载，拼接
		const String operator+(const char* str) const;

		// +=重载，拼接
		String& operator+=(const String& str);

		// += 重载，拼接
		String& operator+=(const char* str);

		// << 重载输出
		friend std::ostream& operator<<(std::ostream& os, const String& str) {
			os << str.data;
			return os;
		} 

		// >> 重载输入
		friend std::istream& operator>>(std::istream& in, String& str) {
			in >> str.data;
			return in;
		}

		// []重载，查询第idx个元素
		char& operator[](int idx);

		// []重载，查询第idx个元素 常量
		const char& operator[](int idx) const;

		// 清空字符串
		void clear();

		// 弹出最后一个
		void pop_back();

		// 获取原字符串
		const char* c_str() const;

		// 获取字符串大小
		const size_t length() const;

		//截取字符串
		const String substr(int idx, int len);

		//删除字符串
		void erase(int idx, int len);

		// begin 获取第一个元素值
		iterator begin();

		// end 获取边界
		iterator end();

		// begin const 常量化获取第一个元素值
		const_iterator begin() const;

		// end const 常量化获取边界
		const_iterator end() const;
};

namespace std {
	template<>
	class hash<String> {
	public:
		size_t operator()(const String& str) const {
			return hash<const char*>()(str.c_str());
		}
	};
};

#endif