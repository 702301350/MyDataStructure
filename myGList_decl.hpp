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
		virtual bool isElemnt() const = 0;

		// = 重载，赋值常量值
		virtual GListNode& operator=(const T& val) const;

		// = 重载， 赋值对应类型
		virtual GListNode& operator=(const GListNode& other) const;

		// << 重载，输出对应类型
		virtual std::ostream operator<<(std::ostream os, const GListNode& node) const;
};

// GList 元素类
template<typename T>
class GListElemnt : public GListNode {
	private:
		T elem;
	public:
		GListElemnt() {}
		GListElemnt(const T val) { elem = val; }
		~GListElemnt() {}

		bool isElemnt() const override;

		// 获取数据
		const T data() const;

		// = 重载， 赋值常量值
		GListElemnt<T>& operator=(const T val) const override;

		// = 重载，赋值GListElement类型
		GListElemnt<T>& operator=(const GListElemnt<T>& other) const override;

		// << 重载，输出GListElement类型
		std::ostream operator<<(std::ostream os, const GListElemnt<T>& element) const override;
};

// GList 广义表类
template<typename T>
class GList : public GListNode {
	private:
		Array<GListNode<T>*>subList;
	public:
		GList() {}
		GList(const GListNode& node);
		GList(const Array<GListNode<T>*>& array);
		GList(const T& data);
		~GList() { 
			subList.clear();
		}

		bool isElemnt() const override;

		// 获取数据
		Array<GListNode*>& data();

		// 获取深度
		size_t deepth();

		// 获取长度
		size_t size();

		// 删除对应下标的表
		void erase(int idx);

		// 清空广义表
		void clear();

		// = 重载，赋值常量值
		GList& operator=(const T val) const override;

		// = 重载，赋值GlistNode类型
		GList& operator=(const GListNode& node) const override;

		// << 重载，输出广义表
		std::ostream operator<<(std::ostream, const GListNode& node) const override;

		// [] 重载，查询第idx个表
		GListNode& operator[](const int idx);
	private:
		// 获取subList
		Array<GListNode<T>*>& getSubList() const;
};


#endif