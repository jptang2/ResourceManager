#include "stdafx.h"
#include "Item.h"
#include <string>

Item::Item(void)
{
	m_szItemName.clear();
	m_vDepend.clear();	
	m_pUseable = NULL;
	m_pItem = NULL;
}


Item::~Item(void)
{
}


std::string Item::GetName()
{
	return m_szItemName;
}

bool Item::GetUseable()
{
	return (m_vDepend.size() == m_vCurrent.size());
}

int Item::GetCompleteCount()
{
	return m_vDepend.size();
}

void Item::SetName(string str)
{
	m_szItemName = str;
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

void Item::AddNodeInLoad(string szNode)
{
	m_vDepend.push_back(szNode);
	m_vCurrent.push_back(szNode);
}
void Item::AddNodeInUse(string szNode)
{
	m_vCurrent.push_back(szNode);
}

void Item::DelNode(string szNode)
{	
	for (vector<string>::iterator it=m_vCurrent.begin();it!=m_vCurrent.end();it++)
	{	
		if ((*it) == szNode)
		{
			m_vCurrent.erase(it);
			break;
		}
	}	
}

bool Item::FindInDepends(string szNode,int& n)
{
	int nCount = m_vDepend.size();
	for (int i=0;i<nCount;i++)
	{
		if (m_vDepend[i] == szNode)
		{
			n = i;
			return true;
		}
	}
	return false;
}

bool Item::FindInCurrent(string szNode,int& n)
{
	int nCount = m_vCurrent.size();
	for (int i=0;i<nCount;i++)
	{
		if (m_vCurrent[i] == szNode)
		{
			n = i;
			return true;
		}
	}
	return false;
}

void Item::SetUseableState()
{
	if (m_vCurrent.size() < m_vDepend.size())
	{
		CTextUI* pUseable = GetUseableText();
		pUseable->SetText("unusable");				
		pUseable->SetAttribute("textcolor","#ffff0000");
	}
	
	int nCurrentInDepend = 0;//Õ¼±È

	for (int i=0;i<m_vCurrent.size();i++)
	{
		string szCurrent = m_vCurrent[i];
		for ()
		{
		}
	}




	CTextUI* pUseable = GetUseableText();
	pUseable->SetText("unusable");				
	pUseable->SetAttribute("textcolor","#ffff0000");
}
