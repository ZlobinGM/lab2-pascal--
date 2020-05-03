#include "search tree.h"

template<class T>
Node<T>* SearchTree<T>::FindRecord(string name)
{
	return nullptr;
}

template<class T>
bool SearchTree<T>::Balance(Node<T>* record)
{
	return false;
}

template<class T>
SearchTree<T>::SearchTree()
{
}

template<class T>
SearchTree<T>::~SearchTree()
{
}

template<class T>
void SearchTree<T>::Insert(string _name, T& _data)
{
}

template<class T>
inline int SearchTree<T>::GetHeight()
{
	return 0;
}

template<class T>
inline Node<T>::Node(string _name, T _data)
{
}
template<class T>
void Node<T>::SetChild(Node<T>* child, bool left)
{
}
template<class T>
inline Node<T>* Node<T>::GetChild(bool left)
{
	return NULL;
}
template<class T>
inline Node<T>* Node<T>::GetParent()
{
	return NULL;
}
template<class T>
void Node<T>::Rotate(bool leftChild)
{
}