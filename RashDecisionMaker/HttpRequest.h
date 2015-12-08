#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

extern "C"
{
#include "mongoose/mongoose.h"
}

#include <string>

enum HttpRequestMethod
{
	requestMethodInvalid,
	requestMethodGET,
	requestMethodPOST,
	requestMethodPUT,
	requestMethodDELETE,
};

class HttpRequest
{
public:
	HttpRequest(const http_message &msg);

	const std::string& uri() const;
	HttpRequestMethod method() const;
	const std::string& rawMethod() const;

private:
	std::string _uri;
	std::string _rawMethod;
	HttpRequestMethod _method;
};

#endif
