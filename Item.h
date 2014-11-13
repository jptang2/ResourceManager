#pragma once
class Item
{
public:
	Item(void);
	~Item(void);

	string m_szItemName;
	vector<string> m_vResource;
	bool m_bUseable;	
};


