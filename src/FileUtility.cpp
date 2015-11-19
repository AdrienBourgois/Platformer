#include "FileUtility.h"

namespace id {

auto FileUtility::getFileNameFromPath(std::string path) -> std::string
{
    if (path.size() == 1)
        return path;
    int i; 
    for (i = path.size() - 1; i > 0; --i)
    {
        if (path[i] == '/')
            break;
    }
    return path.substr(i + 1, path.size() - i);
}

auto FileUtility::getExtensionFromFileName(std::string file_name) -> std::string
{
    if (file_name.size() == 1)
        return file_name;
    int i;
    for (i = file_name.size() - 1; i > 0; --i)
    {
        if (file_name[i] == '.')
            break;
    }
	return file_name.substr(i + 1, file_name.size() - i);
}

auto FileUtility::getPathWithoutFileName(std::string path) -> std::string
{
	if (path.size() == 1)
        return path;
    int i;
    for (i = path.size() - 1; i > 0; --i)
    {
        if (path[i] == '/')
            break;
    }
	return path.substr(0, i + 1);
}

} // namespace id
