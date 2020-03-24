
#ifndef _AUTH_SARC4_H
#define _AUTH_SARC4_H

#include "Define.h"
#include <openssl/evp.h>

class ARC4
{
    public:
        ARC4(uint8 len);
        ARC4(uint8 *seed, uint8 len);
        ~ARC4();
        void Init(uint8 *seed);
        void UpdateData(int len, uint8 *data);
    private:
#if defined(OPENSSL_VERSION_NUMBER) && OPENSSL_VERSION_NUMBER >= 0x10100000L
		EVP_CIPHER_CTX * m_ctx;
#else
		EVP_CIPHER_CTX m_ctx;
#endif
};

#endif
