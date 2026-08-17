// resource.h || Base class for the Resource class

#pragma once 

#include <string>

namespace gquake
{

class Resource 
{

public:

	friend class App; // The App can set the resource class haha
	
	Resource() {}
	~Resource() {}
	Resource(const char* path)
	{
		set_path(path);
		load();
	}

	virtual void load() {}
	inline void set_path(std::string path)
	{
		m_filepath = m_root + path;
	}
	inline std::string get_path()
	{
		return m_filepath;
	}
private:
	static std::string m_root; // Will be root of the resources...
protected:
	std::string m_filepath; // Total file path...
};

} // namespace gquake
