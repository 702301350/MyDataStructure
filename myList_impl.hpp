#ifndef MYLIST_IMPL_HPP_
#define MYLIST_IMPL_HPP_

#include "myList_decl.hpp"
#include <iostream>

//
// insert 插入函数(默认尾部)
//
// @param val 插入数据值
//
template<typename T>
void List<T>::insert(T val) {
	Node* node = new Node(val);
	
	if ( tail == nullptr ) {
		head = tail = node;
		head -> next = tail;
		tail -> pre = head;
	}
	else {
		tail -> next = node;
		node -> pre = tail;
		tail = node;
	}
	head -> pre = tail;
	tail -> next = head;
	size ++;
}

//
// insert 插入函数
//
// @param val 插入数据值   idx 插入位置
//
template<typename T>
void List<T>::insert(T val, int idx) {
	if ( idx < 0 || idx > size ) {
		std::cout << "Index Out Of Range!\n";
		return;
	}

	if ( idx == size ) {
		insert(val);
		return;
	}
	Node* ptr = find(idx);
	Node* node = new Node();

	node -> data = val;
	if ( ptr == nullptr ) {
		head = tail = node;
		head -> next = tail;
		head -> pre = tail;
		tail -> next = head;
		tail -> pre = head;
	}
	else {
		Node* front = ptr -> pre;

		front -> next = node;
		ptr -> pre = node;
		node -> next = ptr;
		node -> pre = front;

		if ( front == tail ) head = node;
	}
	size ++;
}

//
// [] 重载
//
// @oaram idx 查找下标
//
template<typename T>
T& List<T>::operator[](int idx) {
	return find(idx) -> data;
}

//
// [] 重载
//
// @oaram idx 查找下标 常量
//
template<typename T>
const T& List<T>::operator[](int idx) const {
	return find(idx) -> data;
}

//
// = 重载
//
// @param other 提供赋值的链表
//
template<typename T>
List<T>& List<T>::operator=(const List<T>& other) {
	if ( this != &other ) {
		clear();
		size_t len = other.length();
		for (int i = 0;i < len;i ++) {
			insert(other[i]);
		}
	}
	return *this;
}

//
// erase 删除函数
//
// @param idx 删除下标
//
template<typename T>
void List<T>::erase(int idx) {
	idx = idx % size;
	
	Node* it = find(idx);

	if ( it == head ) {
		Node* tmp = head -> next;
		tail -> next = tmp;
		tmp -> pre = tail;
		head = tmp;
		delete it;
	}
	else if ( it == tail ) {
		Node* tmp = tail -> pre;
		tmp -> next = head;
		head -> pre = tmp;
		tail = tmp;
		delete it;
	}
	else {
		Node* back  = it -> next;
		Node* front = it -> pre;

		back -> pre = front;
		front -> next = back;
		delete it;
	}
	size --;
}

//
// size 获取大小函数
// 
template<typename T>
const int List<T>::length() const {
	return size;
}

//
// clear 清空链表函数
//
template<typename T>
void List<T>::clear() {
	if ( head != nullptr ) {
		for (Node* it = head;it != tail;) {
			Node* tmp = it;
			it = it -> next;
			delete tmp;
		}
		delete tail;
	}

	head = nullptr;
	tail = nullptr;
	size = 0;
}

//
// find 查找node元素节点
//
// @param idx 查找下标
//
// 对于超范围的数据(idx >= size 或者 idx < 0 ) 统一按循环模式左右查找
//
template<typename T>
typename List<T>::Node* List<T>::find(int idx) const {
	Node* it = head;
	idx = idx % size;
	if ( idx >= 0 ) {
		while ( idx > 0 ) {
			it = it -> next;
			idx --;
		} 
	}
	else {
		while ( idx < 0 ) {
			it = it -> pre;
			idx ++;
		}
	}
	return it;
}

#endif