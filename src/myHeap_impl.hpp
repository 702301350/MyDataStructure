#ifndef MYHEAP_IMPL_HPP_
#define MYHEAP_IMPL_HPP_

#include "myHeap_decl.hpp"

#include <algorithm>

//
// empty 判断是否为空函数
//
template<typename T, typename C>
bool Heap<T, C>::empty() const {
	return data.empty();
}

//
// size 获取堆大小函数
//
template<typename T, typename C>
size_t Heap<T, C>::size() const {
	return data.size();
}

// 
// insert 插入函数
// 
// @param val 插入元素
//
template<typename T, typename C>
void Heap<T, C>::insert(T val) {
	data.push_back(val);
	up();
}

//
// extract 返回堆顶函数
//
template<typename T, typename C>
T Heap<T, C>::top() const {
	if ( empty() ) {
		throw std::out_of_range("[Heap]: The Heap Is Empty!");
		return T();
	}

	return data[0];
}

//
// pop 弹出堆顶部元素
//
template<typename T, typename C>
void Heap<T, C>::pop() {
	if ( empty() ) return;

	data[0] = data.back();
	data.pop_back();
	down();
}

//
// up 上浮
//
template<typename T, typename C>
void Heap<T, C>::up() {
	size_t idx = size() - 1;

	while ( idx ) {
		int par = (idx - 1) / 2;

		if ( idx > 0 && cmp(data[idx], data[par]) ) {
			std::swap(data[idx], data[par]);
			idx = par;
		}
		else {
			break;
		}
	}
}

//
// down 下沉
//
template<typename T, typename C>
void Heap<T, C>::down() {
	size_t idx = 0, _size = size();

	while ( 1 ) {
		size_t l = 2 * idx + 1;
		size_t r = 2 * idx + 2;
		size_t _top = idx;

		if ( l < _size && cmp(data[l], data[_top]) ) {
			_top = l;
		}
		if ( r < _size && cmp(data[r], data[_top]) ) {
			_top = r;
		}
		if ( _top != idx ) {
			std::swap(data[idx], data[_top]);
			idx = _top;
		}
		else {
			break;
		}
	}
}

#endif