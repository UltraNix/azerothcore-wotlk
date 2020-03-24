
#include "ARC4.h"
#include <openssl/sha.h>

ARC4::ARC4(uint8 len) : m_ctx()
{
#if defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x10100000L
	m_ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(m_ctx, EVP_rc4(), NULL, NULL, NULL);
	EVP_CIPHER_CTX_set_key_length(m_ctx, len);
#else
	EVP_CIPHER_CTX_init(&m_ctx);
	EVP_EncryptInit_ex(&m_ctx, EVP_rc4(), NULL, NULL, NULL);
	EVP_CIPHER_CTX_set_key_length(&m_ctx, len);
#endif
}

ARC4::ARC4(uint8 *seed, uint8 len) : m_ctx()
{
#if defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x10100000L
	m_ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(m_ctx, EVP_rc4(), NULL, NULL, NULL);
	EVP_CIPHER_CTX_set_key_length(m_ctx, len);
	EVP_EncryptInit_ex(m_ctx, NULL, NULL, seed, NULL);
#else
	EVP_CIPHER_CTX_init(&m_ctx);
	EVP_EncryptInit_ex(&m_ctx, EVP_rc4(), NULL, NULL, NULL);
	EVP_CIPHER_CTX_set_key_length(&m_ctx, len);
	EVP_EncryptInit_ex(&m_ctx, NULL, NULL, seed, NULL);
#endif
}

ARC4::~ARC4()
{
#if defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x10100000L
	EVP_CIPHER_CTX_free(m_ctx);
#else
	EVP_CIPHER_CTX_cleanup(&m_ctx);
#endif
}

void ARC4::Init(uint8 *seed)
{
#if defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x10100000L
	EVP_EncryptInit_ex(m_ctx, NULL, NULL, seed, NULL);
#else
	EVP_EncryptInit_ex(&m_ctx, NULL, NULL, seed, NULL);
#endif
}

void ARC4::UpdateData(int len, uint8 *data)
{
    int outlen = 0;
#if defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x10100000L
	EVP_EncryptUpdate(m_ctx, data, &outlen, data, len);
	EVP_EncryptFinal_ex(m_ctx, data, &outlen);
#else
	EVP_EncryptUpdate(&m_ctx, data, &outlen, data, len);
	EVP_EncryptFinal_ex(&m_ctx, data, &outlen);
#endif
}
