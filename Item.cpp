#include "stdafx.h"
#include "Item.h"


Item::Item(void)
{
	m_szItemName.clear();
	m_vDepend.clear();
	m_bUseable = false;
	m_nCompleteCount = 0;
	m_pUseable = NULL;
	m_pItem = NULL;
}


Item::~Item(void)
{
}

int Item::GetNodeCount()
{
	return m_nCompleteCount;
}

std::string Item::GetName()
{
	return m_szItemName;
}

bool Item::GetUseable()
{
	return m_bUseable;
}

void Item::SetCompleteCount(int n)
{
	m_nCompleteCount = n;
}

void Item::SetName(string str)
{
	m_szItemName = str;
}

void Item::SetUseable(bool bUseable)
{
	m_bUseable = bUseable;
}

CTextUI* Item::GetUseableText()
{
	return m_pUseable;
}

void Item::SetUseableText(CTextUI* pUseable)
{
	m_pUseable = pUseable;
}

CTreeNodeUI* Item::GetItemNode()
{
	return m_pItem;
}

void Item::SetItemNode(CTreeNodeUI* pItem)
{
	m_pItem = pItem;
}
