#include "HttpRequest.h"
#include <vector>
#include <string>

namespace
{
	int HexValueFromChar(int ch)
	{
		switch (tolower(ch))
		{
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		case 'a':
			return 10;
		case 'b':
			return 11;
		case 'c':
			return 12;
		case 'd':
			return 13;
		case 'e':
			return 14;
		case 'f':
			return 15;
		default:
			break;
		}

		return 0;
	}

	std::string ExtractURI(const http_message &msg)
	{
		int state = 0;
		int code = 0;
		std::vector<char> buf;

		for (int i = 0; i < msg.uri.len; i++)
		{
			int ch = msg.uri.p[i];

			if (state == 0)
			{
				if (ch != '%')
				{
					buf.push_back(ch);
				}
				else
				{
					state = 1;
				}
			}
			else if (state == 1)
			{
				code = HexValueFromChar(ch) * 16;
				state = 2;
			}
			else if (state == 2)
			{
				code += HexValueFromChar(ch);
				buf.push_back(code);
				state = 0;
			}
		}

		buf.push_back(0);

		return &buf[0];
	}
}

HttpRequest::HttpRequest(const http_message &msg)
	: _uri(ExtractURI(msg))
	, _rawMethod(msg.method.p, msg.method.len)
	, _method(requestMethodInvalid)
{
	if (_rawMethod == "GET")
	{
		_method = requestMethodGET;
	}
	else if (_rawMethod == "POST")
	{
		_method = requestMethodPOST;
	}
	else if (_rawMethod == "PUT")
	{
		_method = requestMethodPUT;
	}
	else if (_rawMethod == "DELETE")
	{
		_method = requestMethodDELETE;
	}
}

const std::string& HttpRequest::uri() const
{
	return _uri;
}

const std::string& HttpRequest::rawMethod() const
{
	return _rawMethod;
}

HttpRequestMethod HttpRequest::method() const
{
	return _method;
}
