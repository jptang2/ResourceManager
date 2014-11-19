#pragma once
#include "StdAfx.h"
TCHAR g_szPath[MAX_PATH];
TCHAR* GetExePath()
{	
	memset(g_szPath,0,MAX_PATH);
	TCHAR buffer[MAX_PATH];
	TCHAR driver[MAX_PATH];
	TCHAR dir[MAX_PATH];
	GetModuleFileName(NULL,buffer,MAX_PATH);
	_splitpath(buffer,driver,dir,NULL,NULL);
	strcat(driver,dir);	
	strcat(g_szPath,driver);	
	return g_szPath;
}