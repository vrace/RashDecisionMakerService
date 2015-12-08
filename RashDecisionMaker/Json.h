#ifndef __JSON_H__
#define __JSON_H__

#include <string>
#include <vector>
#include <sstream>

class Json
{
public:
	Json();
	virtual ~Json();

	Json* AddChild(Json *node);
	virtual std::string ToString() const;

	operator std::string() const;

private:
	std::vector<Json*> _subnodes;
};

class JsonObjectNode : public Json
{
public:
	JsonObjectNode();
	JsonObjectNode(const std::string &name);

	virtual std::string ToString() const;

private:
	std::string _name;
};

class JsonKeyValueNode : public Json
{
public:
	JsonKeyValueNode(const std::string &key, const std::string &value);
	virtual std::string ToString() const;

private:
	std::string _key;
	std::string _value;
};

template <class ValueType>
JsonKeyValueNode* JsonKeyValue(const std::string &key, const ValueType &val)
{
	std::stringstream ss;
	ss << val;

	return new JsonKeyValueNode(key, ss.str());
}

JsonKeyValueNode* JsonKeyValue(const std::string &key, const std::string &value);
JsonKeyValueNode* JsonKeyValue(const std::string &key, const char *value);

#endif
