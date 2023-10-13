#ifndef MYARRAY_DECL_HPP_
#define MYARRAY_DECL_HPP_

#include "myDef.hpp"

template<typename T>
class Array {
	private:
		T* data;
		size_t length;

	public:
		using iterator = T*;
		using const_iterator = const T*;

		Array();
		Array(size_t len);
		Array(size_t len, T val);
		Array(const Array& other);
		Array(std::initializer_list<T> val);
		~Array() {
			clear();
		}

		// 删除下标为idx的元素
		void erase(int idx);

		// 按照迭代器删除
		void erase(iterator it);

		// [] 重载, 返回下标为idx的元素
		T& operator[](int idx);

		// [] 重载，返回下标为idx的元素常量
		const T& operator[](int idx) const;

		// = 重载, 赋值
		Array<T>& operator=(const Array<T>& other);

		// 返回最后一个元素值
		T& back();

		// 插入元素到尾部
		void push_back(T val);

		// 插入元素到下标为idx的位置
		void insert(T val, int idx);

		// 获取数组大小
		const size_t size() const;

		// 返回数组是否为空
		bool empty();

		// 清空数组
		void clear();

		// 头部迭代器
		iterator begin();

		// 尾部迭代器
		iterator end();

		// 头部常量迭代器
		const_iterator begin() const;

		// 尾部常量迭代器
		const_iterator end() const;

	private:
		// 获取data
		T* getData();
};

#endif
