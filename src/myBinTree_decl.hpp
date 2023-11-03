#ifndef MYBINTREE_DECL_HPP_
#define MYBINTREE_DECL_HPP_

#include "myDef.hpp"
#include "myString.hpp"
#include "myArray.hpp"
#include "myQueue.hpp"

template<typename T>
class BinTree {
	//遍历顺序
	#define PRECO   0
	#define MIDO    1
	#define AFTERO  2

	// 左右边
	#define LEFT    0
	#define RIGHT   1

	//结点
	struct Node {
		String number;
		T elem;
		Node *left, *right, *pre;

		Node(const T val) {
			number = -1;
			elem = val;
			left  = nullptr;
			right = nullptr;
			pre   = nullptr;
		}
		~Node() {}

		// 设置左结点
		void setLeft(Node* l) {
			left = l;
		}

		// 设置右结点
		void setRight(Node* r) {
			right = r;
		}
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
		bool empty() const;

		// 遍历，返回遍历数组
		Array<T> traverse(int mode);

		// 插入在根结点的左，右边
		void insertFront(const T val, int side);

		// 插入在对应编号的左，右边
		void insert(const T val, const String num, int side);

		// 删除对应编号的结点
		void erase(const String num);

		// 二叉树嫁接
		void merge(Node* node, int side);

		// 找到父结点
		Node* findParent(Node* node);

		// 查找
		bool find(const T val) const;

		// 判断两个节点是否是同一颗树
		bool isFamily(Node& a, Node& b) const;

		// 判断是否为满二叉树
		bool isFull() const;

		// 判断是否为完全二叉树
		bool isComplete() const;

		// 获取层数
		size_t deepth();

		// 获取大小
		size_t size();

	private:
		
		//先序遍历
		void pre_traverse(Node* node, Array<T>& arr);

		//中序遍历
		void mid_traverse(Node* node, Array<T>& arr);
		
		// 后序遍历
		void aft_traverse(Node* node, Array<T>& arr);
};

#endif