#ifndef __SEARCH_TREE_H__
#define __SEARCH_TREE_H__

#include <string>

using namespace std;

template <class T>
class Node
{
private:
	string name;
	T data;
	Node<T>* parent;
	Node<T>* leftChild;
	Node<T>* rightChild;
public:
	int heightDiff;		//left heght-right height
	bool isLeftChild;

	Node();
	Node(string _name, T _data);

	void SetChild(Node<T>* child, bool left);
	Node<T>* GetChild(bool left);
	Node<T>* GetParent();
	void Rotate(bool leftChild);
};

template <class T>
class SearchTree
{
protected:
	Node<T>* head;
	int height;
	int DataCount;//количетсво записей

	Node<T>* FindRecord(string name);
	bool Balance(Node<T>* record);

	Node<T>* minRecord;
private:
	const bool firstRecordLeft = true;
public:
	SearchTree();
	~SearchTree();

	void Insert(string _name, T& _data);

	int GetHeight();
};

#endif