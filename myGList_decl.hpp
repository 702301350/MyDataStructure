#ifndef MYGLIST_DECL_HPP_
#define MYGLIST_DECL_HPP_

#include "myDef.hpp"
#include "myArray.hpp"
#include "myQueue.hpp"

#include <iostream>

// GList 基类
template<typename T>
class GListNode {
	public:
		// 判断是否为元素
		virtual bool isElement() const = 0;
};

// GList 元素类
template<typename T>
class GListElement : public GListNode<T> {
	private:
		T elem;
	public:
		GListElement() {}
		GListElement(const T val)  { elem = val; }
		GListElement(const GListElement<T>& other) { elem = other.data(); }
		~GListElement() {}

		bool isElement() const override;

		// 获取数据
		const T data() const;

		// = 重载， 赋值常量值
		GListElement<T>& operator=(const T val);

		// = 重载，赋值GListElement类型
		GListElement<T>& operator=(const GListElement<T>& other);
};

// GList 广义表类
template<typename T>
class GList : public GListNode<T> {
	private:
		Array<GListNode<T>*>subList;
	public:
		GList() {}
		GList(const GListNode<T>& node);
		GList(const Array<GListNode<T>*>& array);
		GList(const Array<T>& array);
		GList(std::initializer_list<GList<T>> val);
		GList(const T val);
		~GList() { 
			subList.clear();
		}

		bool isElement() const override;

		// 获取深度
		size_t deepth();

		// 获取长度
		const size_t size() const;

		// 模糊类型插入
		void push_back(GListNode<T>& node);

		// 插入数组
		void push_back(const Array<T>& array);

		// 常量值插入
		void push_back(const T val);

		// 删除对应下标的表
		void erase(int idx);

		// 清空广义表
		void clear();

		// 获取表中第一个元素
		const GListNode<T>& front() const;

		// 获取特定层数的所有广义表
		GList<T> at(int layer);

		// = 重载，赋值常量值
		GList& operator=(const T val);

		// = 重载，赋值GlistNode类型
		GList& operator=(const GListNode<T>& node);

		//[] 重载，查询第idx个表
		GListNode<T>& operator[](int idx);

		// [] 重载，查询第idx个表 常量
		const GListNode<T>& operator[](int idx) const;
	private:
		// 获取subList
		const Array<GListNode<T>*>& getSubList() const;

		// DFS
		size_t bfs(GList<T>* list, int layer);
};



#endif