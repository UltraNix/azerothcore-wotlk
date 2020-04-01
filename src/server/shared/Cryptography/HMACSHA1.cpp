#include "HMACSHA1.h"
#include "BigNumber.h"
#include "Common.h"

HmacHash::HmacHash(uint32 len, uint8 *seed)
{
#if (defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x10100000L) || defined(LIBRESSL_VERSION_NUMBER)
    m_ctx = HMAC_CTX_new();
    HMAC_Init_ex(m_ctx, seed, len, EVP_sha1(), NULL);
    memset(m_digest, 0, sizeof(m_digest));
#else
    HMAC_CTX_init(&m_ctx);
    HMAC_Init_ex(&m_ctx, seed, len, EVP_sha1(), NULL);
    memset(m_digest, 0, sizeof(m_digest));
#endif
}

HmacHash::~HmacHash()
{
#if (defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x10100000L) || defined(LIBRESSL_VERSION_NUMBER)
    HMAC_CTX_free(m_ctx);
#else
    HMAC_CTX_cleanup(&m_ctx);
#endif
}

void HmacHash::UpdateData(const std::string &str)
{
#if (defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x10100000L) || defined(LIBRESSL_VERSION_NUMBER)
    HMAC_Update(m_ctx, (uint8 const*)str.c_str(), str.length());
#else
    HMAC_Update(&m_ctx, (uint8 const*)str.c_str(), str.length());
#endif
}

void HmacHash::UpdateData(const uint8* data, size_t len)
{
#if (defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x10100000L) || defined(LIBRESSL_VERSION_NUMBER)
    HMAC_Update(m_ctx, data, len);
#else
    HMAC_Update(&m_ctx, data, len);
#endif
}

void HmacHash::Finalize()
{
    uint32 length = 0;
#if (defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x10100000L) || defined(LIBRESSL_VERSION_NUMBER)
    HMAC_Final(m_ctx, (uint8*)m_digest, &length);
#else
    HMAC_Final(&m_ctx, (uint8*)m_digest, &length);
#endif
    ASSERT(length == SHA_DIGEST_LENGTH);
}

uint8 *HmacHash::ComputeHash(BigNumber* bn)
{
#if (defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x10100000L) || defined(LIBRESSL_VERSION_NUMBER)
    HMAC_Update(m_ctx, bn->AsByteArray().get(), bn->GetNumBytes());
#else
    HMAC_Update(&m_ctx, bn->AsByteArray().get(), bn->GetNumBytes());
#endif
    Finalize();
    return (uint8*)m_digest;
}
