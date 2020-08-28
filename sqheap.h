#ifndef _SQ_HEAP_H_
#define _SQ_HEAP_H_

//从下标为1的地方开始放数据

template <typename T>
class CSqHeap
{
	int m_Size;
	int m_Length;
	T* m_Array;
	bool (* m_fBigger)(const T*, const T*);

public:

	CSqHeap(bool (* fBigger)(const T*, const T*), int Size = 8);
	CSqHeap(const CSqHeap& that);
	virtual ~CSqHeap();
	CSqHeap& operator=(const CSqHeap& that);

	void Enter(T Data);
	bool Quit(T* pData);
	bool GetTop(T* pData);
	void Clear();
	int Length();

	template <typename T>
	//辅助函数比较表中G与传入数据G的大小
	int BiggerG(T Data, int Begin,bool (* fBigger)(const T*, const T*))
	{
		if(Begin < 0 || Begin > m_Length)
			return 0;
		for(int i = Begin; i < m_Length; ++i)
		{
			if((*fBigger)(&m_Array[i], &Data))
			{
				if (m_Array[i].g > Data.g)
					return 1;
			}
		}
		return 0;
	}

	template <typename T>
	//辅助函数判断传入数据是否在堆中
	int Locate(T Data, int Begin,bool (* fBigger)(const T*, const T*))
	{
		if(Begin < 0 || Begin > m_Length)
			return -1;
		for(int i = Begin; i < m_Length; ++i)
		{
			if((*fBigger)(&m_Array[i], &Data))
					return i;
		}
		return -1;
	}

	template <typename T>
	//辅助函数查找传入数据N在堆中位置,删除堆中N
	void XiuGai(T Data, int Begin,bool (* fBigger)(const T*, const T*))
	{
		int pos;
		for(int i = Begin; i < m_Length; ++i)
		{
			if((*fBigger)(&m_Array[i], &Data))
				//return i;
				pos = i;
		}
		for (int i = pos; i < m_Length;++i)
			m_Array[i] = m_Array[i + 1];
		m_Length -= 1;
		//return -1;
	}

	//void Get(int POS)
	//{
	//	for (int i = POS; i < m_Length;++i)
	//		m_Array[i] = m_Array[i + 1];
	//	m_Length -= 1;
	//}

	void SetBigger(bool (* fBigger)(const T*, const T*));
};

template <typename T>
CSqHeap<T>::CSqHeap(bool (* fBigger)(const T*, const T*), int Size)
:
m_Size(Size),
m_Length(0),
m_Array(new T[m_Size]),
m_fBigger(fBigger)
{}

template <typename T>
CSqHeap<T>::CSqHeap(const CSqHeap& that)
:
m_Size(that.m_Size),
m_Length(that.m_Length),
m_Array(new T[m_Size]),
m_fBigger(that.m_fBigger)
{
	for (int i = 1; i <= m_Length; ++i)
		m_Array[i] = that.m_Array[i];
}

template <typename T>
CSqHeap<T>::~CSqHeap()
{
	delete [] m_Array;
}

template <typename T>
CSqHeap<T>& CSqHeap<T>::operator = (const CSqHeap& that)
{
	if (this != &that)
	{
		delete [] m_Array;

		m_Size = that.m_Size;
		m_Length = that.m_Length;
		m_Array = new T[m_Size];
		m_fBigger = that.m_fBigger;

		for (int i = 1; i <= m_Length; ++i)
			m_Array[i] = that.m_Array[i];
	}
	return *this;
}

template <typename T>
void CSqHeap<T>::Enter(T Data)
{
	if (m_Length + 1 == m_Size)
	{
		T* p = new T[m_Size *= 2];
		for (int i = 1; i <= m_Length; ++i)
			p[i] = m_Array[i];
		delete [] m_Array;
		m_Array = p;
	}

	m_Array[m_Length += 1] = Data;

	int zXB = m_Length;
	int fXB = zXB / 2;

	while (zXB > 1 && (*m_fBigger)(&m_Array[zXB], &m_Array[fXB]))
	{
		T t = m_Array[zXB];
		m_Array[zXB] = m_Array[fXB];
		m_Array[fXB] = t;

		zXB = fXB;
		fXB = zXB / 2;
	}
}

template <typename T>
bool CSqHeap<T>::Quit(T* pData)
{
	if (m_Length == 0)
		return false;
	else if (m_Length == 1)
	{
		*pData = m_Array[1];
		m_Length -= 1;
		return true;
	}
	else
	{
		*pData = m_Array[1];

		int fXB = 1;

		while (1)
		{
			//得到其左右子树下标
			int leftzXB = fXB * 2;
			int rightzXB = leftzXB + 1;

			//左右都有
			if (leftzXB <= m_Length && rightzXB <= m_Length)
			{
				if ((*m_fBigger)(&m_Array[leftzXB], &m_Array[rightzXB]))
				{
					m_Array[fXB] = m_Array[leftzXB];
					fXB = leftzXB;
				}
				else
				{
					m_Array[fXB] = m_Array[rightzXB];
					fXB = rightzXB;
					if (rightzXB == m_Length)
					{
						m_Length -= 1;
						return true;
					}
				}
			}
			//有左无右
			else if (leftzXB <= m_Length && rightzXB > m_Length)
			{
				m_Array[fXB] = m_Array[leftzXB];
				m_Length -= 1;
				return true;
			}
			//左右都无
			else
				break;
		}

		//将最后的节点放入到fXB
		m_Array[fXB] = m_Array[m_Length];
		m_Length -= 1;

		int zXB = fXB;
		fXB = zXB / 2;
		while (zXB > 1 && (*m_fBigger)(&m_Array[zXB], &m_Array[fXB]))
		{
			T t = m_Array[zXB];
			m_Array[zXB] = m_Array[fXB];
			m_Array[fXB] = t;

			zXB = fXB;
			fXB = zXB / 2;
		}

		return true;
	}
}

template <typename T>
bool CSqHeap<T>::GetTop(T* pData)
{
	if (0 == m_Length)
		return false;
	else
	{
		*pData = *(m_Array + 1);
		return true;
	}
}

template <typename T>
void CSqHeap<T>::Clear()
{
	m_Length = 0;
}

template <typename T>
int CSqHeap<T>::Length()
{
	return m_Length;
}

template <typename T>
void CSqHeap<T>::SetBigger(bool (* fBigger)(const T*, const T*))
{
	m_fBigger = fBigger;
}

#endif