#include "error.h"

Error::Error(bool status, int code, std::string source)
{
    m_errorStatus = status;
    m_errorCode = code;
    m_errorMessage = source;
}

bool Error::status()
{
    return m_errorStatus;
}

int Error::code()
{
    return  m_errorCode;
}

std::string Error::source()
{
    return m_errorMessage;
}

