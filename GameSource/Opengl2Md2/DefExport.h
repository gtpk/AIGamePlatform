#pragma once

#ifdef __COMPILING_MYLIB
#define DllExport __declspec(dllimport)
#else
#define DllExport __declspec(dllexport)
#endif