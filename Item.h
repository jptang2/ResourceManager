#pragma once
class Item
{
public:
	Item(void);
	~Item(void);

	int GetNodeCount();
	string GetName();
	void SetName(string str);
	bool GetUseable();
	void SetUseable(bool bUseable);
	void SetCompleteCount(int n);		
	CTextUI* GetUseableText();
	void SetUseableText(CTextUI* pUseable);
	CTreeNodeUI* GetItemNode();
	void SetItemNode(CTreeNodeUI* pItem);
	void AddNode(string szNode);
	void DelNode(string szNode);
private:
	string m_szItemName;	
	bool m_bUseable;	
	int m_nCompleteCount;
	CTextUI* m_pUseable;
	CTreeNodeUI* m_pItem;
	vector<string> m_vDepend;
	vector<string> m_vCurrent;
};

