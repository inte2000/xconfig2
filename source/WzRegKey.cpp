#include "framework.h"
#include "WzRegKey.h"

#define WZ_ASSERT assert

CWzRegKey::CWzRegKey()
{
	m_hKey = NULL;
}

CWzRegKey::CWzRegKey(HKEY hKey, LPCTSTR lpSubKey, REGSAM samDesired)
{
	m_hKey = NULL;
	CreateKey(hKey,lpSubKey,samDesired);
}

CWzRegKey::~CWzRegKey()
{
	CloseKey();
}

LONG CWzRegKey::CreateKey(HKEY hKey, LPCTSTR lpSubKey, REGSAM samDesired)
{
	WZ_ASSERT(m_hKey == NULL);
	DWORD dwDisposition;

	LONG lRtn = ::RegCreateKeyEx(hKey,lpSubKey,0,NULL,REG_OPTION_NON_VOLATILE,samDesired,NULL,&m_hKey,&dwDisposition);
	if(lRtn != ERROR_SUCCESS)
		m_hKey = NULL;

	return lRtn;
}

LONG CWzRegKey::OpenKey(HKEY hKey, LPCTSTR lpSubKey, REGSAM samDesired)
{
	WZ_ASSERT(m_hKey == NULL);
	
	LONG lRtn = ::RegOpenKeyEx(hKey,lpSubKey,0,samDesired,&m_hKey);
	if(lRtn != ERROR_SUCCESS)
		m_hKey = NULL;

	return lRtn;
}

LONG CWzRegKey::CloseKey()
{
	LONG lRtn = ERROR_SUCCESS;
	if(m_hKey != NULL)
	{
		lRtn = ::RegCloseKey(m_hKey);
		m_hKey = NULL;
	}

	return lRtn;
}

LONG CWzRegKey::GetString(LPCTSTR lpszValueName, LPTSTR lpValueBuf, int nBufSize, LPCTSTR lpDefaultValue)
{
	WZ_ASSERT(m_hKey != NULL);
	WZ_ASSERT(lpValueBuf != NULL);

	DWORD dwType = REG_SZ;
	DWORD dwSize = nBufSize;
	LONG lRtn = ::RegQueryValueEx(m_hKey,lpszValueName,NULL,&dwType,(LPBYTE)lpValueBuf,&dwSize);
	if(lRtn != ERROR_SUCCESS)
	{
		if(lpDefaultValue != NULL)
		{
			int nDefLenth = lstrlen(lpDefaultValue);
			if(nDefLenth < nBufSize)
				lstrcpy(lpValueBuf,lpDefaultValue);
			else
			{
				lstrcpyn(lpValueBuf,lpDefaultValue,nBufSize);
				lpValueBuf[nBufSize] = 0;
			}
		}
		else
		{
			lpValueBuf[0] = 0;
		}
	}
	
	return lRtn;
}

LONG CWzRegKey::GetBinary(LPCTSTR lpszValueName, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
	WZ_ASSERT(m_hKey != NULL);
	
	return ::RegQueryValueEx(m_hKey,lpszValueName,NULL,lpType,lpData,lpcbData);
}

LONG CWzRegKey::SetString(LPCTSTR lpszValueName, LPCTSTR lpValue)
{
	WZ_ASSERT(m_hKey != NULL);
	DWORD dwSize = lstrlen(lpValue) + 1;// include null char
	LONG lRtn = ::RegSetValueEx(m_hKey,lpszValueName,0,REG_SZ,(CONST BYTE *)lpValue,dwSize);
	
	return lRtn;
}

LONG CWzRegKey::SetBinary(LPCTSTR lpszValueName, DWORD dwType, CONST BYTE *lpData, DWORD cbData)
{
	WZ_ASSERT(m_hKey != NULL);

	return ::RegSetValueEx(m_hKey,lpszValueName,0,dwType,lpData,cbData);
}

LONG CWzRegKey::EnumValue(DWORD dwIndex,LPTSTR lpValueName,LPDWORD lpcValueName,LPDWORD lpType,LPBYTE lpData,LPDWORD lpcbData)
{
	WZ_ASSERT(m_hKey != NULL);

	return ::RegEnumValue(m_hKey,dwIndex,lpValueName,lpcValueName,NULL,lpType,lpData,lpcbData);
}

LONG CWzRegKey::EnumSubKey(DWORD dwIndex,LPTSTR lpName,LPDWORD lpcName,LPTSTR lpClass,LPDWORD lpcClass, PFILETIME lpftLastWriteTime)
{
	WZ_ASSERT(m_hKey != NULL);

	return ::RegEnumKeyEx(m_hKey,dwIndex,lpName,lpcName,NULL,lpClass,lpcClass,lpftLastWriteTime);
}

