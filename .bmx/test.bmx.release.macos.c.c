#include <stdint.h>
#include <stdlib.h>
//#define ASSERT(C) ...
#ifdef BMAX_64_BIT
  //typedef union { ... } ANY;
  #error 64-bit not supported; try the NG compiler
#else
  typedef union { 
    int32_t i; float f; void * p; void *(*k)(void);
    uint8_t c; uint16_t s; uint8_t ca[4]; uint16_t sa[2];
  } ANY;
  //ASSERT(sizeof(ANY) == ...)
  //ASSERT(sizeof(int32_t) == sizeof(intptr_t))
#endif
extern ANY __bb_blitz_blitz;
extern ANY bbEmptyString;
extern ANY bbEnd;
extern ANY bbGCFree;
extern ANY bbObjectClass;
extern ANY bbObjectCompare;
extern ANY bbObjectCtor;
extern ANY bbObjectFree;
extern ANY bbObjectRegisterType;
extern ANY bbObjectReserved;
extern ANY bbObjectSendMessage;
extern ANY bbObjectToString;
extern ANY bbStringClass;
extern ANY brl_blitz_NullFunctionError;
static int32_t _44;
static int32_t _40;
static char * _4;
static char * _5;
static char * _6;
static char * _7;
static char * _8;
static char * _9;
static char * _10;
static char * _11;
static char * _12;
static char * _13;
static char * _14;
static ANY _3[];
ANY bb_Baz[];
float _bb_Baz_X;
int32_t bb_C;
int64_t bb_D;
double bb_E;
float bb_F;
int32_t bb_G;
static int32_t _43;
static ANY _1[];
static float _73;
static float _81;
int32_t __bb_blitzmax_test2(void);
int32_t bb_Foo(int32_t p0);
int32_t bb_Bar(int32_t p0);
int32_t _bb_Baz_New(ANY * self);
int32_t _bb_Baz_Delete(ANY * self);
int32_t _bb_Baz_M(ANY * self);
float _bb_Baz_A(void);
int64_t _bb_Baz_B(void * p0, double p1, int32_t p2, int32_t p3);
static float _2(void);
int32_t __bb_blitzmax_test2(void) {
  ANY eax, edx, ecx, ebx, esi, edi;
  if (dword [_44] == 0) goto _45;
  eax = 0;
  return eax.i;
_45:
  dword [_44] = 1;
	call	__bb_blitz_blitz
  eax = dword [_40];
  eax &= 1;
  if (eax != 0) goto _41;
	call	dword [bb_Baz+52]
  dword [_bb_Baz_X] = fp0;
	or	dword [_40],1
_41:
	push	bb_Baz
	call	bbObjectRegisterType
	add	esp,4
  eax = dword [_40];
  eax &= 2;
  if (eax != 0) goto _42;
	mov	eax,dword [bb_Baz+52]
  dword [bb_G] = eax;
	or	dword [_40],2
_42:
	call	bbEnd
  eax = 0;
  goto _15;
_15:
  return eax.i;
}
int32_t bb_Foo(int32_t p0) {
  ANY eax, edx, ecx, ebx, esi, edi;
  eax = dword [ebp+8];
  edx = eax;
  edx *= 2;
  eax += edx;
  eax += 1;
  goto _18;
_18:
  return eax.i;
}
int32_t bb_Bar(int32_t p0) {
  ANY eax, edx, ecx, ebx, esi, edi;
  eax = dword [ebp+8];
  eax += 3;
	push	eax
	call	bb_Foo
	add	esp,4
  goto _21;
_21:
  return eax.i;
}
int32_t _bb_Baz_New(ANY * self) {
  ANY eax, edx, ecx, ebx, esi, edi;
  ebx = dword [ebp+8];
	push	ebx
	call	bbObjectCtor
	add	esp,4
  dword [ebx] = bb_Baz;
  eax = bbEmptyString;
  ++dword [eax+4];
  dword [ebx+8] = eax;
  eax = 0;
  goto _24;
_24:
  return eax.i;
}
int32_t _bb_Baz_Delete(ANY * self) {
  ANY eax, edx, ecx, ebx, esi, edi;
  eax = dword [ebp+8];
_27:
  eax = dword [eax+8];
  if(--dword [eax+4]) goto _51;
	push	eax
	call	bbGCFree
	add	esp,4
_51:
  eax = 0;
  goto _49;
_49:
  return eax.i;
}
int32_t _bb_Baz_M(ANY * self) {
  ANY eax, edx, ecx, ebx, esi, edi;
  esi = dword [ebp+8];
  ebx = _1;
  ++dword [ebx+4];
  eax = dword [esi+8];
  if(--dword [eax+4]) goto _55;
	push	eax
	call	bbGCFree
	add	esp,4
_55:
  dword [esi+8] = ebx;
  eax = 0;
  goto _30;
_30:
  return eax.i;
}
float _bb_Baz_A(void) {
  ANY eax, edx, ecx, ebx, esi, edi;
float retv;
  fp0 = dword [_73];
  goto _32;
_32:
  return retv;
}
int64_t _bb_Baz_B(void * p0, double p1, int32_t p2, int32_t p3) {
  ANY eax, edx, ecx, ebx, esi, edi;
  ANY v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15;
int64_t retv;
  edx = dword [ebp+8];
	mov	eax,dword [ebp+20]
  dword [ebp-8] = eax;
	mov	eax,dword [ebp+24]
  dword [ebp-4] = eax;
  dword [ebp-12] = 5;
  dword [ebp-16] = 0;
  goto _36;
_36:
	mov	eax,dword [ebp-12]
  dword [edx+4] = eax;
	mov	eax,dword [ebp-16]
  dword [edx] = eax;
  return retv;
}
static float _2(void) {
  ANY eax, edx, ecx, ebx, esi, edi;
float retv;
  fp0 = dword [_81];
  goto _38;
_38:
  return retv;
}
static int32_t _44 = 0;
static int32_t _40 = 0;
static char * _4 = (char[]){"Baz"};
static char * _5 = (char[]){"msg"};
static char * _6 = (char[]){"$"};
static char * _7 = (char[]){"New"};
static char * _8 = (char[]){"()i"};
static char * _9 = (char[]){"Delete"};
static char * _10 = (char[]){"M"};
static char * _11 = (char[]){"A"};
static char * _12 = (char[]){"()f"};
static char * _13 = (char[]){"B"};
static char * _14 = (char[]){"(d,l)l"};
static ANY _3[] = {
  (ANY){ .i = 2 },
  (ANY){ .p = NULL },
  (ANY){ .i = 3 },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .i = 8 },
  (ANY){ .i = 6 },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .i = 16 },
  (ANY){ .i = 6 },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .i = 20 },
  (ANY){ .i = 6 },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .i = 48 },
  (ANY){ .i = 7 },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .i = 52 },
  (ANY){ .i = 7 },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .i = 56 },
  (ANY){ .i = 0 },
};
ANY bb_Baz[] = {
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .i = 12 },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
  (ANY){ .p = NULL },
};
float _bb_Baz_X = 0;
int32_t bb_C = 65;
int64_t bb_D = 650000000000;
double bb_E = 19.6;
float bb_F = 23.4;
int32_t bb_G = 0;
static int32_t _43 = 49;
static ANY _1[] = {
  (ANY){ .p = NULL },
  (ANY){ .i = 2147483647 },
  (ANY){ .sa = {105,110} },
  (ANY){ .sa = {32,109} },
};
static float _73 = 5.5;
static float _81 = 5.5;
int32_t __bb_blitzmax_test(void) {
  _3[1].p = (void *)_4;
  _3[3].p = (void *)_5;
  _3[4].p = (void *)_6;
  _3[7].p = (void *)_7;
  _3[8].p = (void *)_8;
  _3[11].p = (void *)_9;
  _3[12].p = (void *)_8;
  _3[15].p = (void *)_10;
  _3[16].p = (void *)_8;
  _3[19].p = (void *)_11;
  _3[20].p = (void *)_12;
  _3[23].p = (void *)_13;
  _3[24].p = (void *)_14;
  bb_Baz[0] = bbObjectClass;
  bb_Baz[1] = bbObjectFree;
  bb_Baz[2].p = (void *)_3;
  bb_Baz[4].p = (void *)_bb_Baz_New;
  bb_Baz[5].p = (void *)_bb_Baz_Delete;
  bb_Baz[6] = bbObjectToString;
  bb_Baz[7] = bbObjectCompare;
  bb_Baz[8] = bbObjectSendMessage;
  bb_Baz[9] = bbObjectReserved;
  bb_Baz[10] = bbObjectReserved;
  bb_Baz[11] = bbObjectReserved;
  bb_Baz[12].p = (void *)_bb_Baz_M;
  bb_Baz[13].p = (void *)_bb_Baz_A;
  bb_Baz[14].p = (void *)_bb_Baz_B;
  bb_G = brl_blitz_NullFunctionError.i;
  _1[0] = bbStringClass;
  return __bb_blitzmax_test2();
}
