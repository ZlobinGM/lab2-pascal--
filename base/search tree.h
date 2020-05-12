#ifndef __SEARCH_TREE_H__
#define __SEARCH_TREE_H__

#include <string>

using namespace std;

template <class T>
class NodeTree
{
	NodeTree<T>* parent;
	NodeTree<T>* leftChild;
	NodeTree<T>* rightChild;
public:
	string name;
	T data;

	int heightDiff;		//left heght-right height
	bool isLeftChild;

	NodeTree();
	NodeTree(string _name, T _data);
	
	void SetChild(NodeTree<T>* child, bool left);
	NodeTree<T>* GetChild(bool left);
	NodeTree<T>* GetParent();
	void Rotate(bool leftChild);
};

template <class T>
class SearchTree
{
protected:
	NodeTree<T>* head;
	int height;
	int DataCount;

	bool Balance(NodeTree<T>* _node);
	void Clear(NodeTree<T>* start);
	NodeTree<T>* FindNode(string name);
private:
	const bool firstRecordLeft = true;
public:
	SearchTree();
	~SearchTree();

	T* Find(string name);
	void Insert(string _name, T& _data);

	int GetHeight();
};

#endif