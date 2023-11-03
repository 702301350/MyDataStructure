#ifndef MYBINTREE_DECL_HPP_
#define MYBINTREE_DECL_HPP_

#include "myDef.hpp"
#include "myString.hpp"
#include "myArray.hpp"
#include "myQueue.hpp"

#include <unordered_set>

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
		String id;
		T data;
		Node *left, *right, *pre;

		Node(const T val, const String _id) {
			id = _id;
			data = val;
			left  = nullptr;
			right = nullptr;
			pre   = nullptr;
		}
		~Node() {}
	};

	private:
		std::function<bool(T, T)> compare;   //储存规则
		std::unordered_set<String>hashMap;   //储存编号，防止重复
	public:
		Node*  root;                         //根节点

		BinTree(std::function<bool(T, T)> cmp) {
			root = nullptr;
			compare = cmp;
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

		// 按照规则插入
		void insert(const T val, const String _id);

		// 查找是否存在
		bool has(const T val) const;

		// 通过id获取数据
		T& get(const String _id) const;

		// 删除对应编号的结点
		void erase(const String _id);

		// 删除对应编号结点及以下的子树
		void delSubTree(const String _id);

		// 二叉树合并
		void merge(BinTree* tree);

		// 判断是否为满二叉树
		bool isFull() const;

		// 判断是否为完全二叉树
		bool isComplete() const;

		// 获取层数
		const size_t deepth() const;

		// 获取大小
		const size_t size() const;

	private:
		// 通过id查找
		Node* find(const String _id) const;

		//先序遍历
		void pre_traverse(Node* node, Array<T>& arr);

		//中序遍历
		void mid_traverse(Node* node, Array<T>& arr);
		
		// 后序遍历
		void aft_traverse(Node* node, Array<T>& arr);
};

#endif