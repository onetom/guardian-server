#ifndef _CPUTREEITEM_H_
#define _CPUTREEITEM_H_


#define TREE_ITEM_CLASS_PROCESSOR			0x1
#define TREE_ITEM_CLASS_CORE				0x2
#define TREE_ITEM_CLASS_THREAD				0x3


class CCPUTreeItem;
typedef CTList<CCPUTreeItem> tdCPUTreeItemList;
typedef CTListParser<CCPUTreeItem> tdCPUTreeItemListParser;


///////////////////////////////////////////////////////////////////////////////
//
//	CCPUTreeItem
//
///////////////////////////////////////////////////////////////////////////////

class CCPUTreeItem
{
protected:
	HTREEITEM	m_hTreeItem;
	int			m_iItemClass;

	int			m_iProcessorIndex;
	int			m_iCoreIndex;
	int			m_iThreadIndex;

public:
	CCPUTreeItem(HTREEITEM _hTreeItem,
				 int _itemclass,
				 int _proc_index,
				 int _core_index = I_UNDEFINED_VALUE,
				 int _thread_index = I_UNDEFINED_VALUE);

	virtual ~CCPUTreeItem();

	HTREEITEM hGetTreeItem() { return m_hTreeItem; }
	int iGetItemClass() { return m_iItemClass; }

	int iGetProcessorIndex() { return m_iProcessorIndex; }
	int iGetCoreIndex() { return m_iCoreIndex; }
	int iGetThreadIndex() { return m_iThreadIndex; }
};

#endif //_CPUTREEITEM_H_