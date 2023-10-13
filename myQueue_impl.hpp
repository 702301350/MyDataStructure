#ifndef MYQUEUE_IMPL_HPP_
#define MYQUEUE_IMPL_HPP_

#include "myQueue_decl.hpp"

//
// push 队尾插入元素函数
//
// @param val 插入数据值
//
template<typename T>
void Queue<T>::push(T val) {
	data.push_back(val);
}

//
// pop 弹出队首元素
//
template<typename T>
void Queue<T>::pop() {
	if ( empty() ) {
		throw std::out_of_range("[Queue]: Try To Pop From An Empty Queue!\n");
	}
	data.erase(data.begin());
}

//
// size 返回队列大小
//
template<typename T>
size_t Queue<T>::size(){ 
	return data.size();
}

//
// front 获取队首元素
//
template<typename T>
const T& Queue<T>::front() {
	if ( empty() ) {
		throw std::out_of_range("[Queue]: Try To Elemnt From An Empty Queue\n!");
	}
	return *data.begin();
}

//
// clear 清除队列
//
template<typename T>
void Queue<T>::clear() {
	data.clear();
}

//
// empty 获取队列是否为空状态
//
template<typename T>
bool Queue<T>::empty() {
	return data.empty();
}

//
// = 重载, 赋值
//
// @param other 提供赋值的变量
//
template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	data = other.data;
	return *this;
}

//
// = 重载, 赋值 常量
//
// @param other 提供赋值的变量
//
template<typename T>
const Queue<T>& Queue<T>::operator=(const Queue<T>& other) const {
	data = other.data;
	return *this;
}

#endif