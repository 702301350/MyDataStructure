#ifndef MYGLIST_IMPL_HPP_
#define MYGLIST_IMPL_HPP_

#include "myGList_decl.hpp"

//
//
//***********************************GListElement******************************************//

//
// isElement 判断是否为元素函数
//
template<typename T>
bool GListElement<T>::isElement() const {
	return true;
}

//
// data 获取数据函数
//
template<typename T>
const T GListElement<T>::data() const {
	return elem;
}

//
// = 重载
//
// @param val 提供值的变量
//
template<typename T>
GListElement<T>&  GListElement<T>::operator=(const T val) const {
	elem = val;
	return *this;
}

//
// = 重载
//
// @param element 提供值的GListElement元素
//
template<typename T>
GListElement<T>& GListElement<T>::operator=(const GListElement& other) const {
	elem = other.data();
	return *this;
}

//
// >> 重载
// 
// @param os 提供输出流      element 指定的GListElement元素
template<typename T>
std::ostream GListElement<T>::operator<<(std::ostream os, const GListElement& element) const {
	os << element.data();
	return os;	
}

//
//
//****************************************GList*******************************************//

//
// 模糊构造函数
// 
// @param node 初始化变量
//
// 该处 等号(=) 使用重载 
//
template<typename T>
GList<T>::GList(const GListNode& node) {
	this = node;
}

//
// 常量构造函数
//
// @param data 插入常量值
//
// 该处 等号(=) 使用重载
//
template<typename T>
GList<T>::GList(const T data) {
	this = data;
}

//
// = 重载  模糊赋值
// 
// @param node 提供赋值的变量
//
// 通过isElement判断具体类型
//
template<typename T>
GList<T>& GList<T>::operator=(const GListNode& node) const {
	if ( node.element() ) {
		GListElement* tmp = new GListElement();
		*tmp = static_cast<GListElement>(node).data();
		subList.clear();
		subList.push_back();
	}
	else {
		subList = static_cast<GList>(node).getSubList();
	}
	return *this;
}

//
// = 重载 常量值赋值
//
// @param val  提供值的常量
//
template<typename T>
GList<T>& GList<T>::operator=(const T val) const {
	GListElement* tmp = new GListElement(data);
	subList.push_back(tmp);
	return *this;
}

//
// isElement 判断是否为元素函数
//
template<typename T>
bool GList<T>::isElement() const {
	return false;
}

//
// getSubList 获取subList函数
//
template<typename T>
Array<GListNode<T>*>& GList<T>::getSubList() const {
	return subList;
}

#endif