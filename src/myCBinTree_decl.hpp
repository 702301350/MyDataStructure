#ifndef MYCBINTREE_DECL_HPP_
#define MYCBINTREE_DECL_HPP_

#include "myDef.hpp"
#include "myString.hpp"
#include "myArray.hpp"
#include "myQueue.hpp"

#include <unordered_set>
#include <unordered_map>

/*

CBinTree 普通二叉树，

使用时需要先初始化根结点, 根结点编号默认 root
插入方式采用插入在已知结点的左右边，使用一个
set进行编码映射，可以针对已知编号的结点进行修
改，删除子树等

*/

template<typename T>
class CBinTree {
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
		Node* left, * right;

		Node(const T val, const String _id) {
			id = _id;
			data = val;
			left = nullptr;
			right = nullptr;
		}
		~Node() {}
	};

	private:
		std::unordered_set<String>hashMap;   //储存编号，防止重复

	public:
		Node* root;

		CBinTree(Array<T>& seq1, int mode1, Array<T>& seq2, int mode2);
		CBinTree() {
			root = nullptr;
		}
		~CBinTree() {
			clear();
		}

		// 清空二叉树
		void clear();

		// 是否为空
		bool empty() const;

		// 初始化根节点
		void initRoot(const T val);

		// 插入元素
		void insert(const String _pa, int side, const T val, const String _id);

		// 遍历 二叉树
		Array<T> traverse(int mode);

		// 查找是否存在
		bool has(const T val) const;

		// 删除对应编号结点及以下的子树
		void delSubTree(const String _id);

		// 通过id修改值
		void modify(const String _id, const T val);

		// 通过id获取数据
		T get(const String _id) const;

		// 判断是否为满二叉树
		bool isFull() const;

		// 判断是否为完全二叉树
		bool isComplete() const;

		// 获取层数
		const size_t deepth() const;

		// 获取大小
		const size_t size() const;

	private:
		// 查询元素
		Node* find(const String _id) const;

		// 通过先序和中序构建树
		Node* treeBuilder(Array<T>& pre, size_t pre_st, size_t pre_ed, Array<T>& mid, size_t mid_st, size_t mid_ed, std::unordered_map<T, size_t>& mid_hash);

		// 通过中序和后序构建树
		Node* treeBuilder(Array<T>& mid, size_t mid_st, size_t mid_ed, Array<T>& aft, long& aft_ed, std::unordered_map<T, size_t>& mid_hash);

		//先序遍历
		void pre_traverse(Node* node, Array<T>& arr);

		//中序遍历
		void mid_traverse(Node* node, Array<T>& arr);

		// 后序遍历
		void aft_traverse(Node* node, Array<T>& arr);
};

#endif