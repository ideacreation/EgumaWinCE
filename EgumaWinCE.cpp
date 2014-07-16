/*  
 Copyright (c) 2008-2014 Idea Creation GmbH

 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:

 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "stdafx.h"
#include "EgumaWinCE.h"
#include <wininet.h>
#include <string>
#include <ctype.h>

using namespace std;

#pragma comment( lib, "wininet" )


#define VERSION_NUMBER "1.0.0.0" // when you update it, do it also in version.rc


enum HttpMethod
{
	GET,
	POST
};


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


string GetString(const string& json, const string& key)
{
	// todo: if (found!=string::npos)

	string keyWithQuotes = "\"" + key + "\"";
	string::size_type keyStartPos = json.find(keyWithQuotes);
	string::size_type keyEndPos = keyStartPos + keyWithQuotes.length();

	string::size_type valueStartPos = json.find('\"', keyEndPos+1) + 1;
	string::size_type valueEndPos = json.find('\"', valueStartPos) - 1;


	string value = json.substr(valueStartPos, valueEndPos - valueStartPos + 1);


	return value;
}

bool GetBool(const string& json, const string& key)
{
	// todo: if (found!=string::npos)

	string keyWithQuotes = "\"" + key + "\"";
	string::size_type keyStartPos = json.find(keyWithQuotes);
	string::size_type colonPos = json.find(':', keyStartPos);

	string::size_type pos = colonPos + 1;

	if (json[pos] == 't')
		return true;

	return false;
}

int GetNumber(const string& json, const string& key)
{
	// todo: if (found!=string::npos)

	string keyWithQuotes = "\"" + key + "\"";
	string::size_type keyStartPos = json.find(keyWithQuotes);
	string::size_type colonPos = json.find(':', keyStartPos);
   
	string::size_type pos = colonPos + 1;

	string numberAsString;

	while (isdigit(json[pos]))
	{
		numberAsString += json[pos++];
	}


	return atoi(numberAsString.c_str());
}

void SetErrorMessage(char* error, const char* message)
{
	if (error == NULL)
		return;

	sprintf(error, "%s", message);
}

void WriteLogHeader(FILE* f)
{
	fprintf(f, "Dll Version: %s\n", VERSION_NUMBER);
	fflush(f);
}

void WriteLog(FILE* f, const char* text)
{
	fprintf(f, "%s\n", text);
	fflush(f);
}

void WriteLog(FILE* f, const char* name, const char* value)
{
	fprintf(f, "%s: %s\n", name, value);
	fflush(f);
}

void WriteLog(FILE* f, char* name, int value)
{
	fprintf(f, "%s: %i\n", name, value);
	fflush(f);
}


bool SendHttpRequest(const string& url, HttpMethod httpMethod, char* postData, string& response, char* error, FILE* logFile)
{
	HINTERNET hIntSession = InternetOpenA("EgumaWinCE",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	
	if (hIntSession == NULL)
	{
		SetErrorMessage(error, "InternetOpen() failed!");
		WriteLog(logFile, "InternetOpenA() failed");
		return false;
	}
	WriteLog(logFile, "InternetOpenA() succeeded");
	

	HINTERNET hHttpSession = InternetConnectA(hIntSession, "api.e-guma.ch",INTERNET_DEFAULT_HTTP_PORT, NULL,NULL,INTERNET_SERVICE_HTTP,0,0);
	if (hHttpSession == NULL)
	{
		SetErrorMessage(error, "InternetConnectA() failed!");
		WriteLog(logFile, "InternetConnectA() failed");
		return false;
	}
	WriteLog(logFile, "InternetConnectA() succeeded");


	char* httpMethodAsString = NULL;
	if (httpMethod == GET)
		httpMethodAsString = "GET";
	else if (httpMethod == POST)
		httpMethodAsString = "POST";

	HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, httpMethodAsString, url.c_str(), 0, 0, 0, INTERNET_FLAG_RELOAD, 0);
	if (hHttpRequest == NULL)
	{
		SetErrorMessage(error, "HttpOpenRequestA() failed!");
		WriteLog(logFile, "HttpOpenRequestA() failed");
		return false;
	}
	WriteLog(logFile, "HttpOpenRequestA() succeeded");
	
	
	char* headers = NULL;
	if (httpMethod == POST)
		headers = "Content-Type: application/x-www-form-urlencoded";
	else
		headers = "Content-Type: application/json";

    
	int postDataSize = 0;
	if (postData != NULL)
		postDataSize = strlen(postData);

    if( !HttpSendRequestA(hHttpRequest, headers, strlen(headers), postData, postDataSize)) {
		
		DWORD errorCode = GetLastError();
		
		char errorMsg[1024];
		sprintf(errorMsg, "Can not connect to the E-GUMA Server. Please ensure that the workstation has access to the Internet. Error Code '%d'", errorCode);

		SetErrorMessage(error, errorMsg);
		WriteLog(logFile, errorMsg);

		return false;
    }
	WriteLog(logFile, "HttpSendRequestA() suceeded");


	char statusCodeBuffer[32];
	DWORD statusCodeSize = sizeof(statusCodeBuffer);
	if (!HttpQueryInfoA(hHttpRequest, HTTP_QUERY_STATUS_CODE, &statusCodeBuffer, &statusCodeSize, NULL))
	{      
		SetErrorMessage(error, "HttpQueryInfoA() failed!");
		WriteLog(logFile, "HttpQueryInfoA() failded");

		return false;
	}
	
	statusCodeBuffer[statusCodeSize] = '\0';
	int statusCode = atoi(statusCodeBuffer);

	WriteLog(logFile, "Status Code", statusCode);


	char responseBuffer[1025];
    DWORD dwRead=0;
    while(InternetReadFile(hHttpRequest, responseBuffer, sizeof(responseBuffer)-1, &dwRead) && dwRead)
	{
		responseBuffer[dwRead] = 0;

		WriteLog(logFile, "Response Data", responseBuffer);

		response += responseBuffer;

		dwRead=0;
	}

    InternetCloseHandle(hHttpRequest);
    InternetCloseHandle(hHttpSession);
    InternetCloseHandle(hIntSession);

	if (statusCode != 200)
	{
		sprintf(error, response.c_str(), response.length());
		return false;
	}


	return true;
}

void GetBalance(char* apiKey, char* code, char* codeOut, int* isRedeemable, 
				int* balanceInCents, int* totalAmountInCents, char* message, 
				char* error, int* hasError)
{
	*hasError = 0;

	FILE* logFile = fopen("EgumaBalance.txt", "w");

	WriteLogHeader(logFile);
	WriteLog(logFile, "API-Key", apiKey);
	WriteLog(logFile, "Code", code);


	string url = string("v1/vouchers/") + string(code) + string("/balance.json?apikey=") + string(apiKey);
	string json;
	
	if (!SendHttpRequest(url, GET, NULL, json, error, logFile))
	{  
		*hasError = 1;
		return;
	}

	
	*isRedeemable = GetBool(json, "is_redeemable");
	*balanceInCents = GetNumber(json, "balance_in_cents");
	*totalAmountInCents = GetNumber(json, "total_amount_in_cents");

	string codeTmp = GetString(json, "code");
	sprintf(codeOut, "%s", codeTmp.c_str()); 

	string msg = GetString(json, "message");
	sprintf(message, "%s", msg.c_str());
	
	
	WriteLog(logFile, "Balance in Cents", *balanceInCents);
	WriteLog(logFile, "Code out", codeOut);
	WriteLog(logFile, "Done!");

	fclose(logFile);
}


void Redeem(char* apiKey, char* code, int amountInCents, char* codeOut, 
			int* balanceInCents, char* error, int* hasError)
{
	*hasError = 0;

	FILE* logFile = fopen("EgumaRedeem.txt", "w");

	WriteLog(logFile, "API-Key", apiKey);
	WriteLog(logFile, "Code", code);
	WriteLog(logFile, "AmountInCents", amountInCents);


	string url = string("v1/vouchers/") + string(code) + string("/redeem.json?apikey=") + string(apiKey);
	char postData[1024];
	sprintf(postData, "amount_in_cents=%i", amountInCents);
	string json;

	if (!SendHttpRequest(url, POST, postData, json, error, logFile))
	{  
		*hasError = 1;
		return;
	}
	
	*balanceInCents = GetNumber(json, "balance_in_cents");

	string codeTmp = GetString(json, "code");
	sprintf(codeOut, "%s", codeTmp.c_str()); 


	WriteLog(logFile, "Balance in Cents", *balanceInCents);
	WriteLog(logFile, "Code out", codeOut);
	WriteLog(logFile, "Done!");

	fclose(logFile);
}

void CancelRedemption(char* apiKey, char* code, int amountInCents, char* codeOut,
					  int* balanceInCents, char* error, int* hasError)
{
	*hasError = 0;

	FILE* logFile = fopen("EgumaCancelRedemption.txt", "w");

	WriteLog(logFile, "API-Key", apiKey);
	WriteLog(logFile, "Code", code);
	WriteLog(logFile, "AmountInCents", amountInCents);


	string url = string("v1/vouchers/") + string(code) + string("/cancel_redemption.json?apikey=") + string(apiKey);
	char postData[1024];
	sprintf(postData, "amount_in_cents=%i", amountInCents);
	string json;

	if (!SendHttpRequest(url, POST, postData, json, error, logFile))
	{  
		*hasError = 1;
		return;
	}

	
	*balanceInCents = GetNumber(json, "balance_in_cents");

	string codeTmp = GetString(json, "code");
	sprintf(codeOut, "%s", codeTmp.c_str()); 


	WriteLog(logFile, "Balance in Cents", *balanceInCents);
	WriteLog(logFile, "Code out", codeOut);
	WriteLog(logFile, "Done!");

	fclose(logFile);
}

void DepotStatus(char* apiKey, char* code, int* amountInCents, int* canBeActivated,
				 int* canBeDeactivated, char* codeOut, char* error, int* hasError)
{
	*hasError = 0;

	FILE* logFile = fopen("EgumaDepotStatus.txt", "w");

	WriteLog(logFile, "API-Key", apiKey);
	WriteLog(logFile, "Code", code);
	

	string url = string("v1/vouchers/") + string(code) + string("/depot_status.json?apikey=") + string(apiKey);
	string json;

	if (!SendHttpRequest(url, GET, NULL, json, error, logFile))
	{  
		*hasError = 1;
		return;
	}


	*amountInCents = GetNumber(json, "amount_in_cents");

	*canBeActivated = GetBool(json, "can_be_activated");
	*canBeDeactivated = GetBool(json, "can_be_deactivated");
	
	string codeTemp = GetString(json, "code");
	sprintf(codeOut, "%s", codeTemp.c_str()); 
		

	WriteLog(logFile, "Amount in Cents", *amountInCents);
	WriteLog(logFile, "Code out", codeOut);
	WriteLog(logFile, "Done!");

	fclose(logFile);
}

void Activate(char* apiKey, char* code, int* amountInCents, char* codeOut, char* error, int* hasError)
{
	*hasError = 0;

	FILE* logFile = fopen("EgumaActivate.txt", "w");

	WriteLog(logFile, "API-Key", apiKey);
	WriteLog(logFile, "Code", code);

	string url = string("v1/vouchers/") + string(code) + string("/activate.json?apikey=") + string(apiKey);
	string json;

	if (!SendHttpRequest(url, POST, NULL, json, error, logFile))
	{  
		*hasError = 1;
		return;
	}

	
	*amountInCents = GetNumber(json, "amount_in_cents");
		
	string codeTmp = GetString(json, "code");
	sprintf(codeOut, "%s", codeTmp.c_str());
	
	
	WriteLog(logFile, "Amount in Cents", *amountInCents);
	WriteLog(logFile, "Code out", codeOut);
	WriteLog(logFile, "Done!");

	fclose(logFile);
}

void Deactivate(char* apiKey, char* code, int* amountInCents, char* codeOut, char* error, int* hasError)
{
	*hasError = 0;

	FILE* logFile = fopen("EgumaDeactivate.txt", "w");

	WriteLog(logFile, "API-Key", apiKey);
	WriteLog(logFile, "Code", code);

	string url = string("v1/vouchers/") + string(code) + string("/deactivate.json?apikey=") + string(apiKey);
	string json;

	if (!SendHttpRequest(url, POST, NULL, json, error, logFile))
	{  
		*hasError = 1;
		return;
	}

	
	*amountInCents = GetNumber(json, "amount_in_cents");
		
	string codeTmp = GetString(json, "code");
	sprintf(codeOut, "%s", codeTmp.c_str());
	
	
	WriteLog(logFile, "Amount in Cents", *amountInCents);
	WriteLog(logFile, "Code out", codeOut);
	WriteLog(logFile, "Done!");

	fclose(logFile);
}
