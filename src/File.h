#pragma once
#include "Item.h"
#include "Folder.h"

namespace StorageIO
{
    public ref class File sealed : Item
    {
    public:
        Platform::String^ fileType;
		
        File(Platform::String^ path, Platform::String^ name);
        static File^ GetFromPath(Platform::String^ path);
        static File^ GetFromApplicationFolder(Platform::String^ path);

        bool MoveTo(Folder^ folder, Platform::String^ desiredName);
    };
}