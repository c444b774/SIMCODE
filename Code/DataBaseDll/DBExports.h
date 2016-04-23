#ifdef DB_EXPORTS
#define DB_API extern "C" __declspec(dllexport)
#else
#define DB_API extern "C" __declspec(dllimport)
#endif

