#ifndef MYSTACK_IMPL_HPP_
#define MYSTACK_IMPL_HPP_

#include "myStack_decl.hpp"

//
// pop 弹出栈顶元素函数
// 
template<typename T>
void Stack<T>::pop() {
	if ( empty() ) {
		throw std::out_of_range("[Stack]: Try To Pop When It Is Empty!\n");
	}
	else {
		data.erase(data.size() - 1);
	}
}

//
// top 获取栈顶元素函数
//
template<typename T>
const T& Stack<T>::top() {
	return data.back();
}

//
// push 入栈函数
//
// @param val 入栈的值
//
template<typename T>
void Stack<T>::push(T val) {
	data.push_back(val);
}

//
// size 返回栈大小函数
//
template<typename T>
size_t Stack<T>::size() {
	return data.size();
}

//
// clear 清空栈函数
//
template<typename T>
void Stack<T>::clear() {
	data.clear();
}

//
// empty 判断是否空函数
//
template<typename T>
bool Stack<T>::empty() {
	return data.empty();
}

//
// = 重载
//
// @param other 提供赋值的栈
//
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
	data = other.data;
	return *this;
}

//
// = 重载
//
// @param other 提供赋值的栈 常量
//
template<typename T>
const Stack<T>& Stack<T>::operator=(const Stack<T>& other) const {
	data = other.data;
	return *this;
}

#endif