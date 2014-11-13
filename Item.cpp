#include "stdafx.h"
#include "Item.h"


Item::Item(void)
{
	m_szItemName.clear();
	m_vResource.clear();
	m_bUseable = false;
}


Item::~Item(void)
{
}
