#ifndef MYSKIPLIST_IMPL_HPP_
#define MYSKIPLIST_IMPL_HPP_

#include "mySkipList_decl.hpp"

#include <cmath>

//
// insert 插入元素函数
//
// @param val 插入元素
//
template<typename T>
void SkipList<T>::insert(const T val) {
	size_t cur = getRandom();

	for (auto &x : data) {
		List<T>* ptr = &x;
		int i;
		for (i = 0;i < ptr -> length();i ++) {
			if ( *ptr[i] > val ) {
				break;
			}
		}
		ptr -> insert(val, i + 1);
	}
}

//
// erase 删除元素函数
//
// @param idx 删除元素下标
//
template<typename T>
void SkipList<T>::erase(size_t idx) {
}

//
// count 查询是否存在函数
//
template<typename T>
bool SkipList<T>::count() {

}

//
// = 重载, 赋值
//
// @param other 其他的SkipList类型元素
//
template<typename T>
SkipList<T>& SkipList<T>::operator=(const SkipList<T>& other) {

}

//
// getRandom 获取随机层数函数
//
template<typename T>
size_t SkipList<T>::getRandom() {
	size_t maxLimit = (data.size()) ? data[0].size() : 0;
	size_t idx = 1;
	while ( (size_t)rand() & 0xFFFF < maxLimit & 0xFFFF ) {
		idx ++;
	}
	return idx;
}

#endif