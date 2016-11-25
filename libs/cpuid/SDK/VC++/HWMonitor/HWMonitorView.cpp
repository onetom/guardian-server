// HWMonitorView.cpp : implementation of the CHWMonitorView class
//

#include "stdafx.h"
#include "CTList.h"
#include "cpuidsdk.h"
#include "CMonitor.h"
#include "HWMonitor.h"
#include "HWMonitorDoc.h"
#include "ColumnTreeCtrl.h"
#include "ColumnTreeView.h"
#include "HWMonitorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHWMonitorView

IMPLEMENT_DYNCREATE(CHWMonitorView, CColumnTreeView)

BEGIN_MESSAGE_MAP(CHWMonitorView, CColumnTreeView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_NOTIFY(NM_CUSTOMDRAW, TreeID, OnTreeCustomDraw)
	ON_COMMAND(ID_VIEW_CLEARMINMAX, &CHWMonitorView::OnViewClearminmax)
	ON_COMMAND(ID_FILE_SAVESMBUSDATA, &CHWMonitorView::OnFileSavesmbus)
END_MESSAGE_MAP()

// CHWMonitorView construction/destruction

CHWMonitorView::CHWMonitorView()
{
	// TODO: add construction code here
	m_pMonitorTreeItemListList = new tdMonitorTreeItemListList();
	m_pSelectedMonitor = NULL;
}

CHWMonitorView::~CHWMonitorView()
{
	if (m_pMonitorTreeItemListList)
	{
		m_pMonitorTreeItemListList->vDeleteAllItems();
		delete m_pMonitorTreeItemListList;
	}
}

BOOL CHWMonitorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CColumnTreeView::PreCreateWindow(cs);
}

// CHWMonitorView drawing

void CHWMonitorView::OnDraw(CDC* /*pDC*/)
{
	CHWMonitorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CHWMonitorView diagnostics

#ifdef _DEBUG
void CHWMonitorView::AssertValid() const
{
	CColumnTreeView::AssertValid();
}

void CHWMonitorView::Dump(CDumpContext& dc) const
{
	CColumnTreeView::Dump(dc);
}

CHWMonitorDoc* CHWMonitorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHWMonitorDoc)));
	return (CHWMonitorDoc*)m_pDocument;
}
#endif //_DEBUG


// CHWMonitorView message handlers

int CHWMonitorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CColumnTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here	
	return 0;
}

void CHWMonitorView::OnInitialUpdate()
{
	CColumnTreeView::OnInitialUpdate();

	CTreeCtrl& tree = GetTreeCtrl();
	CHeaderCtrl& header = GetHeaderCtrl();

	DWORD dwStyle = GetWindowLong(tree, GWL_STYLE);
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_FULLROWSELECT | TVS_DISABLEDRAGDROP;
	SetWindowLong(tree, GWL_STYLE, dwStyle);

	HDITEM hditem;
	hditem.mask = HDI_TEXT | HDI_WIDTH | HDI_FORMAT;
	hditem.fmt = HDF_LEFT | HDF_STRING;
	hditem.cxy = 230;
	hditem.pszText = _T("Sensor");
	header.InsertItem(0, &hditem);
	hditem.cxy = 87;
	hditem.pszText = _T("Value");
	header.InsertItem(1, &hditem);
	hditem.cxy = 87;
	hditem.pszText = _T("Min");
	header.InsertItem(2, &hditem);
	hditem.cxy = 87;
	hditem.pszText = _T("Max");
	header.InsertItem(3, &hditem);

	// Create the full-color image list
	// cx, cy = your icon width & height
	// You could also use ILC_COLOR24 rather than ILC_COLOR32
	m_ImgList.Create(16, 16, ILC_MASK | ILC_COLOR32, 0, 0);

	CBitmap bmp;
	bmp.LoadBitmap(IDB_ICONS);
	// Load your imagelist bitmap (bmp) here, however
	//   you feel like (e.g. CBitmap::LoadBitmap)

	// Add the bitmap into the image list
	m_ImgList.Add(&bmp, RGB(255, 255, 255));

	tree.SetImageList(&m_ImgList, TVSIL_NORMAL);

	UpdateColumns();	
}

void CHWMonitorView::OnDestroy()
{
	CColumnTreeView::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(0);
	m_ImgList.DeleteImageList();
	CTreeCtrl &tc = GetTreeCtrl();
	BOOL result = tc.DeleteAllItems();
}

void CHWMonitorView::OnTreeCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMCUSTOMDRAW* pNMCustomDraw = (NMCUSTOMDRAW*)pNMHDR;
	NMTVCUSTOMDRAW* pNMTVCustomDraw = (NMTVCUSTOMDRAW*)pNMHDR;

	switch (pNMCustomDraw->dwDrawStage)
	{
		case CDDS_PREPAINT:
			*pResult = CDRF_NOTIFYITEMDRAW;
			break;

		case CDDS_ITEMPREPAINT:
			*pResult = CDRF_DODEFAULT | CDRF_NOTIFYPOSTPAINT;
			break;

		case CDDS_ITEMPOSTPAINT:
			{
				HTREEITEM hItem = (HTREEITEM)pNMCustomDraw->dwItemSpec;
				CRect rcItem = pNMCustomDraw->rc;

				if (rcItem.IsRectEmpty())
				{
				//	Nothing to paint
					*pResult = CDRF_DODEFAULT;
					break;
				}

				CDC dc;
				dc.Attach(pNMCustomDraw->hdc);

				CRect rcLabel;
				m_Tree.GetItemRect(hItem, &rcLabel, TRUE);

				CRect rcTree;
				GetClientRect(rcTree);

				COLORREF crTextBk = GetSysColor(COLOR_WINDOW);
				unsigned int flag = uiFindFlag(hItem);
				if (flag & ITEM_FLAG_ALT_COLOR)
				{
					crTextBk = RGB(240, 240, 240);
				}

				COLORREF crText = GetSysColor(COLOR_WINDOWTEXT);
				COLORREF crWnd = GetSysColor(COLOR_WINDOW);

			//	Clear the original label rectangle
				CRect rcClear = rcLabel;
				if (rcClear.left > m_arrColWidths[0] - 1)
					rcClear.left = m_arrColWidths[0] - 1;
				dc.FillSolidRect(&rcClear, crWnd);

				int nColsCnt = m_Header.GetItemCount();
				int xOffset = 0;

				CString strText = m_Tree.GetItemText(hItem);
				CString strSub;
				AfxExtractSubString(strSub, strText, 0, '\t');

			//	Calculate main label's size
				CRect rcText(0, 0, 0, 0);
				dc.DrawText(strSub, &rcText, DT_NOPREFIX | DT_CALCRECT);
				rcLabel.right = min(rcLabel.left + rcText.right + 4, m_arrColWidths[0] - 4);

				CRect rcBack = rcLabel;
				if (GetWindowLong(m_Tree.m_hWnd, GWL_STYLE) & TVS_FULLROWSELECT)
				{
					rcBack.right = rcTree.right;

					if (rcBack.left > m_arrColWidths[0] - 1)
						rcBack.left = m_arrColWidths[0] - 1;
				}

				if (rcBack.Width() < 0)
					crTextBk = crWnd;

			//	Draw label's background
				if (crTextBk != crWnd)
					dc.FillSolidRect(&rcBack, crTextBk);

			//	Draw focus rectangle if necessary
				if (pNMCustomDraw->uItemState & CDIS_FOCUS)
					dc.DrawFocusRect(&rcBack);

			//	Draw main label
				rcText = rcLabel;
				rcText.DeflateRect(2, 1);
				dc.SetTextColor(crText);
				dc.DrawText(strSub, &rcText, DT_NOPREFIX | DT_END_ELLIPSIS);

				xOffset = m_arrColWidths[0];
				dc.SetBkMode(TRANSPARENT);

				if (!(GetWindowLong(m_Tree.m_hWnd, GWL_STYLE) & TVS_FULLROWSELECT))
				{
					dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
				}

			//	Draw other columns text
				for (int i=1; i<nColsCnt; i++)
				{
					if (AfxExtractSubString(strSub, strText, i, '\t'))
					{
						rcText = rcLabel;
						rcText.left = xOffset;
						rcText.right = xOffset + m_arrColWidths[i];
						rcText.DeflateRect(m_xOffset, 1, 2, 1);
						dc.DrawText(strSub, &rcText, DT_NOPREFIX | DT_END_ELLIPSIS);
					}
					xOffset += m_arrColWidths[i];
				}
				dc.Detach();

				*pResult = CDRF_DODEFAULT;
			}			
			break;

		default:
			*pResult = CDRF_DODEFAULT;
			break;
	}
}

void CHWMonitorView::OnViewClearminmax()
{
	theApp.vClearMinMax();
}

void CHWMonitorView::OnFileSavesmbus()
{
	TCHAR szCurrentDir[512];
	TCHAR oFilter[64] = _T("TXT File (*.txt)|All Files (*.*)|*.*||");
	CFileDialog	*oFD = NULL;
	CString oFileName;

	DWORD state = GetCurrentDirectory(512, szCurrentDir);

	oFD = new CFileDialog(FALSE,
						  NULL, 
						  _T("hwm_smbus.txt"),
						  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						  oFilter,
						  theApp.GetMainWnd());
	if (oFD)
	{
		if (oFD->DoModal() == IDOK)
		{
			oFileName = oFD->GetPathName();
			state = SetCurrentDirectory(szCurrentDir);

			CHWMonitorDoc *pDoc = GetDocument();
			pDoc->vSaveSMBusDump((LPCTSTR)oFileName);
		}
		delete oFD;
	}	
}

void CHWMonitorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
		case 0:
			vUpdateTree();
			break;

		default:
			break;
	}
	CColumnTreeView::OnTimer(nIDEvent);
}

void CHWMonitorView::vCreateTree()
{
	CTreeCtrl &tree = GetTreeCtrl();
	tree.DeleteAllItems();

	vUpdateTree(TRUE);

	tree.SetFocus();

	UINT_PTR timer0 = SetTimer(0, 1000, NULL);
}

#define	BITMAP_EMPTY						0

#define	BITMAP_DEVICE_MACHINE				1
#define	BITMAP_DEVICE_CHIP					2
#define	BITMAP_DEVICE_PROCESSOR				3
#define	BITMAP_DEVICE_DISPLAYADAPTER		4
#define	BITMAP_DEVICE_HDD					5
#define	BITMAP_DEVICE_PSU					6
#define	BITMAP_DEVICE_MEMORY				13
#define	BITMAP_DEVICE_CHASSIS				15
#define	BITMAP_DEVICE_WATERCOOLER			16
#define	BITMAP_DEVICE_BATTERY				21
#define	BITMAP_DEVICE_MAINBOARD				23

#define	BITMAP_SENSOR_VOLTAGE				7
#define	BITMAP_SENSOR_POWER					8
#define	BITMAP_SENSOR_FAN					9
#define	BITMAP_SENSOR_TEMPERATURE			10
#define	BITMAP_SENSOR_CURRENT				11
#define	BITMAP_SENSOR_CAPACITY				11
#define	BITMAP_SENSOR_CASEOPEN				15
#define	BITMAP_SENSOR_PUMP_PWM				17
#define	BITMAP_SENSOR_FAN_PWM				18
#define	BITMAP_SENSOR_POSITION				20
#define	BITMAP_SENSOR_LEVEL					22
#define	BITMAP_SENSOR_COUNTER				22
#define	BITMAP_SENSOR_UTILIZATION			24
#define	BITMAP_SENSOR_CLOCK_SPEED			25

HTREEITEM CHWMonitorView::hCreateLabelTreeItem(int _monitor_index,
											   int _device_index,
											   unsigned int _sensor_class,
											   HTREEITEM _parent,
											   CMonitorTreeItemList *_pMonitorTreeItemList)
{
	TCHAR buffer[512];
	CTreeCtrl &tree = GetTreeCtrl();
	HTREEITEM hItem = NULL;
	int nImage = BITMAP_EMPTY;

	CTreeItem *pTreeItem = pFindTreeItem(_monitor_index, _device_index, I_UNDEFINED_VALUE, _sensor_class, ITEM_FLAG_LABEL);
	if (!pTreeItem)
	{
		switch (_sensor_class)
		{
			case SENSOR_CLASS_VOLTAGE:
				SPRINTF(buffer, _countof(buffer), _T("Voltages"));
				nImage = BITMAP_SENSOR_VOLTAGE;
				break;

			case SENSOR_CLASS_TEMPERATURE:
				SPRINTF(buffer, _countof(buffer), _T("Temperatures"));
				nImage = BITMAP_SENSOR_TEMPERATURE;
				break;

			case SENSOR_CLASS_FAN:
				SPRINTF(buffer, _countof(buffer), _T("Fans"));
				nImage = BITMAP_SENSOR_FAN;
				break;

			case SENSOR_CLASS_CURRENT:
				SPRINTF(buffer, _countof(buffer), _T("Currents"));
				nImage = BITMAP_SENSOR_CURRENT;
				break;

			case SENSOR_CLASS_POWER:
				SPRINTF(buffer, _countof(buffer), _T("Powers"));
				nImage = BITMAP_SENSOR_POWER;
				break;

			case SENSOR_CLASS_FAN_PWM:
				SPRINTF(buffer, _countof(buffer), _T("Fans PWM"));
				nImage = BITMAP_SENSOR_FAN_PWM;
				break;

			case SENSOR_CLASS_PUMP_PWM:
				SPRINTF(buffer, _countof(buffer), _T("Pumps PWM"));
				nImage = BITMAP_SENSOR_PUMP_PWM;
				break;

			case SENSOR_CLASS_WATER_LEVEL:
				SPRINTF(buffer, _countof(buffer), _T("Water Levels"));
				nImage = BITMAP_EMPTY;
				break;

			case SENSOR_CLASS_POSITION:
				SPRINTF(buffer, _countof(buffer), _T("Positions"));
				nImage = BITMAP_SENSOR_POSITION;
				break;

			case SENSOR_CLASS_CAPACITY:
				SPRINTF(buffer, _countof(buffer), _T("Capacities"));
				nImage = BITMAP_SENSOR_CAPACITY;
				break;

			case SENSOR_CLASS_CASEOPEN:
				SPRINTF(buffer, _countof(buffer), _T("Case Open"));
				nImage = BITMAP_SENSOR_CASEOPEN;
				break;

			case SENSOR_CLASS_LEVEL:
				SPRINTF(buffer, _countof(buffer), _T("Levels"));
				nImage = BITMAP_SENSOR_LEVEL;
				break;

			case SENSOR_CLASS_COUNTER:
				SPRINTF(buffer, _countof(buffer), _T("Counters"));
				nImage = BITMAP_SENSOR_COUNTER;
				break;

			case SENSOR_CLASS_UTILIZATION:
				SPRINTF(buffer, _countof(buffer), _T("Utilizations"));
				nImage = BITMAP_SENSOR_UTILIZATION;
				break;

			case SENSOR_CLASS_CLOCK_SPEED:
				SPRINTF(buffer, _countof(buffer), _T("Clocks"));
				nImage = BITMAP_SENSOR_CLOCK_SPEED;
				break;

			default:
				SPRINTF(buffer, _countof(buffer), _T("Sensor class %X"), _sensor_class);
				break;
		}

		hItem = tree.InsertItem(buffer, nImage, nImage, _parent);
		pTreeItem = new CTreeItem(_monitor_index, _device_index, I_UNDEFINED_VALUE, _sensor_class, hItem);
		pTreeItem->m_uiFlag |= ITEM_FLAG_LABEL;
		_pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
	}
	else
	{
		hItem = pTreeItem->m_hItem;
	}
	return hItem;
}

int CHWMonitorView::iCountTreeItems(HTREEITEM hItem, BOOL _bRecurse)
{
	CTreeCtrl &tree = GetTreeCtrl();

	int Count = 0;
	if (tree.ItemHasChildren(hItem))
	{
		hItem = tree.GetNextItem(hItem, TVGN_CHILD);
		while (hItem)
		{
			Count++;
			if (_bRecurse)
			{
				Count += iCountTreeItems(hItem, _bRecurse);
			}
			hItem = tree.GetNextItem(hItem, TVGN_NEXT);
		}
	}
	return Count;
}

void CHWMonitorView::vDeleteTreeItems(int _monitor_index, int _device_index, unsigned int _sensor_class)
{
	BOOL result;

	CMonitorTreeItemList *pMonitorTreeItemList = pGetMonitorTreeItemList(_monitor_index);
	CTreeCtrl &tree = GetTreeCtrl();

	int nbsensors = pMonitorTreeItemList->iGetNumberOfSensor(_device_index, _sensor_class);
	while (nbsensors > 0)
	{
		tdTreeItemListParser itemparser(pMonitorTreeItemList->m_pTreeItemList);
		CTreeItem *pItem = itemparser.pGetRoot();
		while (pItem)
		{
			if  ((pItem->m_iDeviceIndex == _device_index) &&
				 ((pItem->m_uiSensorID & SENSOR_CLASS_MASK) == _sensor_class) &&
				 (pItem->m_iSensorIndex != I_UNDEFINED_VALUE))
			{
				if (pItem->m_hItem)
					result = tree.DeleteItem(pItem->m_hItem);

				pMonitorTreeItemList->m_pTreeItemList->vRemoveItem(pItem);
				delete pItem;				
				nbsensors--;
				break;
			}
			pItem = itemparser.pGetNext();
		}
	}
}

int round_to_nearest_int(float f)
{
#if defined (_M_IX86)
	const float round_to_nearest = 0.5f;
	int i;
	_asm{
		fld f
		fadd st,st(0)
		fadd round_to_nearest
		fistp i
		sar i,1
	}
	return i;
#else
	if (f < 0.0f)
		return (int)f;
	else
		return (int)(f + 0.5f);
#endif
}

void CHWMonitorView::vUpdateTree(BOOL _bExpand)
{
	TCHAR					buffer[512];
	char					szName[512];
	CMonitorTreeItemList	*pMonitorTreeItemList;
	CTreeItem				*pTreeItem;
	HTREEITEM				hRoot, hdev, htemperature, hvoltage, hfan, hfanpwm, hpower, hcurrent, 
						    hcapacity, hlevel, hposition, hcaseopen, hcounter, hclock, hutilization;
	unsigned int			raw_value, sensor_id, flags;
	float					fValue, fMinValue, fMaxValue;
	int						device_index, picture_index, monitor_index, sensor_index, nbsensors, item_color, nbitems;
	BOOL					result, expand2;

	CTreeCtrl &tree = GetTreeCtrl();
	
	DWORD error = WaitForSingleObject(CHWMonitorApp::m_hTMutex, 20);
	switch (error)
	{
		case WAIT_OBJECT_0:
			{
				monitor_index = 0;
				tdMonitorListParser MonitorListParser = theApp.pGetMonitorList();
				CMonitor *pMonitor = MonitorListParser.pGetRoot();
				while (pMonitor)
				{
					pMonitorTreeItemList = pGetMonitorTreeItemList(monitor_index);
					if (!pMonitorTreeItemList)
					{
						pMonitorTreeItemList = new CMonitorTreeItemList(monitor_index);
						m_pMonitorTreeItemListList->vAddItem(pMonitorTreeItemList);
					}

					pTreeItem = pFindTreeItem(monitor_index, I_UNDEFINED_VALUE, I_UNDEFINED_VALUE, I_UNDEFINED_VALUE, ITEM_FLAG_LABEL);
					if (!pTreeItem)
					{
					#ifdef _UNICODE
						TCHAR szTemp[512];
						int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED,
														pMonitor->m_szName,
														-1, szTemp, 512);
					#else
						TCHAR *szTemp = pMonitor->m_szName;
					#endif

						picture_index = BITMAP_DEVICE_MACHINE;
						SPRINTF(buffer, _countof(buffer), szTemp);
						hRoot = tree.InsertItem(buffer, picture_index, picture_index, TVI_ROOT);

						pTreeItem = new CTreeItem(monitor_index, I_UNDEFINED_VALUE, I_UNDEFINED_VALUE, I_UNDEFINED_VALUE, hRoot);
						pTreeItem->m_uiFlag |= ITEM_FLAG_LABEL;
						pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
					}
					else
					{
						hRoot = pTreeItem->m_hItem;
					}

				//	Get devices list
					for (device_index = 0; device_index < pMonitor->iGetNumberOfDevices(); device_index++ )
					{
						nbsensors = pMonitor->iGetNumberOfSensors(device_index, I_UNDEFINED_VALUE);
						if (nbsensors > 0)
						{
							pTreeItem = pFindTreeItem(monitor_index, device_index, I_UNDEFINED_VALUE, I_UNDEFINED_VALUE, ITEM_FLAG_LABEL);
							if (!pTreeItem)
							{
								picture_index = BITMAP_EMPTY;
								unsigned int dev_class = pMonitor->uiGetDeviceClass(device_index);
								switch (dev_class)
								{
									case CLASS_DEVICE_MAINBOARD:		picture_index = BITMAP_DEVICE_MAINBOARD; break;
									case CLASS_DEVICE_PROCESSOR:		picture_index = BITMAP_DEVICE_PROCESSOR; break;
									case CLASS_DEVICE_DRIVE:			picture_index = BITMAP_DEVICE_HDD; break;
									case CLASS_DEVICE_DISPLAY_ADAPTER:	picture_index = BITMAP_DEVICE_DISPLAYADAPTER; break;
									case CLASS_DEVICE_BATTERY:			picture_index = BITMAP_DEVICE_BATTERY; break;
									case CLASS_DEVICE_MEMORY_MODULE:	picture_index = BITMAP_DEVICE_MEMORY; break;
									case CLASS_DEVICE_PSU:				picture_index = BITMAP_DEVICE_PSU; break;
									case CLASS_DEVICE_WATERCOOLER:		picture_index = BITMAP_DEVICE_WATERCOOLER; break;
									default: break;
								}

								TCHAR szTemp[512];
								if (pMonitor->bGetDeviceName(device_index, szName))
								{
								#ifdef _UNICODE
									int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED,
																	szName,
																	-1, szTemp, 512);
								#else
									strcpy_s(szTemp, szName);
								#endif
								}
								else
								{
									SPRINTF(szTemp, _countof(szTemp), _T("Device %d"), device_index);
								}

								SPRINTF(buffer, _countof(buffer), _T("%s"), szTemp);
								hdev = tree.InsertItem(buffer, picture_index, picture_index, hRoot);

								pTreeItem = new CTreeItem(monitor_index, device_index, I_UNDEFINED_VALUE, I_UNDEFINED_VALUE, hdev);
								pTreeItem->m_uiFlag |= ITEM_FLAG_LABEL;
								pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
							}
							else
							{
								hdev = pTreeItem->m_hItem;
							}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

						//	Voltages
							nbsensors = pMonitor->iGetNumberOfSensors(device_index, SENSOR_CLASS_VOLTAGE);
							if (nbsensors > 0)
							{
								expand2 = FALSE;
								hvoltage = hCreateLabelTreeItem(monitor_index, device_index, SENSOR_CLASS_VOLTAGE, hdev, pMonitorTreeItemList);
								nbitems = iCountTreeItems(hvoltage, FALSE);
								if ((nbitems != nbsensors) && (!_bExpand))
								{
									vDeleteTreeItems(monitor_index, device_index, SENSOR_CLASS_VOLTAGE);
									expand2 = TRUE;
								}
								item_color = ITEM_FLAG_ALT_COLOR;

								for (sensor_index = 0; sensor_index < nbsensors; sensor_index++ )
								{
									if (pMonitor->bGetSensorInfos(device_index, sensor_index,
																  SENSOR_CLASS_VOLTAGE,
																  &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue, &flags))
									{
										if (fValue > -MAX_FLOAT)
										{
									#ifdef _UNICODE
											TCHAR szTemp[512];
											int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
									#else
											TCHAR *szTemp = szName;
									#endif
											pTreeItem = pFindTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_VOLTAGE, 0);
											if (!pTreeItem)
											{
												HTREEITEM hsensor = tree.InsertItem(szTemp, BITMAP_EMPTY, BITMAP_EMPTY, hvoltage);
												pTreeItem = new CTreeItem(monitor_index, device_index, sensor_index, sensor_id, hsensor);

												pTreeItem->m_uiFlag = 0;												

												//if (!(sensor_index % 2))
												//	pTreeItem->m_uiFlag |= ITEM_FLAG_ALT_COLOR;

												pTreeItem->m_uiFlag |= item_color;
												item_color = ITEM_FLAG_ALT_COLOR - item_color;

												pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
											}

											if (fMinValue < MAX_FLOAT)
												SPRINTF(buffer, _countof(buffer), _T("%s\t%.3f V\t%.3f V\t%.3f V"), szTemp, fValue, fMinValue, fMaxValue);
											else
												SPRINTF(buffer, _countof(buffer), _T("%s\t%.3f V"), szTemp, fValue);

											if (pTreeItem->m_hItem)
												tree.SetItemText(pTreeItem->m_hItem, buffer);
										}
									}
								}
								if (_bExpand || expand2)
								{
									result = tree.Expand(hvoltage, TVE_EXPAND);
								}
							}

						//	Temperatures
							nbsensors = pMonitor->iGetNumberOfSensors(device_index, SENSOR_CLASS_TEMPERATURE);
							if (nbsensors > 0)
							{
								expand2 = FALSE;
								htemperature = hCreateLabelTreeItem(monitor_index, device_index, SENSOR_CLASS_TEMPERATURE, hdev, pMonitorTreeItemList);
								nbitems = iCountTreeItems(htemperature, FALSE);
								if ((nbitems != nbsensors) && (!_bExpand))
								{
									vDeleteTreeItems(monitor_index, device_index, SENSOR_CLASS_TEMPERATURE);
									expand2 = TRUE;
								}
								item_color = ITEM_FLAG_ALT_COLOR;

								for (sensor_index = 0; sensor_index < nbsensors; sensor_index++ )
								{
									if (pMonitor->bGetSensorInfos(device_index, sensor_index,
																  SENSOR_CLASS_TEMPERATURE,
																  &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue, &flags))
									{
										if (fValue > -MAX_FLOAT)
										{
									#ifdef _UNICODE
											TCHAR szTemp[512];
											int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
									#else
											TCHAR *szTemp = szName;
									#endif
											pTreeItem = pFindTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_TEMPERATURE, 0);
											if (!pTreeItem)
											{
												HTREEITEM hsensor = tree.InsertItem(szTemp, BITMAP_EMPTY, BITMAP_EMPTY, htemperature);
												pTreeItem = new CTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_TEMPERATURE, hsensor);

												pTreeItem->m_uiFlag = 0;

												//if (!(sensor_index % 2))
												//	pTreeItem->m_uiFlag |= ITEM_FLAG_ALT_COLOR;

												pTreeItem->m_uiFlag |= item_color;
												item_color = ITEM_FLAG_ALT_COLOR - item_color;

												pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
											}

											if (fMinValue < MAX_FLOAT)
											{
												SPRINTF(buffer,
														_countof(buffer),
														_T("%s\t%d °C  (%d °F)\t%d °C  (%d °F)\t%d °C  (%d °F)"),
														szTemp,
														(int)(fValue + 0.5f),
														(int)(1.8f * fValue + 32.0f),
														(int)(fMinValue + 0.5f),
														(int)(1.8f * fMinValue + 32.0f),
														(int)(fMaxValue + 0.5f),
														(int)(1.8f * fMaxValue + 32.0f));
											}
											else
											{
												SPRINTF(buffer,
														_countof(buffer),
														_T("%s\t%d °C  (%d °F)"),
														szTemp,
														(int)(fValue + 0.5f),
														(int)(1.8f * fValue + 32.0f));
											}

											if (pTreeItem->m_hItem)
												tree.SetItemText(pTreeItem->m_hItem, buffer);
										}
									}
								}
								if (_bExpand || expand2)
								{
									result = tree.Expand(htemperature, TVE_EXPAND);
								}
							}

						//	Fans
							nbsensors = pMonitor->iGetNumberOfSensors(device_index, SENSOR_CLASS_FAN);
							if (nbsensors > 0)
							{
								expand2 = FALSE;
								hfan = hCreateLabelTreeItem(monitor_index, device_index, SENSOR_CLASS_FAN, hdev, pMonitorTreeItemList);
								nbitems = iCountTreeItems(hfan, FALSE);
								if ((nbitems != nbsensors) && (!_bExpand))
								{
									vDeleteTreeItems(monitor_index, device_index, SENSOR_CLASS_FAN);
									expand2 = TRUE;
								}
								item_color = ITEM_FLAG_ALT_COLOR;

								for (sensor_index = 0; sensor_index < nbsensors; sensor_index++ )
								{
									if (pMonitor->bGetSensorInfos(device_index, sensor_index,
																  SENSOR_CLASS_FAN,
																  &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue, &flags))
									{
										if (round_to_nearest_int(fValue) >= 0)
										{
									#ifdef _UNICODE
											TCHAR szTemp[512];
											int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
									#else
											TCHAR *szTemp = szName;
									#endif
											pTreeItem = pFindTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_FAN, 0);
											if (!pTreeItem)
											{
												HTREEITEM hsensor = tree.InsertItem(szTemp, BITMAP_EMPTY, BITMAP_EMPTY, hfan);
												pTreeItem = new CTreeItem(monitor_index, device_index, sensor_index, sensor_id, hsensor);

												pTreeItem->m_uiFlag = 0;

												//if (!(sensor_index % 2))
												//	pTreeItem->m_uiFlag |= ITEM_FLAG_ALT_COLOR;

												pTreeItem->m_uiFlag |= item_color;
												item_color = ITEM_FLAG_ALT_COLOR - item_color;

												pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
											}

											if (fMinValue < MAX_FLOAT)
												SPRINTF(buffer, _countof(buffer), _T("%s\t%d RPM\t%d RPM\t%d RPM"), szTemp, (int)fValue, (int)fMinValue, (int)fMaxValue);
											else
												SPRINTF(buffer, _countof(buffer), _T("%s\t%d RPM"), szTemp, (int)fValue);

											if (pTreeItem->m_hItem)
												tree.SetItemText(pTreeItem->m_hItem, buffer);
										}
									}
								}
								if (_bExpand || expand2)
								{
									result = tree.Expand(hfan, TVE_EXPAND);
								}
							}

						//	Fan PWMs
							nbsensors = pMonitor->iGetNumberOfSensors(device_index, SENSOR_CLASS_FAN_PWM);
							if (nbsensors > 0)
							{
								expand2 = FALSE;
								hfanpwm = hCreateLabelTreeItem(monitor_index, device_index, SENSOR_CLASS_FAN_PWM, hdev, pMonitorTreeItemList);
								nbitems = iCountTreeItems(hfanpwm, FALSE);
								if ((nbitems != nbsensors) && (!_bExpand))
								{
									vDeleteTreeItems(monitor_index, device_index, SENSOR_CLASS_FAN_PWM);
									expand2 = TRUE;
								}
								item_color = ITEM_FLAG_ALT_COLOR;

								for (sensor_index = 0; sensor_index < nbsensors; sensor_index++ )
								{
									if (pMonitor->bGetSensorInfos(device_index, sensor_index,
																  SENSOR_CLASS_FAN_PWM,
																  &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue, &flags))
									{
										if (round_to_nearest_int(fValue) >= 0)
										{
									#ifdef _UNICODE
											TCHAR szTemp[512];
											int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
									#else
											TCHAR *szTemp = szName;
									#endif
											pTreeItem = pFindTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_FAN_PWM, 0);
											if (!pTreeItem)
											{
												HTREEITEM hsensor = tree.InsertItem(szTemp, BITMAP_EMPTY, BITMAP_EMPTY, hfanpwm);
												pTreeItem = new CTreeItem(monitor_index, device_index, sensor_index, sensor_id, hsensor);

												pTreeItem->m_uiFlag = 0;

												//if (!(sensor_index % 2))
												//	pTreeItem->m_uiFlag |= ITEM_FLAG_ALT_COLOR;

												pTreeItem->m_uiFlag |= item_color;
												item_color = ITEM_FLAG_ALT_COLOR - item_color;

												pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
											}

											if (fMinValue < MAX_FLOAT)
												SPRINTF(buffer, _countof(buffer), _T("%s\t%d %%\t%d %%\t%d %%"), szTemp, (int)fValue, (int)fMinValue, (int)fMaxValue);
											else
												SPRINTF(buffer, _countof(buffer), _T("%s\t%d %%"), szTemp, (int)fValue);

											if (pTreeItem->m_hItem)
												tree.SetItemText(pTreeItem->m_hItem, buffer);
										}
									}
								}
								if (_bExpand || expand2)
								{
									result = tree.Expand(hfanpwm, TVE_EXPAND);
								}
							}

						//	Powers
							nbsensors = pMonitor->iGetNumberOfSensors(device_index, SENSOR_CLASS_POWER);
							if (nbsensors > 0)
							{
								expand2 = FALSE;
								hpower = hCreateLabelTreeItem(monitor_index, device_index, SENSOR_CLASS_POWER, hdev, pMonitorTreeItemList);
								nbitems = iCountTreeItems(hpower, FALSE);
								if ((nbitems != nbsensors) && (!_bExpand))
								{
									vDeleteTreeItems(monitor_index, device_index, SENSOR_CLASS_POWER);
									expand2 = TRUE;
								}
								item_color = ITEM_FLAG_ALT_COLOR;

								for ( sensor_index = 0; sensor_index < nbsensors; sensor_index++ )
								{
									if (pMonitor->bGetSensorInfos(device_index, sensor_index,
																  SENSOR_CLASS_POWER,
																  &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue, &flags))
									{
										if (round_to_nearest_int(fValue) >= 0)
										{
									#ifdef _UNICODE
											TCHAR szTemp[512];
											int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
									#else
											TCHAR *szTemp = szName;
									#endif
											pTreeItem = pFindTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_POWER, 0);
											if (!pTreeItem)
											{
												HTREEITEM hsensor = tree.InsertItem(szTemp, BITMAP_EMPTY, BITMAP_EMPTY, hpower);
												pTreeItem = new CTreeItem(monitor_index, device_index, sensor_index, sensor_id, hsensor);

												pTreeItem->m_uiFlag = 0;

												//if (!(sensor_index % 2))
												//	pTreeItem->m_uiFlag |= ITEM_FLAG_ALT_COLOR;

												pTreeItem->m_uiFlag |= item_color;
												item_color = ITEM_FLAG_ALT_COLOR - item_color;

												pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
											}

											if (fMinValue < MAX_FLOAT)
												SPRINTF(buffer, _countof(buffer), _T("%s\t%.2f W\t%.2f W\t%.2f W"), szTemp, fValue, fMinValue, fMaxValue);
											else
												SPRINTF(buffer, _countof(buffer), _T("%s\t%.2f W"), szTemp, fValue);

											if (pTreeItem->m_hItem)
												tree.SetItemText(pTreeItem->m_hItem, buffer);
										}
									}
								}
								if (_bExpand || expand2)
								{
									result = tree.Expand(hpower, TVE_EXPAND);
								}
							}

						//	Currents
							nbsensors = pMonitor->iGetNumberOfSensors(device_index, SENSOR_CLASS_CURRENT);
							if (nbsensors > 0)
							{
								expand2 = FALSE;
								hcurrent = hCreateLabelTreeItem(monitor_index, device_index, SENSOR_CLASS_CURRENT, hdev, pMonitorTreeItemList);
								nbitems = iCountTreeItems(hcurrent, FALSE);
								if ((nbitems != nbsensors) && (!_bExpand))
								{
									vDeleteTreeItems(monitor_index, device_index, SENSOR_CLASS_CURRENT);
									expand2 = TRUE;
								}
								item_color = ITEM_FLAG_ALT_COLOR;

								for ( sensor_index = 0; sensor_index < nbsensors; sensor_index++ )
								{
									if (pMonitor->bGetSensorInfos(device_index, sensor_index,
																  SENSOR_CLASS_CURRENT,
																  &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue, &flags))
									{
										if (round_to_nearest_int(fValue) >= 0)
										{
									#ifdef _UNICODE
											TCHAR szTemp[512];
											int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
									#else
											TCHAR *szTemp = szName;
									#endif
											pTreeItem = pFindTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_CURRENT, 0);
											if (!pTreeItem)
											{
												HTREEITEM hsensor = tree.InsertItem(szTemp, BITMAP_EMPTY, BITMAP_EMPTY, hcurrent);
												pTreeItem = new CTreeItem(monitor_index, device_index, sensor_index, sensor_id, hsensor);

												pTreeItem->m_uiFlag = 0;

												//if (!(sensor_index % 2))
												//	pTreeItem->m_uiFlag |= ITEM_FLAG_ALT_COLOR;

												pTreeItem->m_uiFlag |= item_color;
												item_color = ITEM_FLAG_ALT_COLOR - item_color;

												pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
											}

											if (fMinValue < MAX_FLOAT)
												SPRINTF(buffer, _countof(buffer), _T("%s\t%.2f A\t%.2f A\t%.2f A"), szTemp, fValue, fMinValue, fMaxValue);
											else
												SPRINTF(buffer, _countof(buffer), _T("%s\t%.2f A"), szTemp, fValue);

											if (pTreeItem->m_hItem)
												tree.SetItemText(pTreeItem->m_hItem, buffer);
										}
									}
								}
								if (_bExpand || expand2)
								{
									result = tree.Expand(hcurrent, TVE_EXPAND);
								}
							}

						//	Capacities
							nbsensors = pMonitor->iGetNumberOfSensors(device_index, SENSOR_CLASS_CAPACITY);
							if (nbsensors > 0)
							{
								expand2 = FALSE;
								hcapacity = hCreateLabelTreeItem(monitor_index, device_index, SENSOR_CLASS_CAPACITY, hdev, pMonitorTreeItemList);
								nbitems = iCountTreeItems(hcapacity, FALSE);
								if ((nbitems != nbsensors) && (!_bExpand))
								{
									vDeleteTreeItems(monitor_index, device_index, SENSOR_CLASS_CAPACITY);
									expand2 = TRUE;
								}
								item_color = ITEM_FLAG_ALT_COLOR;

								for ( sensor_index = 0; sensor_index < nbsensors; sensor_index++ )
								{
									if (pMonitor->bGetSensorInfos(device_index, sensor_index,
																  SENSOR_CLASS_CAPACITY,
																  &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue, &flags))
									{
										if (round_to_nearest_int(fValue) >= 0)
										{
									#ifdef _UNICODE
											TCHAR szTemp[512];
											int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
									#else
											TCHAR *szTemp = szName;
									#endif
											pTreeItem = pFindTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_CAPACITY, 0);
											if (!pTreeItem)
											{
												HTREEITEM hsensor = tree.InsertItem(szTemp, BITMAP_EMPTY, BITMAP_EMPTY, hcapacity);
												pTreeItem = new CTreeItem(monitor_index, device_index, sensor_index, sensor_id, hsensor);

												pTreeItem->m_uiFlag = 0;

												//if (!(sensor_index % 2))
												//	pTreeItem->m_uiFlag |= ITEM_FLAG_ALT_COLOR;

												pTreeItem->m_uiFlag |= item_color;
												item_color = ITEM_FLAG_ALT_COLOR - item_color;

												pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
											}

											if (fMinValue < MAX_FLOAT)
												SPRINTF(buffer, _countof(buffer), _T("%s\t%.0f mWh\t%.0f mWh\t%.0f mWh"), szTemp, fValue, fMinValue, fMaxValue);
											else
												SPRINTF(buffer, _countof(buffer), _T("%s\t%.0f mWh"), szTemp, fValue);

											if (pTreeItem->m_hItem)
												tree.SetItemText(pTreeItem->m_hItem, buffer);
										}
									}
								}
								if (_bExpand || expand2)
								{
									result = tree.Expand(hcapacity, TVE_EXPAND);
								}
							}

						//	Levels
							nbsensors = pMonitor->iGetNumberOfSensors(device_index, SENSOR_CLASS_LEVEL);
							if (nbsensors > 0)
							{
								expand2 = FALSE;
								hlevel = hCreateLabelTreeItem(monitor_index, device_index, SENSOR_CLASS_LEVEL, hdev, pMonitorTreeItemList);
								nbitems = iCountTreeItems(hlevel, FALSE);
								if ((nbitems != nbsensors) && (!_bExpand))
								{
									vDeleteTreeItems(monitor_index, device_index, SENSOR_CLASS_LEVEL);
									expand2 = TRUE;
								}
								item_color = ITEM_FLAG_ALT_COLOR;

								for ( sensor_index = 0; sensor_index < nbsensors; sensor_index++ )
								{
									if (pMonitor->bGetSensorInfos(device_index, sensor_index,
																  SENSOR_CLASS_LEVEL,
																  &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue, &flags))
									{
										//if (round_to_nearest_int(fValue) >= 0)
										{
									#ifdef _UNICODE
											TCHAR szTemp[512];
											int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
									#else
											TCHAR *szTemp = szName;
									#endif
											pTreeItem = pFindTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_LEVEL, 0);
											if (!pTreeItem)
											{
												HTREEITEM hsensor = tree.InsertItem(szTemp, BITMAP_EMPTY, BITMAP_EMPTY, hlevel);
												pTreeItem = new CTreeItem(monitor_index, device_index, sensor_index, sensor_id, hsensor);

												pTreeItem->m_uiFlag = 0;

												//if (!(sensor_index % 2))
												//	pTreeItem->m_uiFlag |= ITEM_FLAG_ALT_COLOR;

												pTreeItem->m_uiFlag |= item_color;
												item_color = ITEM_FLAG_ALT_COLOR - item_color;

												pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
											}

											if (fMinValue < MAX_FLOAT)
												SPRINTF(buffer, _countof(buffer), _T("%s\t%d %%\t%d %%\t%d %%"), szTemp, (int)fValue, (int)fMinValue, (int)fMaxValue);
											else
												SPRINTF(buffer, _countof(buffer), _T("%s\t%d %%"), szTemp, (int)fValue);

											if (pTreeItem->m_hItem)
												tree.SetItemText(pTreeItem->m_hItem, buffer);
										}
									}
								}
								if (_bExpand || expand2)
								{
									result = tree.Expand(hlevel, TVE_EXPAND);
								}
							}

						//	Positions
							nbsensors = pMonitor->iGetNumberOfSensors(device_index, SENSOR_CLASS_POSITION);
							if (nbsensors > 0)
							{
								expand2 = FALSE;
								hposition = hCreateLabelTreeItem(monitor_index, device_index, SENSOR_CLASS_POSITION, hdev, pMonitorTreeItemList);
								nbitems = iCountTreeItems(hposition, FALSE);
								if ((nbitems != nbsensors) && (!_bExpand))
								{
									vDeleteTreeItems(monitor_index, device_index, SENSOR_CLASS_POSITION);
									expand2 = TRUE;
								}
								item_color = ITEM_FLAG_ALT_COLOR;

								for ( sensor_index = 0; sensor_index < nbsensors; sensor_index++ )
								{
									if (pMonitor->bGetSensorInfos(device_index, sensor_index,
																  SENSOR_CLASS_POSITION,
																  &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue, &flags))
									{
										//if (round_to_nearest_int(fValue) >= 0)
										{
									#ifdef _UNICODE
											TCHAR szTemp[512];
											int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
									#else
											TCHAR *szTemp = szName;
									#endif
											pTreeItem = pFindTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_POSITION, 0);
											if (!pTreeItem)
											{
												HTREEITEM hsensor = tree.InsertItem(szTemp, BITMAP_EMPTY, BITMAP_EMPTY, hposition);
												pTreeItem = new CTreeItem(monitor_index, device_index, sensor_index, sensor_id, hsensor);

												pTreeItem->m_uiFlag = 0;

												//if (!(sensor_index % 2))
												//	pTreeItem->m_uiFlag |= ITEM_FLAG_ALT_COLOR;

												pTreeItem->m_uiFlag |= item_color;
												item_color = ITEM_FLAG_ALT_COLOR - item_color;

												pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
											}

											if (fMinValue < MAX_FLOAT)
												SPRINTF(buffer, _countof(buffer), _T("%s\t%d\t%d\t%d"), szTemp, (int)fValue, (int)fMinValue, (int)fMaxValue);
											else
												SPRINTF(buffer, _countof(buffer), _T("%s\t%d"), szTemp, (int)fValue);

											if (pTreeItem->m_hItem)
												tree.SetItemText(pTreeItem->m_hItem, buffer);
										}
									}
								}
								if (_bExpand || expand2)
								{
									result = tree.Expand(hposition, TVE_EXPAND);
								}
							}

						//	Case open
							nbsensors = pMonitor->iGetNumberOfSensors(device_index, SENSOR_CLASS_CASEOPEN);
							if (nbsensors > 0)
							{
								expand2 = FALSE;
								hcaseopen = hCreateLabelTreeItem(monitor_index, device_index, SENSOR_CLASS_CASEOPEN, hdev, pMonitorTreeItemList);
								nbitems = iCountTreeItems(hcaseopen, FALSE);
								if ((nbitems != nbsensors) && (!_bExpand))
								{
									vDeleteTreeItems(monitor_index, device_index, SENSOR_CLASS_CASEOPEN);
									expand2 = TRUE;
								}
								item_color = ITEM_FLAG_ALT_COLOR;

								for ( sensor_index = 0; sensor_index < nbsensors; sensor_index++ )
								{
									if (pMonitor->bGetSensorInfos(device_index, sensor_index,
																  SENSOR_CLASS_CASEOPEN,
																  &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue, &flags))
									{
								#ifdef _UNICODE
										TCHAR szTemp[512];
										int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
								#else
										TCHAR *szTemp = szName;
								#endif
										pTreeItem = pFindTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_CASEOPEN, 0);
										if (!pTreeItem)
										{
											HTREEITEM hsensor = tree.InsertItem(szTemp, BITMAP_EMPTY, BITMAP_EMPTY, hcaseopen);
											pTreeItem = new CTreeItem(monitor_index, device_index, sensor_index, sensor_id, hsensor);

											pTreeItem->m_uiFlag = 0;

											//if (!(sensor_index % 2))
											//	pTreeItem->m_uiFlag |= ITEM_FLAG_ALT_COLOR;

											pTreeItem->m_uiFlag |= item_color;
											item_color = ITEM_FLAG_ALT_COLOR - item_color;

											pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
										}

										SPRINTF(buffer, _countof(buffer), _T("%s\t%d"), szTemp, raw_value);

										if (pTreeItem->m_hItem)
											tree.SetItemText(pTreeItem->m_hItem, buffer);
									}
								}
								if (_bExpand || expand2)
								{
									result = tree.Expand(hcaseopen, TVE_EXPAND);
								}
							}

						//	Counters
							nbsensors = pMonitor->iGetNumberOfSensors(device_index, SENSOR_CLASS_COUNTER);
							if (nbsensors > 0)
							{
								expand2 = FALSE;
								hcounter = hCreateLabelTreeItem(monitor_index, device_index, SENSOR_CLASS_COUNTER, hdev, pMonitorTreeItemList);
								nbitems = iCountTreeItems(hcounter, FALSE);
								if ((nbitems != nbsensors) && (!_bExpand))
								{
									vDeleteTreeItems(monitor_index, device_index, SENSOR_CLASS_COUNTER);
									expand2 = TRUE;
								}
								item_color = ITEM_FLAG_ALT_COLOR;

								for ( sensor_index = 0; sensor_index < nbsensors; sensor_index++ )
								{
									if (pMonitor->bGetSensorInfos(device_index, sensor_index,
																  SENSOR_CLASS_COUNTER,
																  &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue, &flags))
									{
										//if (round_to_nearest_int(fValue) >= 0)
										{
									#ifdef _UNICODE
											TCHAR szTemp[512];
											int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
									#else
											TCHAR *szTemp = szName;
									#endif
											pTreeItem = pFindTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_COUNTER, 0);
											if (!pTreeItem)
											{
												HTREEITEM hsensor = tree.InsertItem(szTemp, BITMAP_EMPTY, BITMAP_EMPTY, hcounter);
												pTreeItem = new CTreeItem(monitor_index, device_index, sensor_index, sensor_id, hsensor);

												pTreeItem->m_uiFlag = 0;

												//if (!(sensor_index % 2))
												//	pTreeItem->m_uiFlag |= ITEM_FLAG_ALT_COLOR;

												pTreeItem->m_uiFlag |= item_color;
												item_color = ITEM_FLAG_ALT_COLOR - item_color;

												pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
											}

											SPRINTF(buffer, _countof(buffer), _T("%s\t%d"), szTemp, raw_value);

											if (pTreeItem->m_hItem)
												tree.SetItemText(pTreeItem->m_hItem, buffer);
										}
									}
								}
								if (_bExpand || expand2)
								{
									result = tree.Expand(hcounter, TVE_EXPAND);
								}
							}

						//	Clocks
							nbsensors = pMonitor->iGetNumberOfSensors(device_index, SENSOR_CLASS_CLOCK_SPEED);
							if (nbsensors > 0)
							{
								expand2 = FALSE;
								hclock = hCreateLabelTreeItem(monitor_index, device_index, SENSOR_CLASS_CLOCK_SPEED, hdev, pMonitorTreeItemList);								
								nbitems = iCountTreeItems(hclock, FALSE);
								if ((nbitems != nbsensors) && (!_bExpand))
								{
									vDeleteTreeItems(monitor_index, device_index, SENSOR_CLASS_CLOCK_SPEED);
									expand2 = TRUE;
								}
								item_color = ITEM_FLAG_ALT_COLOR;

								for ( sensor_index = 0; sensor_index < nbsensors; sensor_index++ )
								{
									if (pMonitor->bGetSensorInfos(device_index, sensor_index,
																  SENSOR_CLASS_CLOCK_SPEED,
																  &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue, &flags))
									{
										if (round_to_nearest_int(fValue) >= 0)
										{
									#ifdef _UNICODE
											TCHAR szTemp[512];
											int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
									#else
											TCHAR *szTemp = szName;
									#endif
											pTreeItem = pFindTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_CLOCK_SPEED, 0);
											if (!pTreeItem)
											{
												HTREEITEM hsensor = tree.InsertItem(szTemp, BITMAP_EMPTY, BITMAP_EMPTY, hclock);
												pTreeItem = new CTreeItem(monitor_index, device_index, sensor_index, sensor_id, hsensor);

												pTreeItem->m_uiFlag = 0;

												pTreeItem->m_uiFlag |= item_color;
												item_color = ITEM_FLAG_ALT_COLOR - item_color;

												pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
											}

											if (fMinValue < MAX_FLOAT)
												SPRINTF(buffer, _countof(buffer), _T("%s\t%.0f MHz\t%.0f MHz\t%.0f MHz"), szTemp, fValue, fMinValue, fMaxValue);
											else
												SPRINTF(buffer, _countof(buffer), _T("%s\t%.0f MHz"), szTemp, fValue);

											if (pTreeItem->m_hItem)
												tree.SetItemText(pTreeItem->m_hItem, buffer);
										}
									}
								}
								if (_bExpand || expand2)
								{
									result = tree.Expand(hclock, TVE_EXPAND);
								}

								expand2 = FALSE;
							}

						//	Utilizations
							nbsensors = pMonitor->iGetNumberOfSensors(device_index, SENSOR_CLASS_UTILIZATION);
							if (nbsensors > 0)
							{
								expand2 = FALSE;
								hutilization = hCreateLabelTreeItem(monitor_index, device_index, SENSOR_CLASS_UTILIZATION, hdev, pMonitorTreeItemList);
								nbitems = iCountTreeItems(hutilization, FALSE);
								if ((nbitems != nbsensors) && (!_bExpand))
								{
									vDeleteTreeItems(monitor_index, device_index, SENSOR_CLASS_UTILIZATION);
									expand2 = TRUE;
								}
								item_color = ITEM_FLAG_ALT_COLOR;

								for (sensor_index = 0; sensor_index < nbsensors; sensor_index++ )
								{
									if (pMonitor->bGetSensorInfos(device_index, sensor_index,
																  SENSOR_CLASS_UTILIZATION,
																  &sensor_id, szName, &raw_value, &fValue, &fMinValue, &fMaxValue, &flags))
									{
										if ((round_to_nearest_int(fValue) >= 0) && (round_to_nearest_int(fValue) <= 100))
										{
									#ifdef _UNICODE
											TCHAR szTemp[512];
											int value = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szName, -1, szTemp, 512);
									#else
											TCHAR *szTemp = szName;
									#endif
											pTreeItem = pFindTreeItem(monitor_index, device_index, sensor_index, SENSOR_CLASS_UTILIZATION, 0);
											if (!pTreeItem)
											{
												HTREEITEM hsensor = tree.InsertItem(szTemp, BITMAP_EMPTY, BITMAP_EMPTY, hutilization);
												pTreeItem = new CTreeItem(monitor_index, device_index, sensor_index, sensor_id, hsensor);

												pTreeItem->m_uiFlag = 0;


												pTreeItem->m_uiFlag |= item_color;
												item_color = ITEM_FLAG_ALT_COLOR - item_color;

												pMonitorTreeItemList->m_pTreeItemList->vAddItem(pTreeItem);
											}

											if (fMinValue < MAX_FLOAT)
												SPRINTF(buffer, _countof(buffer), _T("%s\t%d %%\t%d %%\t%d %%"), szTemp, (int)fValue, (int)fMinValue, (int)fMaxValue);
											else
												SPRINTF(buffer, _countof(buffer), _T("%s\t%d %%"), szTemp, (int)fValue);

											if (pTreeItem->m_hItem)
												tree.SetItemText(pTreeItem->m_hItem, buffer);
										}
									}
								}
								if (_bExpand || expand2)
								{
									result = tree.Expand(hutilization, TVE_EXPAND);
								}
							}
						}
						if (_bExpand) result = tree.Expand(hdev, TVE_EXPAND);
					}

					monitor_index++;
					pMonitor = MonitorListParser.pGetNext();

					if (_bExpand)
						result = tree.Expand(hRoot, TVE_EXPAND);
				}
				ReleaseMutex(CHWMonitorApp::m_hTMutex);
			}
			break;

		case WAIT_ABANDONED:
			{
				ReleaseMutex(CHWMonitorApp::m_hTMutex);
			}
			break;

		case WAIT_TIMEOUT:
			{
				int debug = 0;
			}
			break;

		default:
			{
				int debug = 0;
			}
			break;
	}
}

CMonitorTreeItemList *CHWMonitorView::pGetMonitorTreeItemList(int _monitor_index)
{
	tdMonitorTreeItemListListParser parser(m_pMonitorTreeItemListList);
	CMonitorTreeItemList *pMonitorTreeItemList = parser.pGetRoot();
	while (pMonitorTreeItemList)
	{
		if (pMonitorTreeItemList->m_iMonitorIndex == _monitor_index)
		{
			return pMonitorTreeItemList;
		}
		pMonitorTreeItemList = parser.pGetNext();
	}
	return NULL;
}

unsigned int CHWMonitorView::uiFindFlag(HTREEITEM _hTreeItem)
{
	tdMonitorTreeItemListListParser parser(m_pMonitorTreeItemListList);
	CMonitorTreeItemList *pMonitorTreeItemList = parser.pGetRoot();
	while (pMonitorTreeItemList)
	{
		tdTreeItemListParser itemparser(pMonitorTreeItemList->m_pTreeItemList);
		CTreeItem *pItem = itemparser.pGetRoot();
		while (pItem)
		{
			if (pItem->m_hItem == _hTreeItem)
				return pItem->m_uiFlag;

			pItem = itemparser.pGetNext();
		}
		pMonitorTreeItemList = parser.pGetNext();
	}
	return 0;
}

CTreeItem *CHWMonitorView::pFindTreeItem(HTREEITEM _hTreeItem)
{
	tdMonitorTreeItemListListParser parser(m_pMonitorTreeItemListList);
	CMonitorTreeItemList *pMonitorTreeItemList = parser.pGetRoot();
	while (pMonitorTreeItemList)
	{
		tdTreeItemListParser itemparser(pMonitorTreeItemList->m_pTreeItemList);
		CTreeItem *pItem = itemparser.pGetRoot();
		while (pItem)
		{
			if (pItem->m_hItem == _hTreeItem)
				return pItem;

			pItem = itemparser.pGetNext();
		}
		pMonitorTreeItemList = parser.pGetNext();
	}
	return NULL;
}

CTreeItem *CHWMonitorView::pFindTreeItem(int _monitor_index, int _device_index, int _sensor_index, int _sensor_id, unsigned int _flag)
{
	CMonitorTreeItemList *pMonitorTreeItemList = pGetMonitorTreeItemList(_monitor_index);
	if (pMonitorTreeItemList)
	{
		tdTreeItemListParser itemparser(pMonitorTreeItemList->m_pTreeItemList);
		CTreeItem *pItem = itemparser.pGetRoot();
		while (pItem)
		{
			if ((pItem->m_iMonitorIndex == _monitor_index) &&
				(pItem->m_iDeviceIndex == _device_index) &&
				(pItem->m_iSensorIndex == _sensor_index) &&
				((pItem->m_uiSensorID & SENSOR_CLASS_MASK) == (unsigned int)(_sensor_id & SENSOR_CLASS_MASK)) &&
				((pItem->m_uiFlag & 0xFFFF) == _flag))
			{
				return pItem;
			}
			pItem = itemparser.pGetNext();
		}
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	CTreeItem
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CTreeItem::CTreeItem(int _monitor_index, int _device_index, int _sensor_index, unsigned int _sensor_id, HTREEITEM _hTreeItem)
{
	m_iMonitorIndex = _monitor_index;
	m_iDeviceIndex = _device_index;
	m_iSensorIndex = _sensor_index;
	m_uiSensorID = _sensor_id;
	m_hItem = _hTreeItem;
	m_uiFlag = 0;
}

CTreeItem::~CTreeItem()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	CMonitorTreeItemList
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CMonitorTreeItemList::CMonitorTreeItemList(int _monitor_index)
{
	m_iMonitorIndex = _monitor_index;
	m_pTreeItemList = new tdTreeItemList();
}

CMonitorTreeItemList::~CMonitorTreeItemList()
{
	if (m_pTreeItemList)
	{
		m_pTreeItemList->vDeleteAllItems();
		delete m_pTreeItemList;
	}
}

int CMonitorTreeItemList::iGetNumberOfSensor(int _device_index, unsigned int _sensor_class)
{
	int nbsensors = 0;

	tdTreeItemListParser itemparser(m_pTreeItemList);
	CTreeItem *pItem = itemparser.pGetRoot();
	while (pItem)
	{
		if  ((pItem->m_iDeviceIndex == _device_index) &&
			 ((pItem->m_uiSensorID & SENSOR_CLASS_MASK) == _sensor_class) && 
			 (pItem->m_iSensorIndex != I_UNDEFINED_VALUE))
		{
			nbsensors++;
		}
		pItem = itemparser.pGetNext();
	}
	return nbsensors;
}
