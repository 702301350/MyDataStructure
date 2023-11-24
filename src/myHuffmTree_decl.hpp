#ifndef MYHUFFMTREE_DECL_HPP_
#define MYHUFFMTREE_DECL_HPP_

#include "myHeap.hpp"
#include "myString.hpp"

#include <unordered_map>

template<typename T>
class HuffmTree {
	struct Node {
		T data;
		size_t frq;
		bool flag;
		Node* left;
		Node* right;

		Node(T val, size_t f) : data(val), frq(f), left(nullptr), right(nullptr), flag(false) {}
		~Node() {}
	};
	struct Comp_Node {
		bool operator()(const Node* lhs, const Node* rhs) const {
			return lhs -> frq < rhs -> frq;
		}
	};

	private:	
		Heap<Node*, Comp_Node> heap;                // 堆
		std::unordered_map<T, size_t>huffFrqc;      // 频率表
		std::unordered_map<T, String>huffCode;      // 哈夫曼编码集合

	public:
		HuffmTree(Array<T> data);
		HuffmTree(std::unordered_map<T, size_t> frqc);
		~HuffmTree() {
			while ( !heap.empty() ) {
				heap.pop();
			}
		}

		// 解析哈夫曼编码
		Array<T> explain(String code);

		// 导出哈夫曼编码
		String   exportHuff(Array<T> data);
	
		// 导出哈夫曼编码表
		std::unordered_map<T, String> exportTable() const;	
	private:
		// 生成哈夫曼编码
		void generateCode(Node* root, String Code);

		// 生成哈夫曼树
		void buildHuffmTree();
};

#endif