#include "HttpResponse.h"
#include <map>

namespace
{
	std::map<int, std::string> StatusCodeMap;

	class InitStatusCodeMap
	{
	public:
		InitStatusCodeMap();
	};

	InitStatusCodeMap::InitStatusCodeMap()
	{
		StatusCodeMap[200] = "OK";
		StatusCodeMap[400] = "Bad Request";
	}

	InitStatusCodeMap initStatusCodeMap;
}

HttpResponse::HttpResponse()
	: _code(400)
	, _contentType("application/json")
	, _content("{}")
{
}

void HttpResponse::SetCode(int code)
{
	_code = code;
}

void HttpResponse::SetContentType(const std::string &contentType)
{
	_contentType = contentType;
}

void HttpResponse::SetContent(const std::string &content)
{
	_content = content;
}

void HttpResponse::Send(mg_connection *conn)
{
	mg_printf(conn, "HTTP/1.1 %d %s\r\n", _code, StatusCodeMap[_code].c_str());
	mg_printf(conn, "Content-Type: %s\r\n", _contentType.c_str());
	mg_printf(conn, "Content-Length: %d\r\n", _content.length());
	mg_printf(conn, "\r\n");
	mg_printf(conn, "%s", _content.c_str());
}
