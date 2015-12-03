#include "json/jsonWriter.h"
#include "json/jsonValue.h"
#include "json/jsonObject.h"
#include "txtLogger.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

int id::json::JsonWriter::indentation = 0;

namespace id {
namespace json { 

JsonWriter::JsonWriter(std::string name)
:file(("./assets/json/" + name + ".json").c_str(), std::ios_base::out)
{
	logger->log("Creating JsonWriter...", LL_DEBUG);

	logger->log("JsonWriter has been created.");
}

JsonWriter::~JsonWriter()
{
	logger->log("Deleting JsonWriter");

	file.close();

	logger->log("JsonWriter has been deleted");
}

auto JsonWriter::indent() -> std::string
{
	std::string str = "";
	for (int i = 0; i < indentation; ++i)
		str += "\t";
	return str;
}

auto JsonWriter::write(JsonObject* obj) -> void
{
	std::map<std::string, JsonValue*> mapValue = obj->getMapValue();

	file << "{" << std::endl;
	if (!mapValue.empty())
	{
		indentation++;

		unsigned int i = 1;
		unsigned int j = mapValue.size();
		for (auto&& val : mapValue)
		{
			file << indent();
			file << "\"" << val.first << "\" : ";
			file << val.second->serialize();
			if ( i == j)
				file << "\n";
			else
				file << ",\n";
			++i;
		}

		--indentation;
		file << indent();
	}
	file << "}";

}

} // namespace json
} // namespace id
