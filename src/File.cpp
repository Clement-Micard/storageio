#include "pch.h"
#include "File.h"
#include <Windows.h>
#include <fileapifromapp.h>
#include <algorithm>
#include <string>
#include <sstream>

using namespace StorageIO;
using namespace Platform;

File^ File::GetFromPath(Platform::String^ path)
{
	WIN32_FILE_ATTRIBUTE_DATA fileData;
	bool exists = GetFileAttributesExFromAppW(path->Data(), GetFileExInfoStandard, &fileData);
	if (!exists)
	{
		return nullptr;
	}
	
	// Get file name
	std::wstring copy(path->Data());
	size_t size = copy.find_last_of(L'\\');
	Platform::String^ nameString = ref new Platform::String((copy.substr(size, copy.size()).c_str()));

	if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		return ref new File(path, nameString);
	}
	else
	{
		return nullptr;
	}
}

File^ File::GetFromApplicationFolder(Platform::String^ path)
{
	return GetFromPath(Windows::ApplicationModel::Package::Current->InstalledLocation->Path + path);
}

bool File::MoveTo(Folder^ folder, Platform::String^ desiredName)
{
	if (folder == nullptr)
	{
		return false;
	}

	// Append desiredName to path
	std::wstring copy(folder->Path->Data());
	copy.append(L"\\");
	copy.append(desiredName->Data());

	Platform::String^ str = ref new Platform::String(copy.c_str());

	return MoveFileFromAppW(str->Data(), copy.c_str());
}

File::File(Platform::String^ path, Platform::String^ name)
{
	_path = path;
	_name = name;
}
