#include "ServiceController.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include "Json.h"

#define CONTROLLER_IMPL(x) HttpResponse x(const HttpRequest &request)

namespace
{
	std::vector<std::string> ExtractItems(const std::string &itemText)
	{
		std::vector<std::string> items;

		for (std::string::size_type pos = 0;;)
		{
			std::string::size_type end = itemText.find('|', pos);
			if (end != std::string::npos)
			{
				items.push_back(itemText.substr(pos, end - pos));
				pos = end + 1;
			}
			else
			{
				items.push_back(itemText.substr(pos));
				break;
			}
		}

		return items;
	}
}

CONTROLLER_IMPL(WelcomeScreen)
{
	std::ifstream fs("Index.html");
	std::stringstream ss;
	ss << fs.rdbuf();
	std::string html = ss.str();

	HttpResponse response;

	response.SetCode(200);
	response.SetContentType("text/html");
	response.SetContent(html);

	return response;
}

CONTROLLER_IMPL(RollDice)
{
	const std::string &uri = request.uri();
	int upper = 100;

	if (uri.find("/d/") == 0)
	{
		upper = atoi(uri.c_str() + 3);
	}

	std::cout << "Rand (1-" << upper << ") = ";

	int val = rand() % upper + 1;

	std::cout << val << std::endl;

	JsonObjectNode json;
	json.AddChild(JsonKeyValue("upper", upper));
	json.AddChild(JsonKeyValue("result", val));

	HttpResponse response;
	response.SetCode(200);
	response.SetContent(json);
	
	return response;
}

CONTROLLER_IMPL(BadRequest)
{
	const std::string &uri = request.uri();
	const std::string &method = request.rawMethod();

	std::cout << "Bad request: " << uri << std::endl;

	JsonObjectNode json;
	json.AddChild(JsonKeyValue("uri", uri));
	json.AddChild(JsonKeyValue("method", method));
	json.AddChild(JsonKeyValue("answer to everything", "42"));

	HttpResponse response;
	response.SetContent(json);
	
	return response;
}

CONTROLLER_IMPL(RandomPick)
{
	const std::string &uri = request.uri();
	const std::string path = "/pick/";
	std::vector<std::string> items = ExtractItems(uri.substr(uri.find(path) + path.length()));

	if (items.empty())
	{
		items.push_back("");
	}

	std::string item = items[rand() % items.size()];

	JsonObjectNode json;
	json.AddChild(JsonKeyValue("item", item));

	HttpResponse response;
	response.SetCode(200);
	response.SetContent(json);

	return response;
}

CONTROLLER_IMPL(PairItems)
{
	const std::string &uri = request.uri();
	const std::string path = "/pair/";

	std::vector<std::string> items = ExtractItems(uri.substr(uri.find(path) + path.length()));
	std::random_shuffle(items.begin(), items.end());

	int numGroups = (items.size() + 1) / 2;

	JsonObjectNode json;
	json.AddChild(JsonKeyValue("numPairs", numGroups));

	for (int i = 0; i < numGroups; i++)
	{
		std::stringstream name;
		name << "pair" << i;
		
		Json *node = json.AddChild(new JsonObjectNode(name.str()));

		std::string a = items[i * 2];
		node->AddChild(JsonKeyValue("a", a));

		std::vector<std::string>::size_type index = i * 2 + 1;

		if (index < items.size())
		{
			std::string b = items[index];
			node->AddChild(JsonKeyValue("b", b));
		}
	}

	HttpResponse response;
	response.SetCode(200);
	response.SetContent(json);

	return response;
}

CONTROLLER_IMPL(YesOrNo)
{
	HttpResponse response;
	
	JsonObjectNode json;
	json.AddChild(JsonKeyValue("answer", rand() % 2 == 0 ? "yes" : "no"));
	
	response.SetCode(200);
	response.SetContent(json);
	return response;
}
