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
	Resource(const char* path)
	{
		m_filepath = m_root + path;
	}
	~Resource() {}

	virtual void load() {}
	inline std::string get_path()
	{
		return m_filepath;
	}

protected:
	std::string m_filepath; // Total file path...

private:
	inline static std::string m_root = ""; // Will be root of the resources...
};

} // namespace gquake
