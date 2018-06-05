// #define NDEBUG

#if __cplusplus

#include <cstdio>
#include <cassert>
#warning "This is cplusplus"
using namespace std;

#else

#include <stdio.h>
#include <assert.h>
#warning "This is C"

#endif

#if _WIN32

#include <windows.h>

#endif

#ifdef DEBUG // Defined with `gcc filename -DDEBUG`

#warning "Debug mode.."

#endif

int main()
{
  printf("compile date:%s\n", __DATE__);
  printf("compile time:%s\n", __TIME__);
  printf("file name:%s\n", __FILE__);
  printf("compile is std C ?:%d\n", __STDC__);
  printf("counrter:%d\n", __COUNTER__);
  printf("counrter:%d\n", __COUNTER__);
  printf("counrter:%d\n", __COUNTER__);
  printf("counrter:%d\n", __COUNTER__);
  printf("counrter:%d\n", __COUNTER__);

  assert(1 == 0);
  return 0;
}
