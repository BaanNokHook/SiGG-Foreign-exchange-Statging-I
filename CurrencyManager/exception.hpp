/**
 * @file exception.hpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <string>
#include <stdexcept>

class Exception : public std::exception
{
protected:
    std::string msg_;

public:
    Exception(const char* msg) : msg_(msg) { }
    Exception(const std::string& msg) : msg_(msg) { }
    virtual ~Exception() noexcept { }

    virtual const char* what() const noexcept
    {
        return msg_.c_str();
    }

};

class ForecasterException : public Exception
{

public:
    ForecasterException(const char* msg) : Exception(msg) { }
    ForecasterException(const std::string& msg) : Exception(msg) { }
    virtual ~ForecasterException() { }

    virtual const char* what() const noexcept
    {
        return msg_.c_str();
    }

};

class CurlHandlerException : public Exception
{

public:
    CurlHandlerException(const char* msg) : Exception(msg) { }
    CurlHandlerException(const std::string& msg) : Exception(msg) { }
    virtual ~CurlHandlerException() { }

    virtual const char* what() const noexcept
    {
        return msg_.c_str();
    }

};

class DataBaseHandlerException : public Exception
{

public:
    DataBaseHandlerException(const char* msg) : Exception(msg) { }
    DataBaseHandlerException(const std::string& msg) : Exception(msg) { }
    virtual ~DataBaseHandlerException() { }

    virtual const char* what() const noexcept
    {
        return msg_.c_str();
    }

};

#endif // EXCEPTION_HPP
