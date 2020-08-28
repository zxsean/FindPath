#ifndef _SQ_LIST_H_
#define _SQ_LIST_H_

template <typename T>
class CSqList
{
private:
	int m_Size;
	int m_Length;
	T* m_Array;
	bool (* m_fBigger)(const T*, const T*);

public:
	CSqList(bool (* fBigger)(const T*, const T*), int Size = 32);
	CSqList(const CSqList& that);
	virtual ~CSqList();
	CSqList& operator = (const CSqList& that);

	bool Insert(T Data, int Pos);
	void Push(T Data);
	bool Erase(int Pos);
	void Clear();
	T* Get(int Pos);
	int Length() const;
	int Locate(T Data, int Begin);
	bool Sort(int Begin, int End, bool Increase = true);

	template <typename T>
	int LocateFather(T Data, int Begin,bool (* fBigger)(const T*, const T*))
	{
		if(Begin < 0 || Begin > m_Length)
			return 0;
		for(int i = Begin; i < m_Length; ++i)
		{
			if((*fBigger)(&Data , &m_Array[i]))
				return i + 1 - Begin;
		}
		return 0;
	}

	void SetBigger(bool (* fBigger)(const T*, const T*));
};

template <typename T>
CSqList<T>::CSqList(bool (* fBigger)(const T*, const T*), int Size = 32)
:m_Size(Size),m_Length(0),m_Array(new T [m_Size]),m_fBigger(fBigger)
{
}
template <typename T>
CSqList<T>::CSqList(const CSqList& that)
:m_Size(that.m_Size),m_Length(that.m_Length),m_fBigger(that.m_fBigger),m_Array(new T [m_Size])
{
	for(int i = 0; i < m_Length; ++ i)
		m_Array[i] = that.m_Array[i];
}
template <typename T>
CSqList<T>::~CSqList()
{
	delete []m_Array;
}
template <typename T>
CSqList<T>& CSqList<T>::operator = (const CSqList& that)
{	if(this != &that)
{
	delete[] m_Array;
	m_Length = that.m_Length;
	m_Size = that.m_Size;
	m_fBigger = that.m_fBigger;
	m_Array = new T[m_Size];
	for(int i = 0; i < m_Length; ++ i)
		m_Array[i] = that.m_Array[i];
}
return *this;
}
template <typename T>
bool CSqList<T>::Insert(T Data, int Pos)
{

	if(Pos < 0 || Pos > m_Length)
		return false;
	if (m_Length == m_Size)
	{
		m_Size *= 2;
		T* xp = new T [m_Size];
		for(int i = 0; i < m_Length; ++ i)
			xp[i] = m_Array[i];
		delete[] m_Array;
		m_Array = xp;
	}
	int n = m_Length - Pos + 1;
	for (int i = 0; i < n; ++i)
		m_Array[m_Length - i] = m_Array[m_Length - 1 - i];
	m_Array[Pos] = Data;
	m_Length ++;
	return true;
}
template <typename T>
void CSqList<T>::Push(T Data)
{
	Insert( Data,m_Length);
}
template <typename T>
bool CSqList<T>::Erase(int Pos)
{
	if(Pos < 0 || Pos > m_Length)
		return false;
	for(int i = Pos - 1;i < m_Length; ++i)
		m_Array[i] = m_Array[i+1];
	m_Length--;
	return true;
}
template <typename T>
void CSqList<T>::Clear()
{
	m_Length = 0;
}
template <typename T>
T* CSqList<T>::Get(int Pos)
{
	if(Pos < 0 || Pos > m_Length)
		return 0;
	return &m_Array[Pos];
}
template <typename T>
int CSqList<T>::Length() const
{
	return m_Length;
}
template <typename T>
int CSqList<T>::Locate(T Data, int Begin)
{
	if(Begin < 0 || Begin > m_Length)
		return -1;
	for(int i = Begin; i < m_Length; ++i)
	{
		if(!(*m_fBigger)(&m_Array[i], &Data) && !(*m_fBigger)(&Data,&m_Array[i]))
			return i + 1 - Begin;
	}
	return -1;
}
template <typename T>
bool CSqList<T>::Sort(int Begin, int End, bool Increase = true)
{
	if(Begin< 0 || Begin > End || End > m_Length)
		return false;
	if(Increase)
	{
		for(int j = Begin; j < End - 1; ++j)
		{
			for(int i = Begin;i < End - j - 1; ++i)
			{
				if((*m_fBigger)(&m_Array[i],&m_Array[i+1]))
				{
					T a = m_Array[i];
					m_Array[i] = m_Array[i + 1];
					m_Array[i + 1] = a;
				}
			}
		}
	}
	else
	{
		for(int j = Begin; j < End - 1; ++j)
		{
			for(int i = Begin;i < End - j - 1; ++i)
			{
				if((*m_fBigger)(&m_Array[i+1],&m_Array[i]))
				{
					T a = m_Array[i];
					m_Array[i] = m_Array[i + 1];
					m_Array[i + 1] = a;
				}
			}
		}
	}
	return true;
}
template <typename T>
void CSqList<T>::SetBigger(bool (* fBigger)(const T*, const T*))
{
	m_fBigger = fBigger;
}
#endif