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

		// ɾ���±�Ϊidx��Ԫ��
		void erase(int idx);

		// ���յ�����ɾ��
		void erase(iterator it);

		// [] ����, �����±�Ϊidx��Ԫ��
		T& operator[](int idx);

		// [] ���أ������±�Ϊidx��Ԫ�س���
		const T& operator[](int idx) const;

		// = ����, ��ֵ
		Array<T>& operator=(const Array<T>& other);

		// �������һ��Ԫ��ֵ
		T& back();

		// ����Ԫ�ص�β��
		void push_back(T val);

		// ����Ԫ�ص��±�Ϊidx��λ��
		void insert(T val, int idx);

		// ��ȡ�����С
		const size_t size() const;

		// ���������Ƿ�Ϊ��
		bool empty();

		// �������
		void clear();

		// ͷ��������
		iterator begin();

		// β��������
		iterator end();

		// ͷ������������
		const_iterator begin() const;

		// β������������
		const_iterator end() const;

	private:
		// ��ȡdata
		T* getData();
};

#endif
