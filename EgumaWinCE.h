extern "C" __declspec(dllexport) bool GetBalance(char* apiKey, char* code, char* codeOut, bool* isRedeemable, int* balanceInCents, int* totalAmountInCents, char* messageOut, char* error);
extern "C" __declspec(dllexport) bool Hello();


// Tests
extern "C" __declspec(dllexport) void TestLogOnly();
extern "C" __declspec(dllexport) void TestLogStringParam(char* text);
extern "C" __declspec(dllexport) void TestReturnStringAsParam(char* result);
extern "C" __declspec(dllexport) void TestReturnIntAsParam(int* result);


