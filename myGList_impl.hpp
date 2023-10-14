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

		int flag = 0;
		for (GListNode<T>* x : list.getSubList()) {
			os << ((flag) ? ",": "");
			if ( x -> isElement() ) {
				os << dynamic_cast<const GListElement<T>&>(*x);
			}
			else {
				os << dynamic_cast<const GList<T>&>(*x);
			}
			flag = 1;
		}
		os << ")";
	}
	return os;
}

//
// modify 修改GListNode
//
// @param idx 修改下标   other 提供GListNode元素
//
template<typename T>
void GListNode<T>::modify(int idx, const GListNode<T>& other) {
	if ( isElement() ) {
		throw std::out_of_range("[GListNode]: Element Cannot Use Modify(int, GListNode)!\n");
	}
	else {
		GList<T>* thisList = dynamic_cast<GList<T>*>(this);

		if ( idx < 0 || idx >= thisList -> getSubList().size() ) {
			throw std::out_of_range("[GListNode]: Idx Out Of Range!\n");
		}

		delete thisList -> getSubList()[idx];
		if ( other.isElement() ) {
			thisList -> getSubList()[idx] = new GListElement<T>(dynamic_cast<const GListElement<T>&>(other));
		}
		else {
			thisList -> getSubList()[idx] = new GList<T>(dynamic_cast<const GList<T>&>(other));
		}
	}
}

//
// modify 修改单值
//
// @param idx 修改下标， val修改值
//
template<typename T>
void GListNode<T>::modify(int idx, const T val) {
	if ( isElement() ) {
		throw std::out_of_range("[GListNode]: Element Cannot Use Modify(int, T)!\n");
	}
	else {
		GList<T>* thisList = dynamic_cast<GList<T>*>(this);
	
		if ( idx < 0 || idx >= this -> getSubList().size() ) {
			throw std::out_of_range("[GList]: Idx Out Of Range!\n");
		}

		delete thisList -> getSubList()[idx];
		thisList -> getSubList()[idx] = new GListElement<T>(val);
	}
}

//
// [] 重载 查询第idx个广义表
//
// @param idx 查询下标
//
template<typename T>
GListNode<T>& GListNode<T>::operator[](int idx) {
	if ( !isElement() ) {
		const GList<T>* list = dynamic_cast<const GList<T>*>(this);
		if ( idx < 0 || idx >= list -> getSubList().size() ) {
			throw std::out_of_range("[GListNode]: Idx Out Of Range!\n");
		}

		if ( list -> getSubList()[idx] -> isElement() ) {
			return *dynamic_cast<GListElement<T>*>(list -> getSubList()[idx]);
		}
		else{
			return *dynamic_cast<GList<T>*>(list -> getSubList()[idx]);
		}
	}
	else {
		return *this;
	}
}

//
// [] 重载 查询第idx个广义表 常量
//
// @param idx 查询下标
//
template<typename T>
const GListNode<T>& GListNode<T>::operator[](int idx) const {
	if ( !isElement() ) {
		const GList<T>* list = dynamic_cast<const GList<T>*>(this);
		if ( idx < 0 || idx >= list -> getSubList().size() ) {
			throw std::out_of_range("[GListNode]: Idx Out Of Range!\n");
		}

		if ( list -> getSubList()[idx] -> isElement() ) {
			return *dynamic_cast<GListElement<T>*>(list -> getSubList()[idx]);
		}
		else{
			return *dynamic_cast<GList<T>*>(list -> getSubList()[idx]);
		}
	}
	else {
		return *this;
	}
}


//
// = 重载  模糊赋值
// 
// @param other 提供赋值的变量
//
// 赋值只支持同类型， 比如元素赋值元素， 广义表赋值广义表
//
template<typename T>
GListNode<T>& GListNode<T>::operator=(const GListNode<T>& other) {
	if ( this == &other ) return *this;

	if ( isElement() ) {
		GListElement<T>* thisElem = dynamic_cast<GListElement<T>*>(this);

		if ( !other.isElement() ) {
			throw std::out_of_range("[GListNode]: Cannot Give GList To An Element\n");
		} 
		thisElem -> modify(dynamic_cast<const GListElement<T>&>(other).data());
		
		return *thisElem;
	}
	else {
		GList<T>* thisList = dynamic_cast<GList<T>*>(this);
		
		thisList -> getSubList().clear();
		if ( other.isElement() ) {
			GListElement<T>* tmp = new GListElement<T>(dynamic_cast<const GListElement<T>&>(other));
			thisList -> push_back(*tmp);
		}
		else {
			for (GListNode<T>* x : dynamic_cast<const GList<T>&>(other).getSubList()) {
				thisList -> push_back(*x);
			}
		}
		return *thisList;
	}
}

//
// = 重载  赋值常量
// 
// @param val 提供赋值
//
template<typename T>
GListNode<T>& GListNode<T>::operator=(const T val) {
	if ( isElement() ) {
		GListElement<T>* thisElem = dynamic_cast<GListElement<T>*>(this);
		thisElem -> modify(val);
		
		return *thisElem;
	}
	else {
		GList<T>* thisList = dynamic_cast<GList<T>*>(this);
		GListElement<T>* tmp = new GListElement<T>(val);
		delete thisList;
		thisList -> getSubList().push_back(tmp);

		return *thisList;
	}
}

//
//
//***********************************GListElement******************************************//

//
// isElement 判断是否为元素函数数
//
template<typename T>
bool GListElement<T>::isElement() const {
	return true;
}

//
// modify 修改函数
//
// @param val 修改值
//
template<typename T>
void GListElement<T>::modify(const T val) {
	elem = val;
}

//
// data 获取数据函数 常量
//
template<typename T>
const T GListElement<T>::data() const {
	return elem;
}

//
//
//****************************************GList*******************************************//

//
// 模糊构造函数
// 
// @param node 初始化变量
//
template<typename T>
GList<T>::GList(const GListNode<T>& node) {
	if ( node.isElement() ) {
		const GListElement<T>& element = dynamic_cast<const GListElement<T>&>(node);
		subList.push_back(new GListElement<T>(element));
	}
	else {
		const GList<T>& list = dynamic_cast<const GList<T>&>(node);
		for (const GListNode<T>* x : list.getSubList()) {
			if ( x -> isElement() ) {
				subList.push_back(new GListElement<T>( dynamic_cast<const GListElement<T>&>(*x) ));
			}
			else {
				subList.push_back(new GList<T>(*x));
			}
		}
	}
}

//
// 常量构造函数
//
// @param data 插入常量值
//
template<typename T>
GList<T>::GList(const T val) {
	subList.push_back(new GListElement<T>(val));
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
		GListElement<T>* element = new GListElement<T>(dynamic_cast<GListElement<T>&>(node));
		subList.push_back(element);
	}
	else {
		subList.push_back(new GList<T>(node));
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
// size 获取广义表的大小
//
template<typename T>
const size_t GList<T>::size() const {
	return subList.size();
}

//
// amount 获取元素个数的函数
// 
template<typename T>
size_t GList<T>::amount() {
	size_t tmp = 0;
	return dfs(!subList.empty(), tmp);
}

//
// deepth 获取广义表的深度
//
//!
template<typename T>
size_t GList<T>::deepth() {
	size_t tmp = 0;
	dfs(!subList.empty(), tmp);
	return tmp;
}

//
// getSubList 获取subList函数 常量
//
template<typename T>
const Array<GListNode<T>*>& GList<T>::getSubList() const {
	return subList;
}

//
// getSubList 获取subList函数 常量
//
template<typename T>
Array<GListNode<T>*>& GList<T>::getSubList() {
	return subList;
}

//
// dfs 深度搜索
//
// @param step 步数       deep 记录深度
//
template<typename T>
size_t GList<T>::dfs(size_t step, size_t& deep) {
	size_t amount = 0;
	deep = std::max(deep, step);
	if ( subList.size() <= 1 ) {
		return subList.size();
	}

	for (GListNode<T>* x : subList) {
		if ( x -> isElement() ) {
			amount ++;
		}
		else {
			amount += dynamic_cast<GList<T>*>(x) -> dfs(step + 1, deep);
		}
	}	

	return amount;
}

#endif
