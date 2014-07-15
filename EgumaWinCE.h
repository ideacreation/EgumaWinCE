extern "C" __declspec(dllexport) void GetBalance(char* apiKey, char* code, char* codeOut, bool* isRedeemable, int* balanceInCents, int* totalAmountInCents, char* message, char* error, bool* hasError);
extern "C" __declspec(dllexport) void Redeem(char* apiKey, char* code, int amountInCents, char* codeOut, int* balanceInCents, char* error, bool* hasError);
extern "C" __declspec(dllexport) void CancelRedemption(char* apiKey, char* code, int amountInCents, char* codeOut, int* balanceInCents, char* error, bool* hasError);
extern "C" __declspec(dllexport) void DepotStatus(char* apiKey, char* code, int* amountInCents, bool* canBeActivated, bool* canBeDeactivated, char* codeOut, char* error, bool* hasError);
extern "C" __declspec(dllexport) void Activate(char* apiKey, char* code, int* amountInCents, char* codeOut, char* error, bool* hasError);
extern "C" __declspec(dllexport) void Deactivate(char* apiKey, char* code, int* amountInCents, char* codeOut, char* error, bool* hasError);
