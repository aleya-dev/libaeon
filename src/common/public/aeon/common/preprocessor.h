// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#ifndef AeonConcatenate
#define AeonConcatenateImpl(s1, s2) s1##s2
#define AeonConcatenate(s1, s2) AeonConcatenateImpl(s1, s2)
#endif

#ifndef AeonAnonymousVariable
#ifdef __COUNTER__
#define AeonAnonymousVariable(str) AeonConcatenate(str, __COUNTER__)
#else
#define AeonAnonymousVariable(str) AeonConcatenate(str, __LINE__)
#endif
#endif

#ifndef AeonArrayLength
#define AeonArrayLength(a) (sizeof(a) / sizeof(a[0]))
#endif

#ifndef AeonStringEncodingNone
#define AeonStringEncodingNone
#endif

#ifndef AeonStringEncodingUtf8
#define AeonStringEncodingUtf8 u8
#endif

#ifndef AeonStringEncodingUtf16
#define AeonStringEncodingUtf16 u
#endif

#ifndef AeonStringEncodingUtf32
#define AeonStringEncodingUtf32 U
#endif

#ifndef AeonStringEncodingWide
#define AeonStringEncodingWide L
#endif

#ifndef AeonStringEncoding
#define AeonStringEncoding AeonStringEncodingUtf8
#endif

#ifndef AeonText
#define AeonText(str) AeonConcatenate(AeonStringEncoding, str)
#endif

#ifndef AeonSingleArg
#define AeonSingleArg(...) __VA_ARGS__
#endif
