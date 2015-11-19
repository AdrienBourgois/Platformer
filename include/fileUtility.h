#ifndef FILE_UTILITY_H_INCLUDED
#define FILE_UTILITY_H_INCLUDED

#include <string>

namespace id {

class FileUtility
{
public:
	static auto getFileNameFromPath(std::string path) 			-> std::string;
    static auto getExtensionFromFileName(std::string file_name) -> std::string;
	static auto getPathWithoutFileName(std::string path) 		-> std::string;
};

} // namespace id

#endif // FILE_UTILITY_H_INCLUDED
