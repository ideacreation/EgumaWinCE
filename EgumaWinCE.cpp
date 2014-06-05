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

void SetErrorMessage(char* error, char* message)
{
	if (error == NULL)
		return;

	sprintf(error, "%s", message);
}

void WriteLog(FILE* f, char* text)
{
	fprintf(f, "%s\n", text);
	fflush(f);
}

bool GetBalance(char* apiKey, char* code, char* codeOut, bool* isRedeemable, int* balanceInCents, int* totalAmountInCents, char* messageOut, char* error)
{
	FILE *f = fopen("GetBalance.txt", "w");

	fprintf(f, "API-Key:%s\n", apiKey);
	fprintf(f, "Code:%s\n", code);
	fflush(f);


	HINTERNET hIntSession = InternetOpenA("EgumaWinCE",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	
	if (hIntSession == NULL)
	{
		SetErrorMessage(error, "InternetOpen() failed!");
		WriteLog(f, "InternetOpenA() failed");
		return false;
	}

	WriteLog(f, "InternetOpenA() succeeded");
	

	HINTERNET hHttpSession = InternetConnectA(hIntSession, "api.e-guma.ch",INTERNET_DEFAULT_HTTP_PORT, NULL,NULL,INTERNET_SERVICE_HTTP,0,0);

	WriteLog(f, "InternetConnectA() succeeded");


	std::string url = string("v1/vouchers/") + string(code) + string("/balance.json?apikey=") + string(apiKey);
    HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", url.c_str(), 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	WriteLog(f, "HttpOpenRequestA() succeeded");
	
    CHAR* szHeaders = "Content-Type: application/json";
    CHAR szReq[1024] = "";
    if( !HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szReq, strlen(szReq))) {
		DWORD dwErr = GetLastError();
      
		SetErrorMessage(error, "HttpSendRequest() failed!");
		WriteLog(f, "HttpSendRequestA() failded");

		return false;
    }

	WriteLog(f, "HttpSendRequestA() suceeded");

	// todo: - error if not 200 OK
	//       - remove while


    CHAR json[1025];
    DWORD dwRead=0;
    while(::InternetReadFile(hHttpRequest, json, sizeof(json)-1, &dwRead) && dwRead) {
      json[dwRead] = 0;
      
		*isRedeemable = GetBool(json, "is_redeemable");


	  	*balanceInCents = GetNumber(json, "balance_in_cents");
		*totalAmountInCents = GetNumber(json, "total_amount_in_cents");

		
		// code
		if (codeOut != NULL)
		{
			std::string code = GetString(json, "code");
			sprintf(codeOut, "%s", code.c_str()); 
		}

		if (messageOut != NULL)
		{
			std::string message = GetString(json, "message");
			sprintf(messageOut, "%s", message.c_str());
		}
		

      dwRead=0;
    }

	fprintf(f, "Balance in Cents:%i\n", *balanceInCents);
	fprintf(f, "Code out:%s\n", codeOut);
	fflush(f);

		
	WriteLog(f, "Done! YES!");
	fclose(f);


    ::InternetCloseHandle(hHttpRequest);
    ::InternetCloseHandle(hHttpSession);
    ::InternetCloseHandle(hIntSession);

	return true;
}

bool Redeem(char* apiKey, char* code, int amountInCents, char* codeOut, int* balanceInCents, char* error)
{
	FILE *f = fopen("Redeem.txt", "w");

	fprintf(f, "API-Key:%s\n", apiKey);
	fprintf(f, "Code:%s\n", code);
	fprintf(f, "AmountInCents:%i\n", amountInCents);
	fflush(f);


	HINTERNET hIntSession = InternetOpenA("EgumaWinCE",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	
	if (hIntSession == NULL)
	{
		SetErrorMessage(error, "InternetOpen() failed!");
		WriteLog(f, "InternetOpenA() failed");
		return false;
	}

	WriteLog(f, "InternetOpenA() succeeded");
	

	HINTERNET hHttpSession = InternetConnectA(hIntSession, "api.e-guma.ch",INTERNET_DEFAULT_HTTP_PORT, NULL,NULL,INTERNET_SERVICE_HTTP,0,0);

	WriteLog(f, "InternetConnectA() succeeded");


	std::string url = string("v1/vouchers/") + string(code) + string("/redeem.json?apikey=") + string(apiKey);
    HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "POST", url.c_str(), 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	WriteLog(f, "HttpOpenRequestA() succeeded");
	
    CHAR* szHeaders = "Content-Type: application/x-www-form-urlencoded";
    CHAR szReq[1024] = "";
	sprintf(szReq, "amount_in_cents=%i", amountInCents);
    if( !HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szReq, strlen(szReq))) {
		DWORD dwErr = GetLastError();
      
		SetErrorMessage(error, "HttpSendRequest() failed!");
		WriteLog(f, "HttpSendRequestA() failded");

		return false;
    }

	WriteLog(f, "HttpSendRequestA() suceeded");

	// todo: - error if not 200 OK
	//       - remove while


    CHAR json[1025];
    DWORD dwRead=0;
    while(::InternetReadFile(hHttpRequest, json, sizeof(json)-1, &dwRead) && dwRead) {
      json[dwRead] = 0;
      
		*balanceInCents = GetNumber(json, "balance_in_cents");

		
		// code
		if (codeOut != NULL)
		{
			std::string code = GetString(json, "code");
			sprintf(codeOut, "%s", code.c_str()); 
		}
		

      dwRead=0;
    }

	fprintf(f, "Balance in Cents:%i\n", *balanceInCents);
	fprintf(f, "Code out:%s\n", codeOut);
	fflush(f);

		
	WriteLog(f, "Done! YES!");
	fclose(f);


    ::InternetCloseHandle(hHttpRequest);
    ::InternetCloseHandle(hHttpSession);
    ::InternetCloseHandle(hIntSession);

	return true;
}

bool CancelRedemption(char* apiKey, char* code, int amountInCents, char* codeOut, int* balanceInCents, char* error)
{
	FILE *f = fopen("CancelRedemption.txt", "w");

	fprintf(f, "API-Key:%s\n", apiKey);
	fprintf(f, "Code:%s\n", code);
	fflush(f);


	HINTERNET hIntSession = InternetOpenA("EgumaWinCE",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	
	if (hIntSession == NULL)
	{
		SetErrorMessage(error, "InternetOpen() failed!");
		WriteLog(f, "InternetOpenA() failed");
		return false;
	}

	WriteLog(f, "InternetOpenA() succeeded");
	

	HINTERNET hHttpSession = InternetConnectA(hIntSession, "api.e-guma.ch",INTERNET_DEFAULT_HTTP_PORT, NULL,NULL,INTERNET_SERVICE_HTTP,0,0);

	WriteLog(f, "InternetConnectA() succeeded");


	std::string url = string("v1/vouchers/") + string(code) + string("/cancel_redemption.json?apikey=") + string(apiKey);
    HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "POST", url.c_str(), 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	WriteLog(f, "HttpOpenRequestA() succeeded");
	
    CHAR* szHeaders = "Content-Type: application/x-www-form-urlencoded";
    CHAR szReq[1024] = "";
	sprintf(szReq, "amount_in_cents=%i", amountInCents);
    if( !HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szReq, strlen(szReq))) {
		DWORD dwErr = GetLastError();
      
		SetErrorMessage(error, "HttpSendRequest() failed!");
		WriteLog(f, "HttpSendRequestA() failded");

		return false;
    }

	WriteLog(f, "HttpSendRequestA() suceeded");

	// todo: - error if not 200 OK
	//       - remove while


    CHAR json[1025];
    DWORD dwRead=0;
    while(::InternetReadFile(hHttpRequest, json, sizeof(json)-1, &dwRead) && dwRead) {
      json[dwRead] = 0;
      
		*balanceInCents = GetNumber(json, "balance_in_cents");

		
		// code
		if (codeOut != NULL)
		{
			std::string code = GetString(json, "code");
			sprintf(codeOut, "%s", code.c_str()); 
		}
		

      dwRead=0;
    }

	fprintf(f, "Balance in Cents:%i\n", *balanceInCents);
	fprintf(f, "Code out:%s\n", codeOut);
	fflush(f);

		
	WriteLog(f, "Done! YES!");
	fclose(f);


    ::InternetCloseHandle(hHttpRequest);
    ::InternetCloseHandle(hHttpSession);
    ::InternetCloseHandle(hIntSession);

	return true;
}

bool DepotStatus(char* apiKey, char* code, int* amountInCents, bool* isInDepot, char* codeOut, char* error)
{
	FILE *f = fopen("DepotStatus.txt", "w");

	fprintf(f, "API-Key:%s\n", apiKey);
	fprintf(f, "Code:%s\n", code);
	fflush(f);


	HINTERNET hIntSession = InternetOpenA("EgumaWinCE",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	
	if (hIntSession == NULL)
	{
		SetErrorMessage(error, "InternetOpen() failed!");
		WriteLog(f, "InternetOpenA() failed");
		return false;
	}

	WriteLog(f, "InternetOpenA() succeeded");
	

	HINTERNET hHttpSession = InternetConnectA(hIntSession, "api.e-guma.ch",INTERNET_DEFAULT_HTTP_PORT, NULL,NULL,INTERNET_SERVICE_HTTP,0,0);

	WriteLog(f, "InternetConnectA() succeeded");


	std::string url = string("v1/vouchers/") + string(code) + string("/depot_status.json?apikey=") + string(apiKey);
    HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", url.c_str(), 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	WriteLog(f, "HttpOpenRequestA() succeeded");
	
    CHAR* szHeaders = "Content-Type: application/json";
    CHAR szReq[1024] = "";
    if( !HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szReq, strlen(szReq))) {
		DWORD dwErr = GetLastError();
      
		SetErrorMessage(error, "HttpSendRequest() failed!");
		WriteLog(f, "HttpSendRequestA() failded");

		return false;
    }

	WriteLog(f, "HttpSendRequestA() suceeded");

	// todo: - error if not 200 OK
	//       - remove while


    CHAR json[1025];
    DWORD dwRead=0;
    while(::InternetReadFile(hHttpRequest, json, sizeof(json)-1, &dwRead) && dwRead) {
      json[dwRead] = 0;
      
		*amountInCents = GetNumber(json, "amount_in_cents");
		*isInDepot = GetBool(json, "is_in_depot");
		
		// code
		if (codeOut != NULL)
		{
			std::string code = GetString(json, "code");
			sprintf(codeOut, "%s", code.c_str()); 
		}
		

      dwRead=0;
    }

	fprintf(f, "Amount in Cents:%i\n", *amountInCents);
	fprintf(f, "Code out:%s\n", codeOut);
	fflush(f);

		
	WriteLog(f, "Done! YES!");
	fclose(f);


    ::InternetCloseHandle(hHttpRequest);
    ::InternetCloseHandle(hHttpSession);
    ::InternetCloseHandle(hIntSession);

	return true;
}

bool Activate(char* apiKey, char* code, int* amountInCents, char* codeOut, char* error)
{
	FILE *f = fopen("Activate.txt", "w");

	fprintf(f, "API-Key:%s\n", apiKey);
	fprintf(f, "Code:%s\n", code);
	fflush(f);


	HINTERNET hIntSession = InternetOpenA("EgumaWinCE",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	
	if (hIntSession == NULL)
	{
		SetErrorMessage(error, "InternetOpen() failed!");
		WriteLog(f, "InternetOpenA() failed");
		return false;
	}

	WriteLog(f, "InternetOpenA() succeeded");
	

	HINTERNET hHttpSession = InternetConnectA(hIntSession, "api.e-guma.ch",INTERNET_DEFAULT_HTTP_PORT, NULL,NULL,INTERNET_SERVICE_HTTP,0,0);

	WriteLog(f, "InternetConnectA() succeeded");


	std::string url = string("v1/vouchers/") + string(code) + string("/activate.json?apikey=") + string(apiKey);
    HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "POST", url.c_str(), 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	WriteLog(f, "HttpOpenRequestA() succeeded");
	
    CHAR* szHeaders = "Content-Type: application/json";
    CHAR szReq[1024] = "";
    if( !HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szReq, strlen(szReq))) {
		DWORD dwErr = GetLastError();
      
		SetErrorMessage(error, "HttpSendRequest() failed!");
		WriteLog(f, "HttpSendRequestA() failded");

		return false;
    }

	WriteLog(f, "HttpSendRequestA() suceeded");

	// todo: - error if not 200 OK
	//       - remove while


    CHAR json[1025];
    DWORD dwRead=0;
    while(::InternetReadFile(hHttpRequest, json, sizeof(json)-1, &dwRead) && dwRead) {
      json[dwRead] = 0;
      
		*amountInCents = GetNumber(json, "amount_in_cents");
		
		// code
		if (codeOut != NULL)
		{
			std::string code = GetString(json, "code");
			sprintf(codeOut, "%s", code.c_str()); 
		}
		

      dwRead=0;
    }

	fprintf(f, "Amount in Cents:%i\n", *amountInCents);
	fprintf(f, "Code out:%s\n", codeOut);
	fflush(f);

		
	WriteLog(f, "Done! YES!");
	fclose(f);


    ::InternetCloseHandle(hHttpRequest);
    ::InternetCloseHandle(hHttpSession);
    ::InternetCloseHandle(hIntSession);

	return true;
}

bool Deactivate(char* apiKey, char* code, int* amountInCents, char* codeOut, char* error)
{
	FILE *f = fopen("Deactivate.txt", "w");

	fprintf(f, "API-Key:%s\n", apiKey);
	fprintf(f, "Code:%s\n", code);
	fflush(f);


	HINTERNET hIntSession = InternetOpenA("EgumaWinCE",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	
	if (hIntSession == NULL)
	{
		SetErrorMessage(error, "InternetOpen() failed!");
		WriteLog(f, "InternetOpenA() failed");
		return false;
	}

	WriteLog(f, "InternetOpenA() succeeded");
	

	HINTERNET hHttpSession = InternetConnectA(hIntSession, "api.e-guma.ch",INTERNET_DEFAULT_HTTP_PORT, NULL,NULL,INTERNET_SERVICE_HTTP,0,0);

	WriteLog(f, "InternetConnectA() succeeded");


	std::string url = string("v1/vouchers/") + string(code) + string("/deactivate.json?apikey=") + string(apiKey);
    HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "POST", url.c_str(), 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	WriteLog(f, "HttpOpenRequestA() succeeded");
	
    CHAR* szHeaders = "Content-Type: application/json";
    CHAR szReq[1024] = "";
    if( !HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szReq, strlen(szReq))) {
		DWORD dwErr = GetLastError();
      
		SetErrorMessage(error, "HttpSendRequest() failed!");
		WriteLog(f, "HttpSendRequestA() failded");

		return false;
    }

	WriteLog(f, "HttpSendRequestA() suceeded");

	// todo: - error if not 200 OK
	//       - remove while


    CHAR json[1025];
    DWORD dwRead=0;
    while(::InternetReadFile(hHttpRequest, json, sizeof(json)-1, &dwRead) && dwRead) {
      json[dwRead] = 0;
      
		*amountInCents = GetNumber(json, "amount_in_cents");
		
		// code
		if (codeOut != NULL)
		{
			std::string code = GetString(json, "code");
			sprintf(codeOut, "%s", code.c_str()); 
		}
		

      dwRead=0;
    }

	fprintf(f, "Amount in Cents:%i\n", *amountInCents);
	fprintf(f, "Code out:%s\n", codeOut);
	fflush(f);

		
	WriteLog(f, "Done! YES!");
	fclose(f);


    ::InternetCloseHandle(hHttpRequest);
    ::InternetCloseHandle(hHttpSession);
    ::InternetCloseHandle(hIntSession);

	return true;
}

bool Hello()
{
	FILE *f = fopen("Hello.txt", "w");

	HINTERNET hIntSession = InternetOpenA("HTTPGET",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	
	if (hIntSession == NULL)
	{
		WriteLog(f, "InternetOpenA() failed");
		return false;
	}
	
	WriteLog(f, "InternetOpenA() succeeded");


	HINTERNET hHttpSession = InternetConnectA(hIntSession, "api.e-guma.ch",INTERNET_DEFAULT_HTTP_PORT, NULL,NULL,INTERNET_SERVICE_HTTP,0,0);

	WriteLog(f, "InternetConnectA() succeeded");

	std::string url = string("v1/hello.json");

    HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", url.c_str(), 0, 0, 0, INTERNET_FLAG_RELOAD, 0);

	WriteLog(f, "HttpOpenRequestA() succeeded");

	
    CHAR* szHeaders = "Content-Type: application/json";
    CHAR szReq[1024] = "";
    if( !HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szReq, strlen(szReq))) {
		
		DWORD dwErr = GetLastError();
		WriteLog(f, "HttpSendRequestA() failed");

		return false;
    }

	WriteLog(f, "HttpSendRequestA() succeeded");

	// todo: - error if not 200 OK
	//       - remove while


    CHAR json[1025];
    DWORD dwRead=0;
    ::InternetReadFile(hHttpRequest, json, sizeof(json)-1, &dwRead);
      
	WriteLog(f, "InternetReadFile() succeeded");
	
	json[dwRead] = 0;
  
	if (json[0] != 'O' && json[1] != 'K')
	{
		WriteLog(f, "No OK from Server...");
		return false;
	}


	WriteLog(f, "Done! YES!");
	fclose(f);

    ::InternetCloseHandle(hHttpRequest);
    ::InternetCloseHandle(hHttpSession);
    ::InternetCloseHandle(hIntSession);	

	return true;
}
