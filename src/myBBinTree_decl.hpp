#ifndef MYBBINTREE_DECL_HPP_
#define MYBBINTREE_DECL_HPP_

#include "myDef.hpp"
#include "myString.hpp"
#include "myArray.hpp"
#include "myQueue.hpp"

/*

BBinTree 规则二叉树，

初始化时传入一个函数指针，则二叉树在插入时会
按照该函数指针的规则进行插入，例如：

BBinTree<int> tree( greater<int>{} );
或者
BBinTree<int> tree( cmp );

*/

template<typename T>
class BBinTree {
	//遍历顺序
	#define PRECO   0
	#define MIDO    1
	#define AFTERO  2

	// 左右边
	#define LEFT    0
	#define RIGHT   1

	//结点
	struct Node {
		T data;
		Node *left, *right;

		Node(const T val) {
			data = val;
			left = nullptr;
			right = nullptr;
		}
		~Node() {}
	};

	private:
		std::function<bool(T, T)> compare;   //储存规则
	
	public:
		Node* root;                         //根节点

		BBinTree(std::function<bool(T, T)> cmp) {
			root = nullptr;
			compare = cmp;
		}
		~BBinTree() {
			clear();
		}

		// 清空规则二叉树
		void clear();

		// 判断是否为空
		bool empty() const;

		// 遍历，返回遍历数组
		Array<T> traverse(int mode);

		// 按照规则插入
		void insert(const T val);

		// 查找是否存在
		bool has(const T val) const;

		// 删除k次指定值
		void erase(const T val, const size_t k);

		// 规则二叉树合并
		void merge(BBinTree& tree);

		// 判断是否为满二叉树
		bool isFull() const;

		// 判断是否为完全二叉树
		bool isComplete() const;

		// 获取层数
		const size_t deepth() const;

		// 获取大小
		const size_t size() const;

	private:
		//先序遍历
		void pre_traverse(Node* node, Array<T>& arr);

		//中序遍历
		void mid_traverse(Node* node, Array<T>& arr);

		// 后序遍历
		void aft_traverse(Node* node, Array<T>& arr);
};

#endif