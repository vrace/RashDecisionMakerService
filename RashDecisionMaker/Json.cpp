#include "Json.h"
#include <sstream>

Json::Json()
{
}

Json::~Json()
{
	for (std::vector<Json*>::iterator it = _subnodes.begin(); it != _subnodes.end(); ++it)
		delete *it;

	_subnodes.clear();
}

Json* Json::AddChild(Json *node)
{
	_subnodes.push_back(node);
	return node;
}

std::string Json::ToString() const
{
	std::stringstream ss;

	for (std::vector<Json*>::const_iterator it = _subnodes.begin(); it != _subnodes.end(); ++it)
	{
		if (it != _subnodes.begin())
		{
			ss << ",";
		}

		ss << (*it)->ToString();
	}

	return ss.str();
}

JsonObjectNode::JsonObjectNode()
{
}

JsonObjectNode::JsonObjectNode(const std::string &name)
	: _name(name)
{
}

std::string JsonObjectNode::ToString() const
{
	std::stringstream ss;

	if (!_name.empty())
		ss << "\"" << _name << "\":";

	ss << "{";
	ss << Json::ToString();
	ss << "}";

	return ss.str();
}

JsonKeyValueNode::JsonKeyValueNode(const std::string &key, const std::string &value)
	: _key(key)
	, _value(value)
{
}

std::string JsonKeyValueNode::ToString() const
{
	std::stringstream ss;

	ss << "\"" << _key << "\":\"" << _value << "\"";

	return ss.str();
}

JsonKeyValueNode* JsonKeyValue(const std::string &key, const std::string &value)
{
	return new JsonKeyValueNode(key, value);
}

JsonKeyValueNode* JsonKeyValue(const std::string &key, const char *value)
{
	return new JsonKeyValueNode(key, value);
}