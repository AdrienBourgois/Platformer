#ifndef SAVE_JSON_H_INCLUDED
#define SAVE_JSON_H_INCLUDED

#include <map>
#include <utility>
#include <vector> 
#include <string>
#include <iostream>

namespace id {
namespace json {

class JsonValue
{
public:
	JsonValue() = default;
	virtual ~JsonValue() = default;

	virtual auto serialize() -> void{}; 
	virtual auto serialize(std::ostream& os) -> void {(void)os;}

	static int indentation;

};


class JsonObject
:public JsonValue
{
public:
	JsonObject();
	virtual ~JsonObject();
	JsonObject(JsonObject const&) = default;
	JsonObject(JsonObject&&) = default;
	auto operator=(JsonObject const&) -> JsonObject& = default;
	auto operator=(JsonObject&&) -> JsonObject& = default;

	virtual auto serialize() -> void override;
	virtual auto serialize(std::ostream& os) -> void override;

	auto operator[](std::string str) -> JsonValue*&;

//private:
	std::map<std::string, JsonValue*> mapValue;
};
///////////////////


class JsonArray
:public JsonValue
{
public:
	JsonArray();
	virtual ~JsonArray();
	JsonArray(JsonArray const&) = default;
	JsonArray(JsonArray&&) = default;
	auto operator=(JsonArray const&) -> JsonArray& = default;
	auto operator=(JsonArray&&) -> JsonArray& = default;

	virtual auto serialize() -> void override;
	virtual auto serialize(std::ostream& os) -> void override;

private:
	std::vector<JsonValue> arrayValue;
};
///////////////////


class JsonString
:public JsonValue
{
public:
	JsonString();
	virtual ~JsonString();
	JsonString(JsonString const&) = default;
	JsonString(JsonString&&) = default;
	auto operator=(JsonString const&) -> JsonString& = default;
	auto operator=(JsonString&&) -> JsonString& = default;

	JsonString(std::string str);

	virtual auto serialize() -> void override;
	virtual auto serialize(std::ostream& os) -> void override;

private:
	std::string str;
};
///////////////////

class JsonBool
:public JsonValue
{
public:
	JsonBool();
	virtual ~JsonBool();
	JsonBool(JsonBool const&) = default;
	JsonBool(JsonBool&&) = default;
	auto operator=(JsonBool const&) -> JsonBool& = default;
	auto operator=(JsonBool&&) -> JsonBool& = default;

	JsonBool(bool boolean);

	virtual auto serialize() -> void override;
	virtual auto serialize(std::ostream& os) -> void override;

private:
	bool boolean;
};
///////////////////

class JsonNumber
:public JsonValue
{
public:
	JsonNumber();
	virtual ~JsonNumber();
	JsonNumber(JsonNumber const&) = default;
	JsonNumber(JsonNumber&&) = default;
	auto operator=(JsonNumber const&) -> JsonNumber& = default;
	auto operator=(JsonNumber&&) -> JsonNumber& = default;

	JsonNumber(long double number);

	virtual auto serialize() -> void override;
	virtual auto serialize(std::ostream& os) -> void override;

//private:
	long double number;
};
///////////////////


class JsonNull
:public JsonValue
{
public:
	JsonNull();
	virtual ~JsonNull();
	JsonNull(JsonNull const&) = default;
	JsonNull(JsonNull&&) = default;
	auto operator=(JsonNull const&) -> JsonNull& = default;
	auto operator=(JsonNull&&) -> JsonNull& = default;

	virtual auto serialize() -> void override;
	virtual auto serialize(std::ostream& os) -> void override;

};

} // namesapce json
} // namespace id

#endif // SAVE_JSON_H_INCLUDED
