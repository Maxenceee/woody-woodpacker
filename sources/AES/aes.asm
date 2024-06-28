

 ; //void AES_256_Key_Expansion (const unsigned char *userkey,
 ; // unsigned char *key)
global AES_256_Key_Expansion
AES_256_Key_Expansion:	; basic label
; # 	[parameter 1: %rdi]
; # 	[parameter 2: %rsi]
movdqu 	xmm1,	[rdi]
movdqu 	xmm3,	[16+rdi]
movdqa 	[rsi],	xmm1
movdqa 	[16+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	01h
call 	MAKE_RK256_a
movdqa 	[32+rsi],	xmm1
aeskeygenassist 	xmm2,	xmm1,	00h
call 	MAKE_RK256_b
movdqa 	[48+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	02h
call 	MAKE_RK256_a
movdqa 	[64+rsi],	xmm1
aeskeygenassist 	xmm2,	xmm1,	00h
call 	MAKE_RK256_b
movdqa 	[80+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	04h
call 	MAKE_RK256_a
movdqa 	[96+rsi],	xmm1
aeskeygenassist 	xmm2,	xmm1,	00h
call 	MAKE_RK256_b
movdqa 	[112+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	08h
call 	MAKE_RK256_a
movdqa 	[128+rsi],	xmm1
aeskeygenassist 	xmm2,	xmm1,	00h
call 	MAKE_RK256_b
movdqa 	[144+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	010h
call 	MAKE_RK256_a
movdqa 	[160+rsi],	xmm1
aeskeygenassist 	xmm2,	xmm1,	00h
call 	MAKE_RK256_b
movdqa 	[176+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	020h
call 	MAKE_RK256_a
movdqa 	[192+rsi],	xmm1
aeskeygenassist 	xmm2,	xmm1,	00h
call 	MAKE_RK256_b
movdqa 	[208+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	040h
call 	MAKE_RK256_a
movdqa 	[224+rsi],	xmm1
ret
MAKE_RK256_a:	; basic label
pshufd 	xmm2,	xmm2,	0ffh
movdqa 	xmm4,	xmm1
pslldq 	xmm4,	4
pxor 	xmm1,	xmm4
pslldq 	xmm4,	4
pxor 	xmm1,	xmm4
pslldq 	xmm4,	4
pxor 	xmm1,	xmm4
pxor 	xmm1,	xmm2
ret
MAKE_RK256_b:	; basic label
pshufd 	xmm2,	xmm2,	0aah
movdqa 	xmm4,	xmm3
pslldq 	xmm4,	4
pxor 	xmm3,	xmm4
pslldq 	xmm4,	4
pxor 	xmm3,	xmm4
pslldq 	xmm4,	4
pxor 	xmm3,	xmm4
pxor 	xmm3,	xmm2
ret


