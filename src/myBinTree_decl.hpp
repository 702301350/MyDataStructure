#ifndef MYBINTREE_DECL_HPP_
#define MYBINTREE_DECL_HPP_

#include "myDef.hpp"

template<typename T>
class BinTree {
	struct Node {
		T data;
		Node *left, *right, *pre;

		Node() {
			left  = nullptr;
			right = nullptr;
			pre   = nullptr;
		}
		~Node() {}
	};

	private:
		Node*  head;
		size_t length;
		size_t id;

	public:
		BinTree() {
			head = nullptr;
		}
		~BinTree() {
			clear();
		}

		// 清空二叉树
		void clear();

		// 判断是否为空
		bool empty();

		// 打印
		void print();

		// 二叉树嫁接
		void merge(Node& node, int side);

		// 查找
		bool find(T val);

		// 判断两个节点是否是同一颗树
		bool isFamily(Node& a, Node& b);

		// 获取层数
		size_t deepth();

		// 获取大小
		size_t size();
};

#endif