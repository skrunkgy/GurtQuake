// resourcemgr.h || Resource manager class for getting resources at runtime, and keeping them alive after creation

#pragma once

#include "resource.h"
#include <unordered_map>
#include <sstream>

namespace gquake
{

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	template<typename T>
	T* get_resource(const char* path)
	{
		return reinterpret_cast<T*>(m_resourcePool[path]);
	}
	// std::stringstream load_file(const char* path);

private:
	std::unordered_map<std::string, Resource*> m_resourcePool;
	std::string m_root;
};

} // namespace gquake
