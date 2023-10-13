#ifndef MYLIST_DECL_HPP_
#define MYLIST_DECL_HPP_

#include "myDef.hpp"

template<typename T>
class List {
	//节点数据
	struct Node {
		Node* next;
		Node* pre;
		T data;

		Node() {
			next = nullptr;
			pre = nullptr;
		}
	};

	private:
		Node* head;
		Node* tail;
		size_t size;

	public:
		List() {
			head = nullptr;
			tail = nullptr;
			size = 0;
		}
		~List() {
			clear();
		}

		// 默认尾部插入
		void insert(T val);

		// 指定位置插入
		void insert(T val, int idx);

		// 查询
		T& operator[](int idx);

 		// 查询 常量
 		const T& operator[](int idx) const;

		// 删除
		void erase(int idx);

		// 清空数组
		void clear();

		// 输出链表大小
		const int length();

	private:
		// 查找对应的node
		Node* find(int idx);
};

#endif
