#include "stdafx.h"
#include "MainDialog.h"
#include <Commdlg.h>
#include <shellapi.h>
#include <string>
bool g_bUpdateDir = false;


void MainDialog::Init()
{
	m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn")));   
    m_pRestoreBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("restorebtn")));
    m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn")));
	m_pClose = static_cast<CButtonUI*>(m_pm.FindControl(_T("close")));
	m_pAddNode = static_cast<CButtonUI*>(m_pm.FindControl(_T("Btn_AddNode")));
	m_pDelNode = static_cast<CButtonUI*>(m_pm.FindControl(_T("Btn_DelNode")));
	m_pInputNodeText = static_cast<CEditUI*>(m_pm.FindControl(_T("Edit_InputNodeName")));
	m_pCurrentNodeText = static_cast<CTextUI*>(m_pm.FindControl(_T("Label_CurrentNodeName")));

	CTreeViewUI* pTree = static_cast<CTreeViewUI*>(m_pm.FindControl(_T("tree")));
			
	errno_t err;
	FILE* pFile = NULL;
	err = fopen_s(&pFile,"resource.txt","r");
	if (NULL == pFile)
	{
		return;
	}

	char szTemp[MAX_PATH]={0};


	while (1 == fscanf_s(pFile,"%[^\n]",szTemp,sizeof(szTemp)))
	{			
		fgetc(pFile);			

		Item *item = new Item();

		string str(szTemp);
		string::size_type pos = str.find(' ');

		string szItemName(str.substr(0, pos));
		item->m_szItemName = szItemName;	
			

		//item				
		TCHAR szItemNode[MAX_PATH] = {0};		 	
		strcpy(szItemNode, szItemName.c_str());  

		CTreeNodeUI* pItemNode = new CTreeNodeUI;
		pItemNode->SetAttribute(_T("folderattr"),_T("padding=\"0,1,0,0\" width=\"36\" height=\"16\" normalimage=\"file='treeview_b.png' source='0,0,36,16'\" hotimage=\"file='treeview_b.png' source='36,0,72,16'\" selectedimage=\"file='treeview_a.png' source='0,0,36,16' selectedhotimage=\"file='treeview_a.png' source='36,0,72,16'\""));
		bool bbb=pTree->Add(pItemNode);
		pItemNode->SetItemText(szItemNode);
		pItemNode->SetUserData(szItemNode);


		if(string::npos == pos)
		{
			item->m_szItemName = str;	
			m_mapItem[item->m_szItemName] = item;
			continue;
		}			

		//resources
		str = str.substr(pos + 1);
		while (string::npos != pos )
		{
			pos = str.find(' ');
			string szResourceName(str.substr(0, pos));
			item->m_vResource.push_back(szResourceName);
			str = str.substr(pos + 1);
				
			TCHAR szResourceNode[MAX_PATH] = {0};		 	
			strcpy(szResourceNode, szResourceName.c_str());  
					
			CTreeNodeUI* pResourceNode = new CTreeNodeUI;
			int nn=pItemNode->GetCountChild();
			bool bb = pItemNode->AddChildNode(pResourceNode);
			nn=pItemNode->GetCountChild();

			pResourceNode->SetAttribute(_T("folderattr"),_T("padding=\"0,1,0,0\" width=\"36\" height=\"16\" normalimage=\"file='treeview_b.png' source='0,0,36,16'\" hotimage=\"file='treeview_b.png' source='36,0,72,16'\" selectedimage=\"file='treeview_a.png' source='0,0,36,16' selectedhotimage=\"file='treeview_a.png' source='36,0,72,16'\""));

			pTree->SetItemExpand(true, pResourceNode);
			pResourceNode->SetItemText(szResourceNode);			
			pResourceNode->SetName(szResourceNode);
			pResourceNode->SetVisibleTag(false);
		}

		item->m_bUseable = true;
		m_mapItem[item->m_szItemName] = item;		
	}

	fclose(pFile);
}
void MainDialog::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("windowinit") ) 
		OnPrepare(msg);
	else if( msg.sType == _T("click") ) 
	{		
		if( msg.pSender == m_pCloseBtn ) 
		{
			PostQuitMessage(0);
			return; 
		}
		else if( msg.pSender == m_pMinBtn ) 
		{ 
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
			return; 
		}	
		else if( msg.pSender == m_pRestoreBtn ) 
		{ 
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; 
		}
		else if( msg.pSender == m_pAddNode ) 
		{ 
			CTreeViewUI* pTree = static_cast<CTreeViewUI*>(m_pm.FindControl(_T("tree")));
			// 		map<string,Item*>::iterator it = m_mapItem.find(sItemName);
			// 		if (it!=m_mapItem.end())
			// 		{
			// 			LPCTSTR ch ;
			// 		//	_T("Item name already exist, the new one will replace the old one")
			// 			MessageBox(NULL,ch,_T("Tip"),MB_OK);
			// 		}
			return; 
		}		
		else if( msg.pSender == m_pDelNode ) 
		{ 			
			CTreeViewUI* pTree = static_cast<CTreeViewUI*>(m_pm.FindControl(_T("tree")));
			CTreeNodeUI* pItemNode = pTree->GetCurSelNode();
			
			if (NULL == pItemNode)
			{
				MessageBox(NULL,"please select a node.",_T("Tip"),MB_OK);
			}

			string szItem = pItemNode->GetItemText();
			map<string,Item*>::iterator it = m_mapItem.find(szItem);
			if (it!=m_mapItem.end())
			{
				m_mapItem.erase(it);
			}
			return; 
		}		
	}
	
	else if(msg.sType==_T("headerclick"))
	{
		CControlUI* pHeader = static_cast<CControlUI*>(msg.pSender);
		CListUI* pList = static_cast<CListUI*>(pHeader->GetParent()->GetParent());
		
		CListBodyUI* pBody = (CListBodyUI*)pList->GetList();
		pBody->SortItems(pList->GetItemIndex(pHeader));
		//MessageBox(NULL,,_T("test"),MB_OK);
	}
	else if( msg.sType == _T("itemexpand") ) 
	{
		CTreeNodeUI* pNowNode = static_cast<CTreeNodeUI*>(msg.pSender);
		pNowNode->Select(true);
		
		CTreeViewUI* pTree = static_cast<CTreeViewUI*>(m_pm.FindControl(_T("tree")));
		CListUI* pList = static_cast<CListUI*>(m_pm.FindControl(_T("file_list")));
		g_bUpdateDir = false;
		if (!pNowNode->IsHasChild())
		{
			g_bUpdateDir = true;
		}

		int nnn = pNowNode->GetCountChild();

	}
	
}

LRESULT MainDialog::OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return FALSE;

}
LRESULT MainDialog::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	//--
	
	m_WndShadow.Create(m_hWnd);
	m_WndShadow.SetSize(4);
	m_WndShadow.SetPosition(0, 0);
	//--
	RECT rcClient;
	::GetClientRect(*this, &rcClient);
	::SetWindowPos(*this, NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, \
		rcClient.bottom - rcClient.top, SWP_FRAMECHANGED);

	m_pm.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("skin.xml"), (UINT)0, this, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);
	Init();
	return 0;
}
LRESULT MainDialog::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}
LRESULT MainDialog::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0L);
	bHandled = FALSE;
	return 0;
}
LRESULT MainDialog::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}
LRESULT MainDialog::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}
LRESULT MainDialog::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}
LRESULT MainDialog::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
    ::ScreenToClient(*this, &pt);

    RECT rcClient;
    ::GetClientRect(*this, &rcClient);
	
    if( !::IsZoomed(*this) ) {
        RECT rcSizeBox = m_pm.GetSizeBox();
        if( pt.y < rcClient.top + rcSizeBox.top ) {
            if( pt.x < rcClient.left + rcSizeBox.left ) return HTTOPLEFT;
            if( pt.x > rcClient.right - rcSizeBox.right ) return HTTOPRIGHT;
            return HTTOP;
        }
        else if( pt.y > rcClient.bottom - rcSizeBox.bottom ) {
            if( pt.x < rcClient.left + rcSizeBox.left ) return HTBOTTOMLEFT;
            if( pt.x > rcClient.right - rcSizeBox.right ) return HTBOTTOMRIGHT;
            return HTBOTTOM;
        }
        if( pt.x < rcClient.left + rcSizeBox.left ) return HTLEFT;
        if( pt.x > rcClient.right - rcSizeBox.right ) return HTRIGHT;
    }
	
    RECT rcCaption = m_pm.GetCaptionRect();
    if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
        && pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) 
	{
            CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
            if( pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 && 
                _tcscmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
                _tcscmp(pControl->GetClass(), _T("TextUI")) != 0
				)
                return HTCAPTION;
    }

    return HTCLIENT;
}
LRESULT MainDialog::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_pm.GetRoundCorner();
	if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) {
		RECT rcClient;
		::GetClientRect(*this, &rcClient);
		HRGN hRgn = ::CreateRoundRectRgn(rcClient.left, rcClient.top, rcClient.right + 1, rcClient.bottom + 1, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}

	bHandled = FALSE;
	return 0;
}
LRESULT MainDialog::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	CDuiRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-rcWork.left, -rcWork.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
	lpMMI->ptMaxPosition.x	= rcWork.left;
	lpMMI->ptMaxPosition.y	= rcWork.top;
	lpMMI->ptMaxSize.x		= rcWork.right;
	lpMMI->ptMaxSize.y		= rcWork.bottom;

	bHandled = FALSE;
	return 0;
}

LRESULT MainDialog::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( wParam == SC_CLOSE )
	{
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = __super::HandleMessage(uMsg, wParam, lParam);
	if( ::IsZoomed(*this) != bZoomed )
	{
		if( !bZoomed )
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
			if( pControl ) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
			if( pControl ) pControl->SetVisible(true);
		}
		else 
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
			if( pControl ) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
			if( pControl ) pControl->SetVisible(false);
		}
	}
	return lRes;
}

LRESULT MainDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch( uMsg ) 
	{
		case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
		case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
		case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
		case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
		case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
		case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
		case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
		case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
		case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
		case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
		
		default:
			bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}