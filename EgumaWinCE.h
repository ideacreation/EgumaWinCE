extern "C" __declspec(dllexport) void GetBalance(char* apiKey, char* code, char* codeOut, int* isRedeemable, int* balanceInCents, int* totalAmountInCents, char* message, char* error, int* hasError);
extern "C" __declspec(dllexport) void Redeem(char* apiKey, char* code, int amountInCents, char* codeOut, int* balanceInCents, char* error, int* hasError);
extern "C" __declspec(dllexport) void CancelRedemption(char* apiKey, char* code, int amountInCents, char* codeOut, int* balanceInCents, char* error, int* hasError);
extern "C" __declspec(dllexport) void DepotStatus(char* apiKey, char* code, int* amountInCents, int* canBeActivated, int* canBeDeactivated, char* codeOut, char* error, int* hasError);
extern "C" __declspec(dllexport) void Activate(char* apiKey, char* code, int* amountInCents, char* codeOut, char* error, int* hasError);
extern "C" __declspec(dllexport) void Deactivate(char* apiKey, char* code, int* amountInCents, char* codeOut, char* error, int* hasError);

extern "C" __declspec(dllexport) void Hello();

// We use int instead of bool as parameters. In Embededd Visual C++ bools are 4 byte and in Visual Studio 2003 1 byte.
// More info: http://stackoverflow.com/questions/4608876/c-sharp-dllimport-with-c-boolean-function-not-returning-correctly