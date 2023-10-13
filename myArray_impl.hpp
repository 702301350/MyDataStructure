#ifndef MYARRAY_IMPL_HPP_
#define MYARRAY_IMPL_HPP_

#include "myArray_decl.hpp"

//
// 默认构造函数
//
template<typename T>
Array<T>::Array() {
	data = nullptr;
	length = 0;
}

//
// 只初始化长度的构造函数
//
template<typename T>
Array<T>::Array(size_t len) {
	data = new T[len];
	length = len;
}

//
// 初始化长度和默认值的构造函数
//
template<typename T>
Array<T>::Array(size_t len, T val) {
	data = new T[len];
	length = len;
	for (int i = 0;i < length;i ++) {
		data[i] = val;
	}
}

//
// 通过其他Array赋值的构造函数
//
template<typename T>
Array<T>::Array(const Array& other) {
	length = other.size();
	data = new T[length];

	int idx = 0;
	for (const auto &x : other) {
		data[idx ++] = x;
	}
}

//
// 通过 {} 赋值的构造函数
//
template<typename T>
Array<T>::Array(std::initializer_list<T> val) {
	length = val.size();
	data = new T[length];

	int idx = 0;
	for (const auto &x : val) {
		data[idx ++] = x;
	}
}

//
// erase 删除函数
// 
// @param idx 删除元素的下标
//
template<typename T>
void Array<T>::erase(int idx) {
	if ( idx >= length || idx < 0 ) {
		throw std::out_of_range("[Array]: Idx Out Of Range!\n");
	}
	else {
		T* tmp = new T [length - 1];

		for (int i = 0, j = 0;i < length;i ++) {
			if ( i != idx ) {
				tmp[j ++] = data[i];
			}
		}

		delete [] data;
		data = tmp;
		length --;
	}
}

//
// erase 删除函数
// 
// @param it 按照迭代器删除元素
//
template<typename T>
void Array<T>::erase(Array<T>::iterator it) {
	if ( it == end() ) {
		throw std::out_of_range("[Array]: Iterator Out Of Range");
	}
	else {
		T* tmp = new T [length - 1];

		for (auto i = begin(), j = tmp; i != end() ;i ++) {
			if ( i != it ) {
				*j = *i;
				j ++;
			}
		}

		delete [] data;
		data = tmp;
		length --;
	}
}

//
// [] 重载
//
// @param idx 查询元素的下标
//
// 越界元素交给编译器处理，给出适当提示
template<typename T>
T& Array<T>::operator[](int idx) {
	if ( idx < 0 || idx >= length ) {
		throw std::out_of_range("[Array]: Idx Out Of Range!\n");
	}
	return data[idx];
}

//
// [] 重载
//
// @param idx 查询元素的下标
//
// 越界元素交给编译器处理，给出适当提示
template<typename T>
const T& Array<T>::operator[](int idx) const {
	if ( idx < 0 || idx >= length ) {
		throw std::out_of_range("[Array]: Idx Out Of Range!\n");
	}
	return data[idx];
}

//
// = 重载
//
// @param other 提供赋值的Array
//
template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
	if ( other.data != data ) {
		clear();
		length = other.size();
		data = new T[length];
		
		int idx = 0;
		for (const auto &x : other) {
			data[idx ++] = x;
		}
	}
	return *this;	
}

//
// back 返回最后一个元素的值
//
template<typename T>
T& Array<T>::back() {
	if ( empty() ) {
		throw std::out_of_range("[Array]: Try To Get Element From A Empty Array!\n");
	}
	return data[length - 1];
}

//
// clear 清空函数
//
template<typename T>
void Array<T>::clear() {
	if ( data != nullptr ) {
		delete [] data;
	}
	data = nullptr;
	length = 0;
}

//
// insert 在指定位置插入元素
// 
// @param val 插入元素值    idx 插入位置下标
//
template<typename T>
void Array<T>::insert(T val, int idx) {
	T *tmp = new T [++ length];

	for (int i = 0, j = 0;i < length;i ++) {
		if ( i == idx ) {
			tmp[i] = val;
		}
		else {
			tmp[i] = data[j ++];
		}
	}

	delete [] data;
	data = tmp;
}


//
// push_back 尾部添加元素函数
//
// @param val 添加元素值
//
template<typename T>
void Array<T>::push_back(T val) {
	insert(val, length);
}

//
// size 返回数组大小函数
//
template<typename T>
const size_t Array<T>::size() const {
	return length;
}

//
// empty 返回数组是否为空函数
//
template<typename T>
bool Array<T>::empty() {
	return length == 0;
}

//
// begin 返回第一个元素的位置
//
template<typename T>
typename Array<T>::iterator Array<T>::begin() {
	return data;
}

//
// begin const 常量形式的begin
//
template<typename T>
typename Array<T>::const_iterator Array<T>::begin() const {
	return data;
}

//
// end 返回第一个超出范围的元素的位置
//
template<typename T>
typename Array<T>::iterator Array<T>::end() {
	return data + length;
}

//
// end const 常量形式的end
//
template<typename T>
typename Array<T>::const_iterator Array<T>::end() const {
	return data + length;
}

//
// getData 返回data
//
template<typename T>
T* Array<T>::getData() {
	return data;
}

#endif
