#ifndef _MainDialog_H_
#define _MainDialog_H_


#include "Item.h"
#include <map>
//------------------------------
//-----------------


class MainDialog : public CWindowWnd, public INotifyUI,public IDialogBuilderCallback
{
public:

    MainDialog():m_dwSkinNo(0) 
	{
    };

    LPCTSTR GetWindowClassName() const 
    { 
        return _T("MainDialog"); 
    };

    UINT GetClassStyle() const
    { 
        return CS_DBLCLKS; 
    };

    void OnFinalMessage(HWND /*hWnd*/) 
    { 
        delete this;
    };
	CControlUI* CreateControl(LPCTSTR pstrClass) 
	{
		return NULL;
	};
	CDuiString GetNowTimeString()
	{
		SYSTEMTIME time = {0};
		
		TCHAR szTime[MAX_PATH] = {0};
		::GetLocalTime(&time);
		//_stprintf_s( szTime, MAX_PATH, _T("%04d/%02d/%02d %02d:%02d:%02d"), time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		_stprintf_s( szTime, MAX_PATH, _T("%02d:%02d:%02d"), time.wHour, time.wMinute, time.wSecond);
		return szTime;
	};
	void Init();

    void OnPrepare(TNotifyUI& msg) 
    {

    };
	void Notify(TNotifyUI& msg);

	void DeleteNodeInTree(string szNode);

	void AddNodeInTree( string szNode,CTreeNodeUI* pParent);

	bool SaveToFile();

	bool FindInItems(string str,int& n);

	void DelInItems(string str);

	LRESULT OnMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	
public:
    CPaintManagerUI m_pm;
	

private:
    CButtonUI* m_pCloseBtn;
    CButtonUI* m_pRestoreBtn;
    CButtonUI* m_pMinBtn;
	CButtonUI* m_pClose;
	CButtonUI* m_pAddItem;
	CButtonUI* m_pAddNode;
	CButtonUI* m_pDelNode;
	CButtonUI* m_pSaveAndExit;
	CEditUI*   m_pInputNodeText;
	CTextUI*   m_pCurrentNodeText;
	CTreeViewUI* m_pTree;

	DWORD m_dwSkinNo;
	vector<Item*> m_vItem;
    //...
};



#endif