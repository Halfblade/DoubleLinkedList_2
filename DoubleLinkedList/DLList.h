#pragma once
#include "DynArray.h"
#include <iostream>
template<typename Type> class DLLIter;
template<typename Type> class DLList;

template<typename Type>
class DLList
{
	

private:
	struct Node
	{
		Type data;
		Node* next;
		Node* prev;

	public:
		Node(Type v = NULL, Node* Next = nullptr, Node* Prev = nullptr)
		{
			data = v;
			next = Next;
			prev = Prev;
		}


		friend class DLList<Type>;
		friend class DLLIter<Type>;

	};
	Node* head = nullptr;
	Node* tail = nullptr;
	unsigned int Size = 0;


public:
	friend class DLLIter<Type>;
		/////////////////////////////////////////////////////////////////////////////
		// Function : Constructor
		// Notes : Does nothing
		/////////////////////////////////////////////////////////////////////////////
	DLList();

		/////////////////////////////////////////////////////////////////////////////
		// Function : Destructor
		// Notes : Destroys a list (call clear())
		/////////////////////////////////////////////////////////////////////////////
	~DLList();

		/////////////////////////////////////////////////////////////////////////////
		// Function : Assignment Operator
		// Notes: Deep copy of that list. Can be done with a loop
		/////////////////////////////////////////////////////////////////////////////
	DLList<Type>& operator=(const DLList<Type>& that);

		/////////////////////////////////////////////////////////////////////////////
		// Function : Copy Constructor
		// Notes: Call assignment operator
		/////////////////////////////////////////////////////////////////////////////
	DLList(const DLList<Type>& that);

		/////////////////////////////////////////////////////////////////////////////
		// Function : addHead
		// Parameters : v - the item to add to the head of the list
		/////////////////////////////////////////////////////////////////////////////
	void addHead(const Type& v);

		/////////////////////////////////////////////////////////////////////////////
		// Function : addTail
		// Parameters : v - the item to add to the tail of the list
		/////////////////////////////////////////////////////////////////////////////
	void addTail(const Type& v);

		/////////////////////////////////////////////////////////////////////////////
		// Function : clear
		// Notes : clears the list, freeing any dynamic memory
		/////////////////////////////////////////////////////////////////////////////
	void clear();


		/////////////////////////////////////////////////////////////////////////////
		// Function : insert
		// Parameters :	index - an iterator to the location to insert at
		//				v - the item to insert
		// Notes : do nothing if index current pointer is null
		/////////////////////////////////////////////////////////////////////////////
	void insert(DLLIter<Type>& index, const Type& v);

		/////////////////////////////////////////////////////////////////////////////
		// Function : remove
		// Parameters :	index - an iterator pointing at the node to delete
		// Notes : do nothing if index current pointer is null
		/////////////////////////////////////////////////////////////////////////////
	void remove(DLLIter<Type>& index);

	void helper(Node* n);
	void helperT(Node* n);
};



template<typename Type>
class DLLIter
{
	

private:

	DLList<Type>* ptrList;
	typename DLList<Type>::Node* curr;
	


public:

	friend class DLList<Type>;

		/////////////////////////////////////////////////////////////////////////////
		// Function : Constructor
		// Parameters :	listToIterate - the list to iterate
		// Notes: Point list pointer at address of this list object
		/////////////////////////////////////////////////////////////////////////////
	DLLIter(DLList<Type>& listToIterate);

		/////////////////////////////////////////////////////////////////////////////
		// Function : beginHead
		// Notes : moves the iterator to the head of the list
		/////////////////////////////////////////////////////////////////////////////
	void beginHead();

		/////////////////////////////////////////////////////////////////////////////
		// Function : beginTail
		// Notes : moves the iterator to the tail of the list
		/////////////////////////////////////////////////////////////////////////////
	void beginTail();

		/////////////////////////////////////////////////////////////////////////////
		// Function : end
		// Notes : returns true if current pointer is null, false otherwise
		/////////////////////////////////////////////////////////////////////////////
	bool end() const;

		/////////////////////////////////////////////////////////////////////////////
		// Function : operator++
		// Notes : move the current pointer to its own next
		/////////////////////////////////////////////////////////////////////////////
	DLLIter<Type>& operator++();

		/////////////////////////////////////////////////////////////////////////////
		// Function : operator--
		// Notes : move the current pointer to its own previous
		/////////////////////////////////////////////////////////////////////////////
	DLLIter<Type>& operator--();


		/////////////////////////////////////////////////////////////////////////////
		// Function : current
		// Notes : returns the item at the current iterator location. Does not
		//		perform error checking
		////////////////////////////////////////////////////////////////////////////
	Type& current() const;
	
};

template<typename Type>
inline DLList<Type>::DLList()
{
}

template<typename Type>
inline DLList<Type>::~DLList()
{
	clear();
}

template<typename Type>
inline DLList<Type>& DLList<Type>::operator=(const DLList<Type>& that)
{
	if (this != &that)
	{
		clear();
		helper(that.head);
		
	}
	return *this;
}

template<typename Type>
inline DLList<Type>::DLList(const DLList<Type>& that)
{
	*this = that;
}

//head prev pointer will always be nullptr
template<typename Type>
inline void DLList<Type>::addHead(const Type& v)
{
	Node* newNode = new Node(v);
	if (head == nullptr) // if the list is empty
	{
		head = newNode;
		tail = newNode;
	}
	else if (tail->prev == nullptr)
	{
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
		tail->prev = head;
	}
	else
	{
		
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
		
	}
	
}

template<typename Type>
inline void DLList<Type>::addTail(const Type& v)
{
	Node* newNode = new Node(v);
	if (tail == nullptr)
	{
		
		head = newNode;
		tail = newNode;
		
	}
	else if (head->next == nullptr)
	{
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
		head->next = tail;
	}
	else
	{
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
	
}

template<typename Type>
inline void DLList<Type>::clear()
{
	while (head != nullptr)
	{
		Node* curr = head;
		head = head->next;
		delete curr;
		
		

	}
	tail = nullptr; // set tail to null because the loop ends based on head
	
	
}

template<typename Type>
inline void DLList<Type>::insert(DLLIter<Type>& index, const Type& v)
{
	
	if (index.curr != nullptr)
	{
		if (index.curr == head)
		{
			addHead(v);
			index.curr = head;
			
			
		}
		else
		{
			Node* temp = new Node(v);
			index.curr->prev->next = temp;
			temp->prev = index.curr->prev;
			index.curr->prev = temp;
			temp->next = index.curr;
			index.curr = temp;
			
			
			
		}
	}
		
	
}

template<typename Type>
inline void DLList<Type>::remove(DLLIter<Type>& index)
{
	Node* temp = index.curr;
	if (index.curr != nullptr)
	{
		if (index.curr->next == nullptr && index.curr->prev == nullptr)
		{
			index.curr = nullptr;
			head = nullptr;
			tail = nullptr;
		}
		else if (index.curr == head)
		{
			head = head->next;
			head->prev = nullptr;
			index.curr = head;
			
		
		}
		else if (index.curr == tail)
		{
			tail = tail->prev;
			tail->next = nullptr;
			index.curr = tail;
			
			
		}
		else
		{
			
			index.curr->prev->next = index.curr->next;
			index.curr->next->prev = index.curr->prev;
			index.curr = index.curr->next;
			
			

		}
	}
		delete temp;
}

template<typename Type>
inline void DLList<Type>::helper(Node* n)
{
	if (n != nullptr)
	{
		
		helper(n->next);
		addHead(n->data);
	}
}

template<typename Type>
inline void DLList<Type>::helperT(Node* n)
{
	if (n != nullptr)
	{
		helperT(n->next);
		addTail(n->data);
	}
}

template<typename Type>
inline DLLIter<Type>::DLLIter(DLList<Type>& listToIterate)
{
	ptrList = &listToIterate;
	
}

template<typename Type>
inline void DLLIter<Type>::beginHead()
{
	curr = ptrList->head;
}

template<typename Type>
inline void DLLIter<Type>::beginTail()
{
	curr = ptrList->tail;
}

template<typename Type>
inline bool DLLIter<Type>::end() const
{
	if (curr == nullptr)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

template<typename Type>
inline DLLIter<Type>& DLLIter<Type>::operator++()
{
	if (end() == false)
	{
		//sets current to current next
		curr = curr->next;
	}
	return *this;
	
}

template<typename Type>
inline DLLIter<Type>& DLLIter<Type>::operator--()
{
	if (curr != nullptr)
	{
		
		curr = curr->prev;
		
	}

	//returns current point location
	return *this;
	
}

template<typename Type>
inline Type& DLLIter<Type>::current() const
{
	return curr->data;
}


