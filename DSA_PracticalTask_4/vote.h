#ifndef H_VOTE
#define H_VOTE

#include <windows.h>

/// <summary>
/// Результат голосования за команду
/// </summary>
struct vote
{
   ULONGLONG team = 0, first = 0, last = 0, top = 0;
};
#endif