// sha.h - written and placed in the public domain by Wei Dai

//! \file
//! \headerfile sha.h
//! \brief Classes for SHA-1 and SHA-2 family of message digests

#ifndef CRYPTOPP_SHA_H
#define CRYPTOPP_SHA_H

#include "config.h"
#include "iterhash.h"

// Clang 3.3 integrated assembler crash on Linux
//  http://github.com/weidai11/cryptopp/issues/264
#define CRYPTOPP_DISABLE_SHA_ASM

NAMESPACE_BEGIN(CryptoPP)

/// <a href="http://www.weidai.com/scan-mirror/md.html#SHA-1">SHA-1</a>
class CRYPTOPP_DLL SHA1 : public IteratedHashWithStaticTransform<word32, BigEndian, 64, 20, SHA1>
{
public:
	static void CRYPTOPP_API InitState(HashWordType *state);
	static void CRYPTOPP_API Transform(word32 *digest, const word32 *data);
	CRYPTOPP_CONSTEXPR static const char * CRYPTOPP_API StaticAlgorithmName() {return "SHA-1";}
};

typedef SHA1 SHA;	// for backwards compatibility

//! implements the SHA-256 standard
class CRYPTOPP_DLL SHA256 : public IteratedHashWithStaticTransform<word32, BigEndian, 64, 32, SHA256, 32, true>
{
public:
#if (defined(CRYPTOPP_X86_ASM_AVAILABLE) || defined(CRYPTOPP_X32_ASM_AVAILABLE) || defined(CRYPTOPP_X64_MASM_AVAILABLE)) && !defined(CRYPTOPP_DISABLE_SHA_ASM)
	size_t HashMultipleBlocks(const word32 *input, size_t length);
#endif
	static void CRYPTOPP_API InitState(HashWordType *state);
	static void CRYPTOPP_API Transform(word32 *digest, const word32 *data);
	CRYPTOPP_CONSTEXPR static const char * CRYPTOPP_API StaticAlgorithmName() {return "SHA-256";}
};

//! implements the SHA-224 standard
class CRYPTOPP_DLL SHA224 : public IteratedHashWithStaticTransform<word32, BigEndian, 64, 32, SHA224, 28, true>
{
public:
#if (defined(CRYPTOPP_X86_ASM_AVAILABLE) || defined(CRYPTOPP_X32_ASM_AVAILABLE) || defined(CRYPTOPP_X64_MASM_AVAILABLE)) && !defined(CRYPTOPP_DISABLE_SHA_ASM)
	size_t HashMultipleBlocks(const word32 *input, size_t length);
#endif
	static void CRYPTOPP_API InitState(HashWordType *state);
	static void CRYPTOPP_API Transform(word32 *digest, const word32 *data) {SHA256::Transform(digest, data);}
	CRYPTOPP_CONSTEXPR static const char * CRYPTOPP_API StaticAlgorithmName() {return "SHA-224";}
};

//! implements the SHA-512 standard
class CRYPTOPP_DLL SHA512 : public IteratedHashWithStaticTransform<word64, BigEndian, 128, 64, SHA512, 64, (CRYPTOPP_BOOL_X86|CRYPTOPP_BOOL_X32)>
{
public:
	static void CRYPTOPP_API InitState(HashWordType *state);
	static void CRYPTOPP_API Transform(word64 *digest, const word64 *data);
	CRYPTOPP_CONSTEXPR static const char * CRYPTOPP_API StaticAlgorithmName() {return "SHA-512";}
};

//! implements the SHA-384 standard
class CRYPTOPP_DLL SHA384 : public IteratedHashWithStaticTransform<word64, BigEndian, 128, 64, SHA384, 48, (CRYPTOPP_BOOL_X86|CRYPTOPP_BOOL_X32)>
{
public:
	static void CRYPTOPP_API InitState(HashWordType *state);
	static void CRYPTOPP_API Transform(word64 *digest, const word64 *data) {SHA512::Transform(digest, data);}
	CRYPTOPP_CONSTEXPR static const char * CRYPTOPP_API StaticAlgorithmName() {return "SHA-384";}
};

NAMESPACE_END

#endif
