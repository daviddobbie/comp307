// This file allows compilation of the program dependent on any settings that are specific to an implementation

// just comment out the following as neccesary, or add your own

#ifndef comh
#define comh

#ifdef _WIN32
  #define isnan _isnan
  #define random rand
  #define srandom(seed) srand((unsigned int)seed)
#endif

#ifdef Use_Render
#include "../Render/common.h"
#endif

#ifdef Use_Theories
#include "../Theories/common.h"
#endif

#ifdef Use_Classify
#include "../Classify/common.h"
#endif

#ifdef Use_ClassifyStress
#include "../ClassifyStress/common.h"
#endif

#ifdef Use_Classify2
#include "../Classify2/common.h"
#endif

#ifdef Use_SimpleClassify
#include "../SimpleClassify/common.h"
#endif

#ifdef Use_XOR
#include "../XOR/common.h"
#endif

#ifdef Use_SymRegression
#include "../SymRegression/common.h"
#endif

#ifdef Use_regression
#include "../regression/common.h"
#endif

#ifdef Use_UltClassify
#include "../UltClassify/common.h"
#endif

#ifdef Use_ClassifyGD
#include "../ClassifyGD/common.h"
#endif

#ifdef Use_Locator
#include "../Locator/common.h"
#endif

#ifdef Use_Locator2
#include "../Locator2/common.h"
#endif

#ifdef Use_RefCls
#include "../RefCls/common.h"
#endif

extern long g_verbose;
#ifndef PERR
#define PERR ((g_verbose%100)>0)
#endif

#ifndef POUT
#define POUT(i) ((g_verbose%100)>=i)
#endif

void *mymalloc(long siz);
void myfree(void *ptr,long siz);

#endif
