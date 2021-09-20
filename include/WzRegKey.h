#ifndef __WZREGKEY_H__
#define __WZREGKEY_H__

class CWzRegKey
{
public:
	CWzRegKey();
	CWzRegKey(HKEY hKey, LPCTSTR lpSubKey, REGSAM samDesired = KEY_ALL_ACCESS);
	~CWzRegKey();

	operator HKEY() { return m_hKey; }
public:
	LONG CreateKey(HKEY hKey, LPCTSTR lpSubKey, REGSAM samDesired = KEY_ALL_ACCESS);
	LONG OpenKey(HKEY hKey, LPCTSTR lpSubKey, REGSAM samDesired = KEY_ALL_ACCESS);
	LONG CloseKey();
	BOOL IsValid() const { return (m_hKey != NULL); }

	LONG GetString(LPCTSTR lpszValueName, LPTSTR lpValueBuf, int nBufSize, LPCTSTR lpDefaultValue = NULL);
	LONG GetBinary(LPCTSTR lpszValueName, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData);

	LONG SetString(LPCTSTR lpszValueName, LPCTSTR lpValue);
	LONG SetBinary(LPCTSTR lpszValueName, DWORD dwType, CONST BYTE *lpData, DWORD cbData);

	LONG EnumValue(DWORD dwIndex,LPTSTR lpValueName,LPDWORD lpcValueName,LPDWORD lpType,LPBYTE lpData,LPDWORD lpcbData);
	LONG EnumSubKey(DWORD dwIndex,LPTSTR lpName,LPDWORD lpcName,LPTSTR lpClass,LPDWORD lpcClass, PFILETIME lpftLastWriteTime);

protected:
	HKEY         m_hKey;
};

#endif