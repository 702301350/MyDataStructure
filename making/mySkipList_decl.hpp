#ifndef MYSKIPLIST_DECL_HPP_
#define MYSKIPLIST_DECL_HPP_

#include "myDef.hpp"
#include "myList.hpp"

template<typename T>
class SkipList {
	// 元素节点
	struct Node {
		T elem;
		double score;
		Node *next, *down, *pre;

		Node(const T val, const double s) 
		: elem(val), score(s), next(nullptr), down(nullptr), pre(nullptr) {}
		
		Node(const Node& other) {
			elem = other.elem;
			next = other.next;
			down = other.down;
			pre = other.pre;
		}
		~Node() {}
	};
	private:
		List<Node*> layer;

	public:
		SkipList(const size_t level);
		~SkipList() {}

		// 插入元素
		void insert(const T val);

		// 清空跳表
		void clear();

		// 删除元素
		void erase(const T val);

		// 查询元素在跳表中是否存在
		bool count(const T val);

		// 生成score
		double scoreGen(const T val, auto func);

	private:
		//获取随机层数
		size_t getRandom(const double s) const;

};

#endif