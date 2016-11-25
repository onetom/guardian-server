// CPUViewerView.cpp : implementation of the CCPUViewerView class
//

#include "stdafx.h"
#include "CTList.h"
#include "cpuidsdk.h"
#include "CPUTreeItem.h"
#include "CPUViewer.h"
#include "CPUViewerDoc.h"
#include "CPUViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCPUViewerView

IMPLEMENT_DYNCREATE(CCPUViewerView, CListView)

BEGIN_MESSAGE_MAP(CCPUViewerView, CListView)
	ON_WM_STYLECHANGED()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CCPUViewerView construction/destruction

CCPUViewerView::CCPUViewerView()
{
	// TODO: add construction code here
	m_hCurrentTreeItem = NULL;
}

CCPUViewerView::~CCPUViewerView()
{
}

BOOL CCPUViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

void CCPUViewerView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}


// CCPUViewerView diagnostics

#ifdef _DEBUG
void CCPUViewerView::AssertValid() const
{
	CListView::AssertValid();
}

void CCPUViewerView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CCPUViewerDoc* CCPUViewerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCPUViewerDoc)));
	return (CCPUViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CCPUViewerView message handlers
void CCPUViewerView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window	
	CListView::OnStyleChanged(nStyleType,lpStyleStruct);	
}


int CCPUViewerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CListCtrl &lc = GetListCtrl();

	lc.ModifyStyle(LVS_SORTASCENDING | LVS_SORTDESCENDING, LVS_REPORT);
	DWORD dwStyle = lc.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	lc.SetExtendedStyle(dwStyle);

	//lc.EnableWindow(FALSE);
	lc.InsertColumn(0, _T("Field"), LVCFMT_LEFT, 160);
	lc.InsertColumn(1, _T("Value"), LVCFMT_LEFT, 300);
	lc.DeleteAllItems();

	return 0;
}

void CCPUViewerView::OnDestroy()
{
	CListView::OnDestroy();

	// TODO: Add your message handler code here
	CListCtrl &lc = GetListCtrl();
	lc.DeleteAllItems();
}

void CCPUViewerView::vAddItem(TCHAR *_szTitle, LPCSTR _szValue, int _item, BOOL _bUpdate)
{
#ifdef _UNICODE
	TCHAR TempStr[MAX_PATH];
#endif
	CListCtrl &lc = GetListCtrl();

	if (_bUpdate)
	{
	#ifdef _UNICODE
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, _szValue, -1, TempStr, MAX_PATH);
		lc.SetItem(_item, 1, LVIF_TEXT, TempStr, 0, 0, 0, 0);
	#else
		lc.SetItem(_item, 1, LVIF_TEXT, (LPSTR)_szValue, 0, 0, 0, 0);
	#endif
	}
	else
	{
		LVITEM lvi;

		lvi.mask =  LVIF_TEXT;
		lvi.iItem = _item;
		lvi.iSubItem = 0;
		lvi.pszText = _szTitle;
		lc.InsertItem(&lvi);

		lvi.iSubItem = 1;
	#ifdef _UNICODE
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, _szValue, -1, TempStr, MAX_PATH);
		lvi.pszText = TempStr;
	#else
		lvi.pszText = (LPSTR)_szValue;
	#endif
		lc.SetItem(&lvi);
	}
}
void CCPUViewerView::vUpdate(CCPUTreeItem *_pCPUTreeItem)
{
	char		buffer[512];
	char		buffer2[128];
	int			proc_id, core_id, thread_id, item, iValue;
	int			supported, enabled;
	float		fValue;
	BOOL		bClearList;

	CPUIDSDK *pSDK = theApp.pGetSDKInstance();
	if (!pSDK) return;

	CListCtrl &lc = GetListCtrl();
	if (!_pCPUTreeItem)
	{
		lc.DeleteAllItems();
		m_hCurrentTreeItem = NULL;
		return;
	}

	if (m_hCurrentTreeItem == _pCPUTreeItem)
		bClearList = FALSE;
	else
		bClearList = TRUE;

	if (bClearList)
	{
		m_hCurrentTreeItem = _pCPUTreeItem;
		lc.DeleteAllItems();
	}

	switch (_pCPUTreeItem->iGetItemClass())
	{
		case TREE_ITEM_CLASS_PROCESSOR:
			{
				proc_id = _pCPUTreeItem->iGetProcessorIndex();
				item = 0;

			//	Number of cores
				sprintf_s(buffer, _countof(buffer), "%d", pSDK->GetProcessorCoreCount(proc_id));
				vAddItem(_T("Number of cores"), buffer, item++, !bClearList);

			//	Number of threads
				sprintf_s(buffer, _countof(buffer), "%d", pSDK->GetProcessorThreadCount(proc_id));
				vAddItem(_T("Number of threads"), buffer, item++, !bClearList);

			//	Processor name
				if (pSDK->GetProcessorName(proc_id, buffer))
				{
					vAddItem(_T("Name"), buffer, item++, !bClearList);
				}

			//	Processor code name
				if (pSDK->GetProcessorCodeName(proc_id, buffer))
				{
					vAddItem(_T("Codename"), buffer, item++, !bClearList);
				}

			//	Processor package
				if (pSDK->GetProcessorPackage(proc_id, buffer))
				{
					vAddItem(_T("Package"), buffer, item++, !bClearList);
				}

			//	Processor specification
				if (pSDK->GetProcessorSpecification(proc_id, buffer))
				{
					vAddItem(_T("Specification"), buffer, item++, !bClearList);
				}

			//	Processor stepping
				if (pSDK->GetProcessorStepping(proc_id, buffer))
				{
					vAddItem(_T("Revision"), buffer, item++, !bClearList);
				}

			//	Manufacturing process
				fValue = pSDK->GetProcessorManufacturingProcess(proc_id);
				if (IS_F_DEFINED(fValue))
				{
					if (fValue < 0.10f)
					{
						float fVal = fValue * 1000.0f;
						sprintf_s(buffer, _countof(buffer), "%d nm", (int)(fVal + 0.5f));
					}
					else
					{
						sprintf_s(buffer, _countof(buffer), "%1.2f um", fValue);
					}
					vAddItem(_T("Process"), buffer, item++, !bClearList);
				}

			//	Instruction sets
				sprintf_s(buffer, _countof(buffer), "");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_MMX)?"MMX":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_EXTENDED_MMX)?" (+)":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_3DNOW)?", 3DNow!":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_EXTENDED_3DNOW)?" (+)":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSE)?", SSE":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSE2)?", SSE2":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSE3)?", SSE3":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSSE3)?", SSSE3":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSE4_1)?", SSE4.1":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSE4_2)?", SSE4.2":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_SSE4A)?", SSE4A":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_X86_64)?", x86-64":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_NX)?", NX":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_VMX)?", VMX":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_AES)?", AES":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_AVX)?", AVX":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_AVX2)?", AVX2":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_XOP)?", XOP":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_FMA3)?", FMA3":"");
				strcat_s(buffer, _countof(buffer), pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_FMA4)?", FMA4":"");

				if (pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_RTM) &&
					pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_HLE))
				{
					strcat_s(buffer, _countof(buffer), ", TSX");
				}
				else if (pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_RTM))
				{
					strcat_s(buffer, _countof(buffer), ", RTM");
				}
				else if (pSDK->IsProcessorInstructionSetAvailable(proc_id, ISET_HLE))
				{
					strcat_s(buffer, _countof(buffer), ", HLE");
				}

				vAddItem(_T("Instructions Sets"), buffer, item++, !bClearList);

			//	Virtualization
				if (pSDK->GetVirtualTechnologyStatus(proc_id, &supported, &enabled))
				{
					sprintf_s(buffer, _countof(buffer), "");
					if (IS_I_DEFINED(supported))
					{
						strcat_s(buffer, _countof(buffer), supported?"supported":"not supported");

						if (IS_I_DEFINED(enabled))
							strcat_s(buffer, _countof(buffer), enabled?", enabled":", not enabled");

						vAddItem(_T("Virtualization"), buffer, item++, !bClearList);
					}
				}


			//	Bus frequency
				fValue = pSDK->GetBusFrequency();
				if (IS_F_DEFINED(fValue))
				{
					sprintf_s(buffer, _countof(buffer), "%.1f MHz", fValue);
					vAddItem(_T("Bus Speed"), buffer, item++, !bClearList);
				}

			//	Rated bus frequency
				fValue = pSDK->GetProcessorRatedBusFrequency(proc_id);
				if (IS_F_DEFINED(fValue))
				{
					sprintf_s(buffer, _countof(buffer), "%.1f MHz", fValue);
					vAddItem(_T("Rated Bus Speed"), buffer, item++, !bClearList);
				}

			//	Stock core speed
				iValue = pSDK->GetProcessorStockClockFrequency(proc_id);
				if (IS_I_DEFINED(iValue))
				{
					sprintf_s(buffer, _countof(buffer), "%d MHz", iValue);
					vAddItem(_T("Stock Core Speed"), buffer, item++, !bClearList);
				}

			//	Stock bus speed
				iValue = pSDK->GetProcessorStockBusFrequency(proc_id);
				if (IS_I_DEFINED(iValue))
				{
					sprintf_s(buffer, _countof(buffer), "%d MHz", iValue);
					vAddItem(_T("Stock Bus Speed"), buffer, item++, !bClearList);
				}

			//	HT
				supported = enabled = 0;
				BOOL result = pSDK->GetHyperThreadingStatus(proc_id, &supported, &enabled);

				unsigned int model_id = pSDK->GetProcessorID(proc_id);
				int debug = 0;

			//	Caches
				int max_level = pSDK->GetProcessorMaxCacheLevel(proc_id);
				if (IS_I_DEFINED(max_level))
				{
					int NbCaches, CacheSize, associativity, linesize;

					if (max_level >= 1)
					{
					//	Data L1
						pSDK->GetProcessorCacheParameters(proc_id, 1, CACHE_TYPE_DATA, &NbCaches, &CacheSize);
						if (CacheSize > 0)
						{
							if (NbCaches > 1)
								sprintf_s(buffer, _countof(buffer), "%d x %d KBytes", NbCaches, CacheSize);
							else
								sprintf_s(buffer, _countof(buffer), "%d KBytes", CacheSize);

							pSDK->GetProcessorExtendedCacheParameters(proc_id, 1, CACHE_TYPE_DATA, &associativity, &linesize);
							if (IS_I_DEFINED(associativity))
							{
								sprintf_s(buffer2, _countof(buffer2), ", %d-way", associativity);
								strcat_s(buffer, _countof(buffer), buffer2);
							}
							if (IS_I_DEFINED(linesize))
							{
								sprintf_s(buffer2, _countof(buffer2), ", %d-byte line size", linesize);
								strcat_s(buffer, _countof(buffer), buffer2);
							}

							vAddItem(_T("L1 Data Cache"), buffer, item++, !bClearList);
						}

					//	Instruction L1
						pSDK->GetProcessorCacheParameters(proc_id, 1, CACHE_TYPE_INSTRUCTION, &NbCaches, &CacheSize);
						if (CacheSize > 0)
						{
							if (NbCaches > 1)
								sprintf_s(buffer, _countof(buffer), "%d x %d KBytes", NbCaches, CacheSize);
							else
								sprintf_s(buffer, _countof(buffer), "%d KBytes", CacheSize);

							pSDK->GetProcessorExtendedCacheParameters(proc_id, 1, CACHE_TYPE_INSTRUCTION, &associativity, &linesize);
							if (IS_I_DEFINED(associativity))
							{
								sprintf_s(buffer2, _countof(buffer2), ", %d-way", associativity);
								strcat_s(buffer, _countof(buffer), buffer2);
							}
							if (IS_I_DEFINED(linesize))
							{
								sprintf_s(buffer2, _countof(buffer2), ", %d-byte line size", linesize);
								strcat_s(buffer, _countof(buffer), buffer2);
							}

							vAddItem(_T("L1 Instructions Cache"), buffer, item++, !bClearList);
						}

					//	Trace cache
						pSDK->GetProcessorCacheParameters(proc_id, 1, CACHE_TYPE_TRACE_CACHE, &NbCaches, &CacheSize);
						if (CacheSize > 0)
						{
							if (NbCaches > 1)
								sprintf_s(buffer, _countof(buffer), "%d x %d Kuops", NbCaches, CacheSize);
							else
								sprintf_s(buffer, _countof(buffer), "%d Kuops", CacheSize);

							pSDK->GetProcessorExtendedCacheParameters(proc_id, 1, CACHE_TYPE_INSTRUCTION, &associativity, &linesize);
							if (IS_I_DEFINED(associativity))
							{
								sprintf_s(buffer2, _countof(buffer2), ", %d-way", associativity);
								strcat_s(buffer, _countof(buffer), buffer2);
							}

							vAddItem(_T("L1 Trace Cache"), buffer, item++, !bClearList);
						}
					}

				//	L2 Cache
					if (max_level >= 2)
					{
						pSDK->GetProcessorCacheParameters(proc_id, 2, CACHE_TYPE_UNIFIED, &NbCaches, &CacheSize);
						if (CacheSize > 0)
						{
							if (NbCaches > 1)
								sprintf_s(buffer, _countof(buffer), "%d x %d KBytes", NbCaches, CacheSize);
							else
								sprintf_s(buffer, _countof(buffer), "%d KBytes", CacheSize);

							pSDK->GetProcessorExtendedCacheParameters(proc_id, 2, CACHE_TYPE_UNIFIED, &associativity, &linesize);
							if (IS_I_DEFINED(associativity))
							{
								sprintf_s(buffer2, _countof(buffer2), ", %d-way", associativity);
								strcat_s(buffer, _countof(buffer), buffer2);
							}
							if (IS_I_DEFINED(linesize))
							{
								sprintf_s(buffer2, _countof(buffer2), ", %d-byte line size", linesize);
								strcat_s(buffer, _countof(buffer), buffer2);
							}

							vAddItem(_T("L2 Unified Cache"), buffer, item++, !bClearList);
						}
					}

				//	L3 Cache
					if (max_level >= 3)
					{
						pSDK->GetProcessorCacheParameters(proc_id, 3, CACHE_TYPE_UNIFIED, &NbCaches, &CacheSize);
						if (CacheSize > 0)
						{
							if (NbCaches > 1)
								sprintf_s(buffer, _countof(buffer), "%d x %d KBytes", NbCaches, CacheSize);
							else
								sprintf_s(buffer, _countof(buffer), "%d KBytes", CacheSize);

							pSDK->GetProcessorExtendedCacheParameters(proc_id, 3, CACHE_TYPE_UNIFIED, &associativity, &linesize);
							if (IS_I_DEFINED(associativity))
							{
								sprintf_s(buffer2, _countof(buffer2), ", %d-way", associativity);
								strcat_s(buffer, _countof(buffer), buffer2);
							}
							if (IS_I_DEFINED(linesize))
							{
								sprintf_s(buffer2, _countof(buffer2), ", %d-byte line size", linesize);
								strcat_s(buffer, _countof(buffer), buffer2);
							}

							vAddItem(_T("L3 Unified Cache"), buffer, item++, !bClearList);
						}
					}
				}
			}
			break;

		case TREE_ITEM_CLASS_CORE:
			{
				proc_id = _pCPUTreeItem->iGetProcessorIndex();
				core_id = _pCPUTreeItem->iGetCoreIndex();
				item = 0;

			//	Core clock frequency
				fValue = pSDK->GetProcessorCoreClockFrequency(proc_id, core_id);
				if (IS_F_DEFINED(fValue))
				{
					sprintf_s(buffer, _countof(buffer), "%.1f MHz", fValue);
					vAddItem(_T("Core Speed"), buffer, item++, !bClearList);
				}

			//	Core clock multiplier
				fValue = pSDK->GetProcessorCoreClockMultiplier(proc_id, core_id);
				if (IS_F_DEFINED(fValue))
				{
					int coeff = (int)(100.0f * fValue);
					if (coeff % 10)
						sprintf_s(buffer, _countof(buffer), "x %.2f", fValue);
					else
						sprintf_s(buffer, _countof(buffer), "x %.1f", fValue);

					vAddItem(_T("Multiplier"), buffer, item++, !bClearList);
				}

			//	Bus frequency
				fValue = pSDK->GetBusFrequency();
				if (IS_F_DEFINED(fValue))
				{
					sprintf_s(buffer, _countof(buffer), "%.1f MHz", fValue);
					vAddItem(_T("Bus Speed"), buffer, item++, !bClearList);
				}

			//	Rated bus frequency
				fValue = pSDK->GetProcessorRatedBusFrequency(proc_id);
				if (IS_F_DEFINED(fValue))
				{
					sprintf_s(buffer, _countof(buffer), "%.1f MHz", fValue);
					vAddItem(_T("Rated Bus Speed"), buffer, item++, !bClearList);
				}

			//	Core temperature
				fValue = pSDK->GetProcessorCoreTemperature(proc_id, core_id);
				if (IS_F_DEFINED(fValue))
				{
					sprintf_s(buffer, _countof(buffer), "%d °C  (%d °F)", (int)fValue, (int)(1.8f * fValue + 32.0f));
					vAddItem(_T("Temperature"), buffer, item++, !bClearList);
				}
			}
			break;

		case TREE_ITEM_CLASS_THREAD:
			{
				proc_id = _pCPUTreeItem->iGetProcessorIndex();
				core_id = _pCPUTreeItem->iGetCoreIndex();
				thread_id = _pCPUTreeItem->iGetThreadIndex();
				item = 0;

			//	APIC ID
				iValue = pSDK->GetProcessorThreadAPICID(proc_id, core_id, thread_id);
				if (IS_I_DEFINED(iValue))
				{
					sprintf_s(buffer, _countof(buffer), "%d", iValue);
					vAddItem(_T("APIC ID"), buffer, item++, !bClearList);
				}
			}
			break;

		default:
			break;
	}
}