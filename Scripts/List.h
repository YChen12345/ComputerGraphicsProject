#pragma once
#include <iostream>

template<typename T>
class Node {
public:
	T data;
	std::shared_ptr<Node> next;

public:
	Node(Node& node):data(node.data),next(node.next){}
	Node(T item):data(item),next(nullptr){}
	Node(T item, std::shared_ptr<Node> node) :data(item), next(node) {}
};

template<typename T>
class List {
public:
	std::shared_ptr<Node<T>> firstNode;
	int length;

public:
	List() {
		firstNode = nullptr;
		length = 0;
	}
	List(List<T>& list) : length(list.length) {
		firstNode = list.firstNode;
	}

	void Add(T item) {
		auto node = std::make_shared<Node<T>>(item, firstNode);
		firstNode = node;
		length++;
	}

	bool Remove(T item) {
		if (length > 0) {
			Node<T>* nd = firstNode.get();
			if (nd->data == item) {
				firstNode = nd->next;
				length--;
				return true;
			}
			else
			{
				while (nd->next!=nullptr)
				{
					Node<T>* next = (nd->next).get();
					if (next->data == item) {
						nd->next = next->next;
						length--;
						return true;
					}
					nd = (nd->next).get();
				}
			}
		}
		return false;
	}
	void RemoveAll(T item) {
		while (Remove(item));
	}
	bool RemoveAt(unsigned int index) {
		if (length > 0) {
			Node<T>* nd = firstNode.get();
			if (index < length) {
				if (index == 0) {
					firstNode = (nd->next);
					length--;
					return true;
				}
				else
				{
					for (unsigned int i = 1; i < length; i++) {
						if (i == index) {
							Node<T>* next = (nd->next).get();
							nd->next = (next->next);
							length--;
							return true;
						}
						nd = (nd->next).get();
					}
				}
			}
		}
		return false;
	}

	T& operator[] (unsigned int index) {
		Node<T>* nd = firstNode.get();
		if (index < length) {
			for (int i = 0; i < index; i++) {
				nd = (nd->next).get();
			}
		}
		return (nd->data);
	}
	void Clear() {
		firstNode = nullptr;
		length = 0;
	}
};