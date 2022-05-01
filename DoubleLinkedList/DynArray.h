#pragma once

template < typename Type>

class DynArray
{
private:

	Type* array = nullptr;
	unsigned int Size = 0, Capacity = 0;


public:

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Default Constructor
	// Notes : Doesn't do anything since data members were initialized above.
	//		Still needs to exist due to copy constructor.
	/////////////////////////////////////////////////////////////////////////////
	DynArray();

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Destructor
	// Notes : cleans up any dynamic memory (can call clear())
	/////////////////////////////////////////////////////////////////////////////
	~DynArray();

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Copy Constructor
	// Notes : Call the assignment operator
	/////////////////////////////////////////////////////////////////////////////
	DynArray(const DynArray<Type>& that);

	/////////////////////////////////////////////////////////////////////////////
	// Function :	Assignment Operator
	// Notes : Perform deep copy of 'that' internal array
	/////////////////////////////////////////////////////////////////////////////
	DynArray<Type>& operator=(const DynArray<Type>& that);

	/////////////////////////////////////////////////////////////////////////////
	// Function : operator[]
	// Parameters : index - the index to access
	// Return : Type & - returns the array element at [index]
	// Notes : performs no error checking
	/////////////////////////////////////////////////////////////////////////////
	Type& operator[](const unsigned int index);
	/////////////////////////////////////////////////////////////////////////////
	// Function : operator[] const version
	// Notes : Same as above but works for const DynArray objects
	/////////////////////////////////////////////////////////////////////////////
	const Type& operator[](const unsigned int index) const;
		/////////////////////////////////////////////////////////////////////////////
	// Function :	size
	// Returns : int - returns the Size data member
	/////////////////////////////////////////////////////////////////////////////
		unsigned int size() const;
	/////////////////////////////////////////////////////////////////////////////
	// Function : capacity
	// Returns : int - returns the Capacity data member
	/////////////////////////////////////////////////////////////////////////////
	unsigned int capacity() const;

	/////////////////////////////////////////////////////////////////////////////
	// Function :	clear
	// Notes : deletes any dynamic memory and resets size and capacity to 0
	//	and array to nullptr
	/////////////////////////////////////////////////////////////////////////////
	void clear();

	/////////////////////////////////////////////////////////////////////////////
	// Function : append
	// Parameters : item - the item to be appended to the next open spot
	// Notes : this function will append the item to the next open spot. if 
	//		the array is full first, call reserve() to double the array, then
	//		append the item.
	/////////////////////////////////////////////////////////////////////////////
	void append(const Type& item);

	/////////////////////////////////////////////////////////////////////////////
	// Function : reserve
	// Parameters : newCap - the new capacity
	// Notes : 	A) Default parameter of 0 should double the array capacity. In
	//	this double case, check for existing capacity of 0 or non-0.
	//	B) Parameter of lesser (non-0) or equal value to current capacity
	//	should do NOTHING.
	//	C) Parameter of higher value should be the newvalue for current
	//	capacity.
	//	Reallocates the array based on the new capacity amount (and copies over
	//	the existing data)
	/////////////////////////////////////////////////////////////////////////////
	void reserve(const unsigned int& newCap = 0);

};

template<typename Type>
inline DynArray<Type>::DynArray()
{
}

template<typename Type>
inline DynArray<Type>::~DynArray()
{
	clear();
}

template<typename Type>
inline DynArray<Type>::DynArray(const DynArray<Type>& that)
{
	array = nullptr;
	*this = that;
}

// that array is source and this is destination
template<typename Type>
inline DynArray<Type>& DynArray<Type>::operator=(const DynArray<Type>& that)
{
	
	if (this != &that)
	{
		delete[] this->array;
		this->array = new Type[that.Capacity];
		for (unsigned int i = 0; i < that.Size; i++)
		{
			this->array[i] = that.array[i];
		}
		this->Capacity = that.Capacity;
		this->Size = that.Size;
	}
	return *this;
}

template<typename Type>
inline Type& DynArray<Type>::operator[](const unsigned int index)
{
	// TODO: insert return statement here
	return array[index];
}

template<typename Type>
inline const Type& DynArray<Type>::operator[](const unsigned int index) const
{
	// TODO: insert return statement here
	return array[index];
}

//size of only data not null terminators
template<typename Type>
inline unsigned int DynArray<Type>::size() const
{
	return Size;
}

//complete size of the array pointer
template<typename Type>
inline unsigned int DynArray<Type>::capacity() const
{
	return Capacity;
}

template<typename Type>
inline void DynArray<Type>::clear()
{
	if (array)
	{
		delete[] array;
	}
	array = nullptr;
	Capacity = 0;
	Size = 0;
}

template<typename Type>
inline void DynArray<Type>::append(const Type& item)
{
	if (Size >= Capacity)
	{
		reserve();

	}
	array[Size] = item;
	Size++;


}

template<typename Type>
inline void DynArray<Type>::reserve(const unsigned int& newCap)
{
	if (newCap == 0)
	{
		if (Capacity == 0)
		{
			Capacity = 1;
		}
		else if (Capacity != 0)
		{
			Capacity = Capacity * 2;
		}
	}
	else if (newCap <= Capacity)
		return;
	else
	{
		Capacity = newCap;
	}
	Type* array2 = new Type[Capacity];
	for (unsigned int i = 0; i < Size; i++)
	{
		array2[i] = array[i];
	}

	delete[] array;

	array = array2;



}
