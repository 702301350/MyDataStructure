#ifndef MYGLIST_DECL_HPP_
#define MYGLIST_DECL_HPP_

#include "myDef.hpp"
#include "myArray.hpp"

#include <iostream>

// GList 基类
template<typename T>
class GListNode {
	public:
		// 判断是否为元素
		virtual bool isElement() const = 0;

		// 修改元素
		void modify(int idx, const GListNode<T>& other);

		// 修改元素
		void modify(int idx, const T val);

		// [] 重载，查询
		GListNode<T>& operator[](int idx);

		// [] 重载 查询 常量
		const GListNode<T>& operator[](int idx) const;

		// = 重载 常熟赋值
		GListNode<T>& operator=(const T val);

		// = 赋值GListNode类型
		GListNode<T>& operator=(const GListNode<T>& other);
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
		~GListElement() { elem = 0; }

		bool isElement() const override;

		//修改元素 
		void modify(const T val);

		// 获取数据 常量
		const T data() const;
};

// GList 广义表类
template<typename T>
class GList : public GListNode<T> {
	private:
		Array<GListNode<T>*>subList;
	public:
		GList() {}
		GList(const GListNode<T>& node);
		GList(const T val);
		GList(std::initializer_list<GList<T>> val);
		~GList() { 
			clear();
		}

		bool isElement() const override;

		// 清除
		void clear();

		// 获取深度
		size_t deepth();

		// 获取个数
		size_t amount();

		// 获取长度
		const size_t size() const;

		// 模糊类型插入
		void push_back(GListNode<T>& node);

		// 常量值插入
		void push_back(const T val);

		// 删除对应下标的表
		void erase(int idx);

		// 获取表中第一个元素
		const GListNode<T>& front() const;

		// 获取subList
		Array<GListNode<T>*>& getSubList();

		// 获取subList 常量
		const Array<GListNode<T>*>& getSubList() const;
	private:

		// DFS
		size_t dfs(size_t step, size_t& deep);
};



#endif