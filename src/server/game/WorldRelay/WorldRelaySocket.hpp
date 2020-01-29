#ifndef SUNWELL_HTTP_POSTER_H
#define SUNWELL_HTTP_POSTER_H

#include "Common.h"

#include <openssl/ssl.h>
#include <string>

class HttpPosterSocket
{
public:
    HttpPosterSocket(std::string address);
    ~HttpPosterSocket();

    bool post(std::string data, std::string endpoint);
private:

    bool connect();
    BIO* m_web;
    SSL_CTX* m_ctx;
    std::string m_address;
    std::string m_header;
};


#endif
