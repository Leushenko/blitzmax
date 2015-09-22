#include <stdint.h>
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
int32_t _bb_main(void);extern ANY __bb_blitz_blitz;
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
int32_t _bb_main2(void);
int32_t bb_Foo(int32_t p0);
int32_t bb_Bar(int32_t p0);
int32_t _bb_Baz_New(ANY * self);
int32_t _bb_Baz_Delete(ANY * self);
int32_t _bb_Baz_M(ANY * self);
float _bb_Baz_A(void);
int64_t _bb_Baz_B(void * p0, double p1, int32_t p2, int32_t p3);
static float _2(void);
int32_t _bb_main2(void) {
  ANY eax, edx, ecx, ebx, esi, edi;
  if (dword [_44] == 0) goto _45;
	mov	eax,0
  return eax.i;
_45:
	mov	dword [_44],1
	call	__bb_blitz_blitz
	mov	eax,dword [_40]
	and	eax,1
  if (eax != 0) goto _41;
	call	dword [bb_Baz+52]
	mov	dword [_bb_Baz_X],fp0
	or	dword [_40],1
_41:
	push	bb_Baz
	call	bbObjectRegisterType
	add	esp,4
	mov	eax,dword [_40]
	and	eax,2
  if (eax != 0) goto _42;
	mov	eax,dword [bb_Baz+52]
	mov	dword [bb_G],eax
	or	dword [_40],2
_42:
	call	bbEnd
	mov	eax,0
	jmp	_15
_15:
  return eax.i;
  return ((int32_t)0);
}
int32_t bb_Foo(int32_t p0) {
  ANY eax, edx, ecx, ebx, esi, edi;
	mov	eax,dword [ebp+8]
	mov	edx,eax
	shl	edx,1
	add	eax,edx
	add	eax,1
	jmp	_18
_18:
  return eax.i;
  return ((int32_t)0);
}
int32_t bb_Bar(int32_t p0) {
  ANY eax, edx, ecx, ebx, esi, edi;
	mov	eax,dword [ebp+8]
	add	eax,3
	push	eax
	call	bb_Foo
	add	esp,4
	jmp	_21
_21:
  return eax.i;
  return ((int32_t)0);
}
int32_t _bb_Baz_New(ANY * self) {
  ANY eax, edx, ecx, ebx, esi, edi;
	mov	ebx,dword [ebp+8]
	push	ebx
	call	bbObjectCtor
	add	esp,4
	mov	dword [ebx],bb_Baz
	mov	eax,bbEmptyString
	inc	dword [eax+4]
	mov	dword [ebx+8],eax
	mov	eax,0
	jmp	_24
_24:
  return eax.i;
  return ((int32_t)0);
}
int32_t _bb_Baz_Delete(ANY * self) {
  ANY eax, edx, ecx, ebx, esi, edi;
	mov	eax,dword [ebp+8]
_27:
	mov	eax,dword [eax+8]
	dec	dword [eax+4]
	jnz	_51
	push	eax
	call	bbGCFree
	add	esp,4
_51:
	mov	eax,0
	jmp	_49
_49:
  return eax.i;
  return ((int32_t)0);
}
int32_t _bb_Baz_M(ANY * self) {
  ANY eax, edx, ecx, ebx, esi, edi;
	mov	esi,dword [ebp+8]
	mov	ebx,_1
	inc	dword [ebx+4]
	mov	eax,dword [esi+8]
	dec	dword [eax+4]
	jnz	_55
	push	eax
	call	bbGCFree
	add	esp,4
_55:
	mov	dword [esi+8],ebx
	mov	eax,0
	jmp	_30
_30:
  return eax.i;
  return ((int32_t)0);
}
float _bb_Baz_A(void) {
  ANY eax, edx, ecx, ebx, esi, edi;
	mov	fp0,dword [_73]
	jmp	_32
_32:
  return retv;
  return ((float)0);
}
int64_t _bb_Baz_B(void * p0, double p1, int32_t p2, int32_t p3) {
  ANY eax, edx, ecx, ebx, esi, edi;
  ANY v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15;
	mov	edx,dword [ebp+8]
	mov	eax,dword [ebp+20]
	mov	dword [ebp-8],eax
	mov	eax,dword [ebp+24]
	mov	dword [ebp-4],eax
	mov	dword [ebp-12],5
	mov	dword [ebp-16],0
	jmp	_36
_36:
	mov	eax,dword [ebp-12]
	mov	dword [edx+4],eax
	mov	eax,dword [ebp-16]
	mov	dword [edx],eax
  return retv;
  return ((int64_t)0);
}
static float _2(void) {
  ANY eax, edx, ecx, ebx, esi, edi;
	mov	fp0,dword [_81]
	jmp	_38
_38:
  return retv;
  return ((float)0);
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
  (ANY){ .p = _4 },
  (ANY){ .i = 3 },
  (ANY){ .p = _5 },
  (ANY){ .p = _6 },
  (ANY){ .i = 8 },
  (ANY){ .i = 6 },
  (ANY){ .p = _7 },
  (ANY){ .p = _8 },
  (ANY){ .i = 16 },
  (ANY){ .i = 6 },
  (ANY){ .p = _9 },
  (ANY){ .p = _8 },
  (ANY){ .i = 20 },
  (ANY){ .i = 6 },
  (ANY){ .p = _10 },
  (ANY){ .p = _8 },
  (ANY){ .i = 48 },
  (ANY){ .i = 7 },
  (ANY){ .p = _11 },
  (ANY){ .p = _12 },
  (ANY){ .i = 52 },
  (ANY){ .i = 7 },
  (ANY){ .p = _13 },
  (ANY){ .p = _14 },
  (ANY){ .i = 56 },
  (ANY){ .i = 0 },
};
ANY bb_Baz[] = {
  (ANY){ .p = bbObjectClass },
  (ANY){ .p = bbObjectFree },
  (ANY){ .p = _3 },
  (ANY){ .i = 12 },
  (ANY){ .p = _bb_Baz_New },
  (ANY){ .p = _bb_Baz_Delete },
  (ANY){ .p = bbObjectToString },
  (ANY){ .p = bbObjectCompare },
  (ANY){ .p = bbObjectSendMessage },
  (ANY){ .p = bbObjectReserved },
  (ANY){ .p = bbObjectReserved },
  (ANY){ .p = bbObjectReserved },
  (ANY){ .p = _bb_Baz_M },
  (ANY){ .p = _bb_Baz_A },
  (ANY){ .p = _bb_Baz_B },
};
float _bb_Baz_X = 0;
int32_t bb_C = 65;
int64_t bb_D = 650000000000;
double bb_E = 19.6;
float bb_F = 23.4;
int32_t bb_G = brl_blitz_NullFunctionError.i;
static int32_t _43 = 49;
static ANY _1[] = {
  (ANY){ .p = bbStringClass },
  (ANY){ .i = 2147483647 },
  (ANY){ .sa = {105,110} },
  (ANY){ .sa = {32,109} },
};
static float _73 = 5.5;
static float _81 = 5.5;
