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
	CTextUI* GetUseableText();
	void SetUseableText(CTextUI* pUseable);
	CTreeNodeUI* GetItemNode();
	void SetItemNode(CTreeNodeUI* pItem);
	void AddNodeInLoad(string szNode);
	void AddNodeInUse(string szNode);
	void DelNode(string szNode);
	bool FindInDepends(string szNode);
	bool FindInCurrent(string szNode);
	void SetUseableState();
	vector<string> GetCurrentNodes();
private:
	string m_szItemName;				
	CTextUI* m_pUseable;
	CTreeNodeUI* m_pItem;
	vector<string> m_vDepend;
	vector<string> m_vCurrent;
};

