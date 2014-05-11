// EgumaCppLib.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "EgumaWinCE.h"

#include <wininet.h>
#include <string>
#include <ctype.h>

#pragma comment( lib, "wininet" )

using namespace std;


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

std::string GetString(const std::string& json, const std::string& key)
{
	// todo: if (found!=std::string::npos)

	std::string keyWithQuotes = "\"" + key + "\"";
	std::string::size_type keyStartPos = json.find(keyWithQuotes);
	std::string::size_type keyEndPos = keyStartPos + keyWithQuotes.length();

	std::string::size_type valueStartPos = json.find('\"', keyEndPos+1) + 1;
	std::string::size_type valueEndPos = json.find('\"', valueStartPos) - 1;


	std::string value = json.substr(valueStartPos, valueEndPos - valueStartPos + 1);


	return value;
}

bool GetBool(const std::string& json, const std::string& key)
{
	// todo: if (found!=std::string::npos)

	std::string keyWithQuotes = "\"" + key + "\"";
	std::string::size_type keyStartPos = json.find(keyWithQuotes);
	std::string::size_type colonPos = json.find(':', keyStartPos);

	std::string::size_type pos = colonPos + 1;

	if (json[pos] == 't')
		return true;

	return false;
}

int GetNumber(const std::string& json, const std::string& key)
{
	// todo: if (found!=std::string::npos)

	std::string keyWithQuotes = "\"" + key + "\"";
	std::string::size_type keyStartPos = json.find(keyWithQuotes);
	std::string::size_type colonPos = json.find(':', keyStartPos);
   
	std::string::size_type pos = colonPos + 1;

	std::string numberAsString;

	while (isdigit(json[pos]))
	{
		numberAsString += json[pos++];
	}


	return atoi(numberAsString.c_str());
}

void SetErrorMessage(wchar_t* error, wchar_t* message)
{
	if (error == NULL)
		return;

	wsprintf(error, _T("%s"), message);
}

bool GetBalance(wchar_t* apiKey, wchar_t* code, wchar_t* codeOut, bool& isRedeemable, int& balanceInCents, int& totalAmountInCents, wchar_t* messageOut, wchar_t* error)
{
	HINTERNET hIntSession = InternetOpen(_T("HTTPGET"),INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	
	if (hIntSession == NULL)
	{
		SetErrorMessage(error, _T("InternetOpen() failed!"));
		return false;
	}
	

	HINTERNET hHttpSession = InternetConnect(hIntSession, _T("api.e-guma.ch"),INTERNET_DEFAULT_HTTP_PORT, NULL,NULL,INTERNET_SERVICE_HTTP,0,0);


	// v1/vouchers/2QH3-QTDM-28N6/balance.json?apikey=510e32c594d84816a4af9df0
	std::wstring url = wstring(_T("v1/vouchers/")) + wstring(code) + wstring(_T("/balance.json?apikey=")) + wstring(apiKey);
	

    HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T("GET"), url.c_str(), 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	
    TCHAR* szHeaders = _T("Content-Type: application/json");
    CHAR szReq[1024] = "";
    if( !HttpSendRequest(hHttpRequest, szHeaders, _tcslen(szHeaders), szReq, strlen(szReq))) {
		DWORD dwErr = GetLastError();
      
		SetErrorMessage(error, _T("HttpSendRequest() failed!"));

		return false;
    }

	// todo: - error if not 200 OK
	//       - remove while


    CHAR json[1025];
    DWORD dwRead=0;
    while(::InternetReadFile(hHttpRequest, json, sizeof(json)-1, &dwRead) && dwRead) {
      json[dwRead] = 0;
      
		isRedeemable = GetBool(json, "is_redeemable");


	  	balanceInCents = GetNumber(json, "balance_in_cents");
		totalAmountInCents = GetNumber(json, "total_amount_in_cents");

		
		// code
		if (codeOut != NULL)
		{
			std::string code = GetString(json, "code");
			wsprintf(codeOut, _T("%s"), s2ws(code).c_str()); 
		}

		if (messageOut != NULL)
		{
			std::string message = GetString(json, "message");
			wsprintf(messageOut, _T("%s"), s2ws(message).c_str());
		}
		

      dwRead=0;
    }

    ::InternetCloseHandle(hHttpRequest);
    ::InternetCloseHandle(hHttpSession);
    ::InternetCloseHandle(hIntSession);

	return true;
}

bool Hello()
{
	HINTERNET hIntSession = InternetOpen(_T("HTTPGET"),INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	
	if (hIntSession == NULL)
	{
		return false;
	}
	

	HINTERNET hHttpSession = InternetConnect(hIntSession, _T("api.e-guma.ch"),INTERNET_DEFAULT_HTTP_PORT, NULL,NULL,INTERNET_SERVICE_HTTP,0,0);


	std::wstring url = wstring(_T("v1/hello"));
	

    HINTERNET hHttpRequest = HttpOpenRequest(hHttpSession, _T("GET"), url.c_str(), 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	
    TCHAR* szHeaders = _T("Content-Type: application/json");
    CHAR szReq[1024] = "";
    if( !HttpSendRequest(hHttpRequest, szHeaders, _tcslen(szHeaders), szReq, strlen(szReq))) {
		DWORD dwErr = GetLastError();
		return false;
    }

	// todo: - error if not 200 OK
	//       - remove while


    CHAR json[1025];
    DWORD dwRead=0;
    while(::InternetReadFile(hHttpRequest, json, sizeof(json)-1, &dwRead) && dwRead) {
      json[dwRead] = 0;
      
		if (json[0] != 'O' && json[1] != 'K')
			return false;

		

      dwRead=0;
    }

    ::InternetCloseHandle(hHttpRequest);
    ::InternetCloseHandle(hHttpSession);
    ::InternetCloseHandle(hIntSession);

	return true;
}