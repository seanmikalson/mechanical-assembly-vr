#define DATA_FULL noItems >= maxItems
#define ALL_ITEMS int i = 0; i < noItems; i++
#define INDEX_OUT_OF_RANGE index >= noItems || index < 0

template<class cType> 
class List{

	protected:
		int noItems,maxItems;
		cType* data;

	public:
	    List(int maxItems);
		List();
		List(const List<cType>& rhs);
		~List();

		//-------------------------------------
		// Gets Functions
		//-------------------------------------
		cType* getItem(int index);
		int getNoItems(){return noItems;};
		int getMaxItems(){return maxItems;};
		cType* getDataPtr(){return data;};

		//-------------------------------------
		// Set Functions
		//-------------------------------------
		bool setItem(cType addition, int index);
		void setNoItems(int noItems){(*this).noItems = noItems;};
		void setMaxItems(int maxItems){(*this).maxItems = maxItems;};

		//-------------------------------------
		// Other Class Functions
		//-------------------------------------
		void addItem(cType addition);
		bool insertItem(cType addition,int index);
		void resetList(int maxItems);	
		void increaseSize(int amount);
		bool full(){return noItems >= maxItems;};
		bool removeItem(int index);
		cType* min();
		cType* max();
		int minIndex();
		int maxIndex();

		List<cType>& operator=(const List& rhs);
		cType& const operator[](int index);
};

//---------------------------------------------------
// Constructors and Destructors
//---------------------------------------------------
template<class cType> 
List<cType>::List(int maxItems)
{
	(*this).maxItems = maxItems;
	(*this).noItems = 0;
	(*this).data = new cType[maxItems];
}
template<class cType> 
List<cType>::List()
{
	(*this).maxItems = 10;
	(*this).noItems = 0;
	(*this).data = new cType[maxItems];
}
template<class cType> 
List<cType>::~List()
{
	delete []data;
}
template<class cType> 
List<cType>::List(const List<cType>& rhs)
{
	(*this).maxItems = rhs.maxItems;
	(*this).noItems = rhs.noItems;

	(*this).data = new cType[(*this).maxItems];

	for(ALL_ITEMS)
		(*this).data[i] = rhs.data[i];
}

//---------------------------------------------------
// Get Functions
//---------------------------------------------------
template<class cType> 
cType* List<cType>::getItem(int index)
{
	if(index >= noItems)
		return nullptr;

	return &data[index];
}

//---------------------------------------------------
// Set Functions
//---------------------------------------------------
template<class cType> 
bool List<cType>::setItem(cType addition, int index)
{
	if(index >= maxItems)
		return false;

	data[index] = addition;

	return true;
}

//---------------------------------------------------
// Other Class Functions
//---------------------------------------------------
template<class cType> 
void List<cType>::addItem(cType addition)
{
	if(full())
		increaseSize(maxItems);

	data[noItems++] = addition;
}
template<class cType> 
bool List<cType>::insertItem(cType addition, int index)
{
	#define ITEMS_AFTER_INSERTION int i = noItems; i > index; i--

	if(index >= noItems)
		return false;

	if(full())
	{
		int amount = (maxItems * 0.2) + 1;
		increaseSize(amount);
	}

	for(ITEMS_AFTER_INSERTION)
		data[i] = data[i-1];

	data[index] = addition;
	noItems++;
	return true;
}
template<class cType>
bool List<cType>::removeItem(int index)
{
	if(INDEX_OUT_OF_RANGE)
		return false;

	for(int i = index; i < noItems - 1; i++)
		data[i] = data[i + 1];

	noItems--;

	return true;
}
template<class cType> 
void List<cType>::increaseSize(int amount)
{
	cType* tempData = new cType[maxItems + amount];

	for(ALL_ITEMS)
		tempData[i] = data[i];

	delete []data;

	data = tempData;
	maxItems += amount;
}
template<class cType> 
void List<cType>::resetList(int maxItems)
{
	delete []data;

	noItems = 0;
	(*this).maxItems = maxItems;

	data = new cType[maxItems];
}
template<class cType> 
cType* List<cType>::min()
{
	if(noItems < 1)
		return nullptr;

	cType* temp = &data[0];
	for(int i = 1; i < noItems; i++)
	{
		if( *temp > data[i])
			temp = &data[i];
	}

	return temp;
}
template<class cType> 
cType* List<cType>::max()
{
	if(noItems < 1)
		return nullptr;

	cType* temp = &data[0];
	for(int i = 1; i < noItems; i++)
	{
		if( *temp < data[i])
			temp = &data[i];
	}

	return temp;
}
template<class cType>
int List<cType>::minIndex()
{
	if(noItems < 1)
		return -1;

	int temp = 0;
	for(int i = 1; i < noItems; i++)
	{
		if( data[temp] > data[i])
			temp = i;
	}

	return temp;
}
template<class cType>
int List<cType>::maxIndex()
{
	if(noItems < 1)
		return -1;

	int temp = 0;
	for(int i = 1; i < noItems; i++)
	{
		if( data[temp] < data[i])
			temp = i;
	}

	return temp;
}

//---------------------------------------------------
// Operators
//---------------------------------------------------
template<class cType> 
List<cType>& List<cType>::operator=(const List<cType>& rhs)
{
	if((*this).data != nullptr)
		delete []data;
	
	(*this).maxItems = rhs.maxItems;
	(*this).noItems = rhs.noItems;

	(*this).data = new cType[(*this).maxItems];

	for(ALL_ITEMS)
		(*this).data[i] = rhs.data[i];

	return *this;
}
template<class cType>
cType& List<cType>::operator[](int index) 
{
	return data[index];
}