#ifndef ERROR_H
#define ERROR_H

#include <string> // Using std::string

class Error
{
public:
    Error(bool status, int code, std::string source);

    /**
     * @brief Indicates if an error has occured (TRUE = error, FALSE = no error)
     */
    bool status();

    /**
     * @brief Return an error code
     */
    int code();

    /**
     * @brief Retrun an error message
     */
    std::string source();

private:
    bool m_errorStatus;
    int m_errorCode;
    std::string m_errorMessage;
};

#endif // ERROR_H
