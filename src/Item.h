#pragma once

namespace StorageIO
{
	public ref class Item
	{
	protected:
		Platform::String^ _name;
		Platform::String^ _path;
	public:
		property Platform::String^ Name { Platform::String^ get(); };
		property Platform::String^ Path { Platform::String^ get(); };
	};
}