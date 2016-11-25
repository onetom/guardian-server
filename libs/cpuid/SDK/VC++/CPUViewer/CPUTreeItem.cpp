#include "stdafx.h"
#include "CTList.h"
#include "cpuidsdk.h"
#include "CPUTreeItem.h"
#include "CPUViewer.h"


///////////////////////////////////////////////////////////////////////////////
//
//	CCPUTreeItem
//
///////////////////////////////////////////////////////////////////////////////


CCPUTreeItem::CCPUTreeItem(HTREEITEM _hTreeItem, 
						   int _itemclass,
						   int _proc_index,
						   int _core_index,
						   int _thread_index)
{
	m_hTreeItem = _hTreeItem;
	m_iItemClass = _itemclass;
	m_iProcessorIndex = _proc_index;
	m_iCoreIndex = _core_index;
	m_iThreadIndex = _thread_index;
}

CCPUTreeItem::~CCPUTreeItem()
{
}