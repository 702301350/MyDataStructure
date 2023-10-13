#ifndef MYGLIST_IMPL_HPP_
#define MYGLIST_IMPL_HPP_

#include "myGList_decl.hpp"

//
//
//***********************************GListNode******************************************//

//
// 输出全局函数 
//
// @param os 输出流     node GListNode类型
//
template<typename T>
std::ostream& operator<<(std::ostream& os,const GListNode<T>& node) {
	if ( node.isElement() ) {
		const GListElement<T>& element = dynamic_cast<const GListElement<T>&>(node);
		os << element.data();
	}
	else {
		const GList<T>& list = dynamic_cast<const GList<T>&>(node);

		os << "(";

		int flag = 0, len = list.size();
		for (int i = 0; i < len; i ++) {
			os << ((flag) ? ",": "");
			if ( list[i].isElement() ) {
				os << dynamic_cast<const GListElement<T>&>(list[i]);
			}
			else {
				os << dynamic_cast<const GList<T>&>(list[i]);
			}
			flag = 1;
		}
		os << ")";
	}
	return os;
}

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
GListElement<T>&  GListElement<T>::operator=(const T val) {
	elem = val;
	return *this;
}

//
// = 重载
//
// @param element 提供值的GListElement元素
//
template<typename T>
GListElement<T>& GListElement<T>::operator=(const GListElement<T>& other) {
	elem = other.data();
	return *this;
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
GList<T>::GList(const GListNode<T>& node) {
	if ( node.isElement() ) {
		GListElement<T>* tmp = new GListElement<T>(dynamic_cast<const GListElement<T>&>(node).data());
		subList.push_back(tmp);
	}
	else {
		subList = dynamic_cast<const GList<T>&>(node).getSubList();
	}
}

//
// 常量构造函数
//
// @param data 插入常量值
//
// 该处 等号(=) 使用重载
//
template<typename T>
GList<T>::GList(const T val) {
	subList.push_back(new GListElement<T>(val));
}

//
// 通过GList数组初始化构造函数
//
// @param array 提供数据的数组
//
template<typename T>
GList<T>::GList(const Array<GListNode<T>*>& array) {
	subList = array;
}


//
// 通过Array数组初始化构造函数
//
// @param array 提供数据数组 
//
template<typename T>
GList<T>::GList(const Array<T>& array) {
	for (auto &x : array) {
		subList.push_back(new GListElement<T>(x));		
	}
}

//
// 通过 {} 赋值
//
template<typename T>
GList<T>::GList(std::initializer_list<GList<T>> val) {
	for (const GList<T>& x : val) {
		if ( x.size() == 1 && x.front().isElement() ) {
			T y = dynamic_cast<const GListElement<T>&>(x.front()).data();
			subList.push_back(new GListElement<T>(y));
		}
		else {
			subList.push_back(new GList<T>(x));
		}
	}
}

//
// = 重载  模糊赋值
// 
// @param node 提供赋值的变量
//
// 通过isElement判断具体类型
//
template<typename T>
GList<T>& GList<T>::operator=(const GListNode<T>& node) {
	if ( node.isElement() ) {
		GListElement<T>* tmp = new GListElement<T>(dynamic_cast<const GListElement<T>&>(node).data());
		subList.clear();
		subList.push_back(tmp);
	}
	else {
		subList = dynamic_cast<const GList<T>&>(node).getSubList();
	}
	return *this;
}

//
// = 重载 常量值赋值
//
// @param val  提供值的常量
//
template<typename T>
GList<T>& GList<T>::operator=(const T val) {
	GListElement<T>* tmp = new GListElement<T>(val);
	subList.push_back(tmp);
	return *this;
}

//
// [] 重载 查询第idx个广义表
//
// @param idx 查询下标
//
template<typename T>
GListNode<T>& GList<T>::operator[](int idx) {
	if ( idx < 0 || idx >= subList.size() ) {
		throw std::out_of_range("[GList]: Idx Out Of Range!\n");
	}

	if ( subList[idx] -> isElement() ) {
		return *dynamic_cast<GListElement<T>*>(subList[idx]);
	}
	else{
		return *dynamic_cast<GList<T>*>(subList[idx]);
	}
}

//
// [] 重载 查询第idx个广义表 常量
//
// @param idx 查询下标
//
template<typename T>
const GListNode<T>& GList<T>::operator[](int idx) const {
	if ( idx < 0 || idx >= subList.size() ) {
		throw std::out_of_range("[GList]: Idx Out Of Range!\n");
	}

	if ( subList[idx] -> isElement() ) {
		return *dynamic_cast<GListElement<T>*>(subList[idx]);
	}
	else{
		return *dynamic_cast<GList<T>*>(subList[idx]);
	}
}

//
// isElement 判断是否为元素函数
//
template<typename T>
bool GList<T>::isElement() const {
	return false;
}

//
// push_back 尾部插入函数
//
// @param val 待插入值
//
template<typename T>
void GList<T>::push_back(GListNode<T>& node) {
	if ( node.isElement() ) {
		subList.push_back(dynamic_cast<GListElement<T>*>(&node));
	}
	else {
		subList.push_back(dynamic_cast<GList<T>*>(&node));
	}
}

//
// push_back 尾部插入常数函数
//
// @param val 插入常数值
//
template<typename T>
void GList<T>::push_back(const T val) {
	subList.push_back(new GListElement<T>(val));
}

//
// push_back 尾部插入数组
//
// @param array 插入数组
//
template<typename T>
void GList<T>::push_back(const Array<T>& array) {
	GList<T>* tmp = new GList<T>();
	for (const auto &x : array) {
		GListElement<T>* element = new GListElement<T>(x);
		tmp -> push_back(*element);
	}
	subList.push_back(tmp);
}

//
// erase 删除函数
//
// @param idx 删除元素的下标
//
template<typename T>
void GList<T>::erase(int idx) {
	if ( idx < 0 || idx >= subList.size() ) {
		throw std::out_of_range("[GList]: Idx Out Of Range!\n");
	}
	
	subList.erase(idx);
}

//
// clear 清空函数
//
template<typename T>
void GList<T>::clear() {
	subList.clear();
}

//
// front 获取表内第一个元素
//
template<typename T>
const GListNode<T>& GList<T>::front() const {
	GListNode<T>* tmp = subList[0];
	if ( tmp -> isElement() ) {
		return *dynamic_cast<GListElement<T>*>(tmp);
	}
	else {
		return *dynamic_cast<GList<T>*>(tmp);
	}
}

//
// at 获取第layer层的所有广义表
//
// @param layer 指定层
//
template<typename T>
GList<T> GList<T>::at(int layer) {
	GList<T> tmp;
	bfs(&tmp, layer);
	return tmp;
}

//
// size 获取广义表的大小
//
template<typename T>
const size_t GList<T>::size() const {
	return subList.size();
}

//
// deepth 获取广义表的深度
//
//!
template<typename T>
size_t GList<T>::deepth() {
	return bfs(nullptr, MY_NOT_LIMIT);
}

//
// getSubList 获取subList函数
//
template<typename T>
const Array<GListNode<T>*>& GList<T>::getSubList() const {
	return subList;
}

//
// bfs 深度搜索
//
// @param list 搜索得到的广义表       layer 搜索的层数
//
template<typename T>
size_t GList<T>::bfs(GList<T>* list, int layer) {
	size_t deep = 0;
	Queue<GListNode<T>*>q, qN;
	
	if ( !subList.size() ) return 0;

	q.push(subList[0]);

	while ( !q.empty() ) {
		GListNode<T>* tmp = q.front();
		q.pop();

		if ( !(tmp -> isElement()) ) {
			GList<T>* ttmp = dynamic_cast<GList<T>*>(tmp);
			for (GListNode<T>* x : ttmp -> getSubList()) {
				if ( !(x -> isElement()) ) { 
					qN.push(x);

					if ( list != nullptr && layer != MY_NOT_LIMIT ) {
						if (deep == layer) { 
							list -> push_back(*x);
						}
						else if ( deep > layer ) {
							return deep;
						}
					}
				}
			}
		}

		if ( !qN.empty() && q.empty() ) {
			q = qN;
			qN.clear();
			deep ++;
		}  
	}

	return deep;	
}

#endif