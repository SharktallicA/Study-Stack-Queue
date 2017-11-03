#include <iostream>

using namespace std;

template <typename T>
class Node
{
	//purpose: a Node for containing data and information on its place within a Node chain

public:
	T tValue; //value of the Node
	Node* ptrNext = nullptr; //pointer to the next Node in the Node chain
	Node* ptrPrevious = nullptr; //pointer to the previous Node in the Node chain
};

template <typename T>
class Stack
{
	//purpose: Stack memory structure

public:
	~Stack(void);
	void push(T);
	Node<T>* nodePop(void);
	T pop(void);
protected:
	Node<T>* ptrTop = nullptr; //pointer to the top Node in the Node chain
};

template <typename T>
class Queue : protected Stack<T>
{
	//purpose: Queue memory structure

private:
	Node<T>* ptrFront; //pointer to the front Node in the Node chain
public:
	Queue(void);
	~Queue(void);
	virtual void enqueue(T);
	virtual Node<T>* nodeDequeue(void);
	virtual T dequeue(void);
};

template <typename T>
Stack<T>::~Stack()
{
	//usage: destructor of the Stack
	while (ptrTop != nullptr) { delete nodePop(); } //whilst there are Nodes left, pop all Nodes
}
template <typename T>
void Stack<T>::push(T tValue)
{
	//usage: creates new Node and adds it to the top of the Node chain
	//parametres: (tValue) templated value for the Node

	Node<T>* ptrTemp = new Node<T>; 
	ptrTemp->tValue = tValue; //asigns Node its value
	ptrTemp->ptrNext = ptrTop; //tells Node that currently the next Node is the top (itself)
	ptrTop = ptrTemp; //assigns the new Node as the top Node
}
template <typename T>
Node<T>* Stack<T>::nodePop()
{
	//usage: removes the current top Node from the chain for deletion

	Node<T>* ptrTemp = ptrTop;
	if (ptrTop != nullptr) ptrTop = ptrTop->ptrNext; //assigns the next Node in the chain as the top Node
	return ptrTemp;
}
template <typename T>
T Stack<T>::pop()
{
	//usage: deletes the current top Node and return its value

	Node<T>* ptrTemp = nodePop();
	int intReturn = 0;

	if (ptrTemp != nullptr)
		intReturn = ptrTemp->tValue;
	else
		throw "Stack empty!\n";

	delete ptrTemp;
	return intReturn;
}

template <typename T>
Queue<T>::Queue(void)
{
	//usage: constructor of the Queue
	ptrFront = ptrTop = nullptr; 
}
template <typename T>
Queue<T>::~Queue()
{
	//usage: destructor of the Queue
	while (ptrTop != nullptr) { delete nodeDequeue(); } //whilst there are Nodes left, dequeue all Nodes
}
template <typename T>
void Queue<T>::enqueue(T tValue)
{
	//usage: creates new Node and adds it to the top of the Node chain
	//parametres: (tValue) templated value for the Node

	this->push(tValue); //uses Stack class's push method for Node creation
	if (ptrFront == nullptr) ptrFront = ptrTop;
	else (ptrTop->ptrNext)->ptrPrevious = ptrTop;
}
template <typename T>
Node<T>* Queue<T>::nodeDequeue()
{
	//usage: removes the current bottom Node from the chain for deletion

	Node<T>* ptrTemp = ptrFront;
	if (ptrFront != nullptr)
	{
		ptrFront = ptrFront->ptrPrevious; //assigns the previous Node in the chain as the front Node
		if (ptrFront != nullptr) ptrFront->ptrNext = nullptr;
	}
	return ptrTemp;
}
template <typename T>
T Queue<T>::dequeue()
{
	//usage: deletes the current front Node and returns its value

	Node<T>* ptrTemp = nodeDequeue();
	T tReturn = 0;
	
	if (ptrTemp != nullptr)
		tReturn = ptrTemp->tValue;
	else
		throw "Queue empty!\n";
	if (ptrFront == nullptr) ptrTop = ptrFront; //last Node removed
	
	delete ptrTemp;
	return tReturn;
}

void main()
{
	Stack<int> MyStack;
	Queue<int> MyQueue;

	for (int intCount = 0; intCount < 20; intCount++)
	{
		MyStack.push(intCount);
		MyQueue.enqueue(intCount);
	}

	try
	{
		cout << "Stack:\n";
		while (true)
			cout << MyStack.pop() << " ";
	}
	catch (...)
	{
		cout << "\n";
	}
	try
	{
		cout << "Queue:\n";
		while (true)
			cout << MyQueue.dequeue() << " ";
	}
	catch (...)
	{
		cout << "\n";
	}

	system("pause");
}