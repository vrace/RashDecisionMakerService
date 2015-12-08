#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

extern "C"
{
#include "mongoose/mongoose.h"
}

#include <string>

class HttpResponse
{
public:
	HttpResponse();

	void SetCode(int code);
	void SetContentType(const std::string &contentType);
	void SetContent(const std::string &content);

	void Send(mg_connection *conn);
	
private:
	int _code;
	std::string _contentType;
	std::string _content;
};

#endif
