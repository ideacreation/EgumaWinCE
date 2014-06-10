extern "C" __declspec(dllexport) bool GetBalance(char* apiKey, char* code, char* codeOut, bool* isRedeemable, int* balanceInCents, int* totalAmountInCents, char* messageOut, char* error);
extern "C" __declspec(dllexport) bool Redeem(char* apiKey, char* code, int amountInCents, char* codeOut, int* balanceInCents, char* error);
extern "C" __declspec(dllexport) bool Redeem2(char* apiKey, char* code, int* amountInCents, char* codeOut, int* balanceInCents, char* error);
extern "C" __declspec(dllexport) bool CancelRedemption(char* apiKey, char* code, int amountInCents, char* codeOut, int* balanceInCents, char* error);
extern "C" __declspec(dllexport) bool DepotStatus(char* apiKey, char* code, int* amountInCents, bool* canBeActivated, bool* canBeDeactivated, char* codeOut, char* error);
extern "C" __declspec(dllexport) bool Activate(char* apiKey, char* code, int* amountInCents, char* codeOut, char* error);
extern "C" __declspec(dllexport) bool Deactivate(char* apiKey, char* code, int* amountInCents, char* codeOut, char* error);

extern "C" __declspec(dllexport) bool Hello();


