///////////////////////////////////////////////////////////////////////////
//
//	CTList : Template List Class
//	class CTListItem<TYPE> : item class
//	class CTList<TYPE> : list class
//  class CTListParser<TYPE> : listparser
//
///////////////////////////////////////////////////////////////////////////

template<class TYPE>
class CTListParser;

///////////////////////////////////////////////////////////////////////////
//
//	class CTListItem
//
///////////////////////////////////////////////////////////////////////////

template<class TYPE>
class CTListItem
{
protected:
	TYPE		*m_pItem;

public:
	CTListItem	*m_pNext;

public:
	CTListItem(TYPE *_pT);
	virtual ~CTListItem();

	void vDeleteItem()
	{
		if (m_pItem) { delete m_pItem; m_pItem = NULL; }
	}

	TYPE *pGetItem()
	{
		return m_pItem;
	}
};

///////////////////////////////////////////////////////////////////////////
//
//	class CTListItem : implementation
//
///////////////////////////////////////////////////////////////////////////

template<class TYPE>
CTListItem<TYPE>::CTListItem(TYPE *_pT)
{
	m_pItem = _pT;
	m_pNext = NULL;
}

template<class TYPE>
CTListItem<TYPE>::~CTListItem()
{
}

///////////////////////////////////////////////////////////////////////////
//
//	class CTList
//
///////////////////////////////////////////////////////////////////////////

template<class TYPE>
class CTList
{
	friend class CTListParser<TYPE>;

protected:
	CTListItem<TYPE>	*m_pRoot;
	int					m_iNbItems;

protected:
	CTListItem<TYPE> *pGetRootItem() { return m_pRoot; }

public:
	CTList();
	virtual ~CTList();
		
	int iGetNumberOfItem() { return m_iNbItems; }
	void vClear();
	void vAddItem(TYPE *_pT);
	void vRemoveItem(TYPE *_pT);
	void vDeleteAllItems();
};

///////////////////////////////////////////////////////////////////////////
//
//	class CList : implementation
//
///////////////////////////////////////////////////////////////////////////

template<class TYPE>
CTList<TYPE>::CTList()
{
	m_pRoot = NULL;
	m_iNbItems = 0;
}

template<class TYPE>
CTList<TYPE>::~CTList()
{
	vClear();
}

template<class TYPE>
void CTList<TYPE>::vClear()
{
	CTListItem<TYPE> *pItem, *pTemp;

	pTemp = m_pRoot;
	pItem = m_pRoot;

	while (pItem)
	{
		pItem = pItem->m_pNext;
		delete pTemp;
		pTemp = pItem;
	}

	m_pRoot = NULL;
	m_iNbItems = 0;
}

template<class TYPE>
void CTList<TYPE>::vAddItem(TYPE *_pT)
{
	CTListItem<TYPE> *pItem, *pPrev;

	if (!m_pRoot)
	{
		m_pRoot = new CTListItem<TYPE>(_pT);
	}
	else
	{
		pItem = m_pRoot;
		pPrev = NULL;
		while (pItem)
		{
			pPrev = pItem;
			pItem = pItem->m_pNext;
		}

		pItem = new CTListItem<TYPE>(_pT);
		pPrev->m_pNext = pItem;
	}

	m_iNbItems++;
}

template<class TYPE>
void CTList<TYPE>::vRemoveItem(TYPE *_pT)
{
	CTListItem<TYPE> *pItem, *pPrev, *pNext;
	TYPE *T;

	pItem = m_pRoot;
	pPrev = NULL;
	while (pItem)
	{
		T = pItem->pGetItem();
		if (T == _pT)
		{
			if (pPrev)
			{
				pPrev->m_pNext = pNext;
				delete pItem;
				m_iNbItems--;
				break;
			}
			else
			{
				m_pRoot = pItem->m_pNext;
				delete pItem;
				m_iNbItems--;
				break;
			}
		}
		pPrev = pItem;
		pItem = pItem->m_pNext;
		if (pItem) pNext = pItem->m_pNext;
	}	
}

template<class TYPE>
void CTList<TYPE>::vDeleteAllItems()
{
	CTListItem<TYPE> *pItem;

	pItem = m_pRoot;

	while (pItem)
	{
		pItem->vDeleteItem();
		pItem = pItem->m_pNext;
	}

	vClear();
}

///////////////////////////////////////////////////////////////////////////
//
//	class CTListParser
//
///////////////////////////////////////////////////////////////////////////

template<class TYPE>
class CTListParser
{
protected:
	CTList<TYPE>		*m_pList;
	CTListItem<TYPE>	*m_pCurrent;

public:
	CTListParser(CTList<TYPE> *pList)
	{
		m_pList = pList;
	}

	TYPE *pGetRoot()
	{
		if (!m_pList)
			return NULL;

		m_pCurrent = m_pList->pGetRootItem();
		if (m_pCurrent)
			return m_pCurrent->pGetItem();
		else
			return NULL;
	}

	TYPE *pGetNext()
	{
		CTListItem<TYPE> *pItem;
		if (m_pCurrent)
		{
			pItem = m_pCurrent->m_pNext;
			if (pItem)
			{
				m_pCurrent = pItem;
				return m_pCurrent->pGetItem();
			}
			else
				return NULL;
		}
		else
			return NULL;
	}
};