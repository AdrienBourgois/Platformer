#ifndef GUI_SAVE_FILE_H_INCLUDED
#define GUI_SAVE_FILE_H_INCLUDED

#include <string>

namespace id {

class Device;

class SaveFile
{
public:
	SaveFile();
	~SaveFile() = default;
	SaveFile(SaveFile const&) = delete;
	SaveFile(SaveFile&&) = delete;
	auto operator=(SaveFile const&) -> SaveFile& = delete;
	auto operator=(SaveFile&&) -> SaveFile& = delete;

	auto getActiveSave() const -> const bool 		{ return activeSave;	} 
	auto setActiveSave(bool const active) -> void 	{ activeSave = active; 	}

	auto DisplaySaveLevel(Device* dev) -> void;

private:
	std::string fileNameSave;
	bool activeSave;
};

} // namespace id 

#endif // GUI_SAVE_FILE_H_INCLUDED
