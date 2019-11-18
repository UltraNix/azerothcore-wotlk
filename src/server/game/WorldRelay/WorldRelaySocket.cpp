#include "WorldRelaySocket.hpp"
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Stream.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "Log.h"
#include "fmt/format.h"

HttpPosterSocket::HttpPosterSocket(std::string address) : m_address(address)
{
    m_header = " HTTP/1.1\r\nHost: " + address + "\r\nUser-Agent: curl/7.66.0\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: ";
}

HttpPosterSocket::~HttpPosterSocket()
{
}

bool HttpPosterSocket::connect()
{
    SSL_library_init();
    m_ctx = nullptr;
    m_web = nullptr;
    SSL* ssl;
    const char* const PREFERRED_CIPHERS = "HIGH:!aNULL:!kRSA:!PSK:!SRP:!MD5:!RC4";
    const SSL_METHOD* method = SSLv23_method();
    if (method == nullptr)
        return false;

    m_ctx = SSL_CTX_new(method);
    if (m_ctx == nullptr)
        return false;

    SSL_CTX_set_verify(m_ctx, SSL_VERIFY_NONE, nullptr);
    SSL_CTX_set_options(m_ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_COMPRESSION);
    m_web = BIO_new_ssl_connect(m_ctx);
    if (m_web == nullptr)
        return false;

    if (BIO_set_conn_hostname(m_web, (m_address + ":443").c_str()) != 1)
        return false;

    BIO_get_ssl(m_web, &ssl);
    if (ssl == nullptr)
        return false;

    if (SSL_set_cipher_list(ssl, PREFERRED_CIPHERS) != 1)
        return false;

    if (SSL_set_tlsext_host_name(ssl, m_address.c_str()) != 1)
        return false;

    if (BIO_do_connect(m_web) != 1)
        return false;

    if (BIO_do_handshake(m_web) != 1)
        return false;

    return true;
}

bool HttpPosterSocket::post(std::string data, std::string endpoint)
{
    if (!connect())
        return false;

    int len = 0;
    std::string puts = fmt::format("POST {}{}{}\r\n\r\n{}\r\n", endpoint, m_header, data.length(), data);
    if (sLog->IsOutDebug())
    {
        sLog->outDebug(DebugLogFilters::LOG_FILTER_NETWORKIO, "WorldRelaySocket::Post: message < %s >", puts);
    }

    BIO_puts(m_web, puts.c_str());
    BIO_free_all(m_web);
    SSL_CTX_free(m_ctx);
    return true;
}
