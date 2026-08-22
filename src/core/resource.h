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
	Resource(std::string path)
	{
		m_filepath = parse_path(path);
		uid = path;
	}
	~Resource() {}
	
	inline std::string parse_path(std::string path)
	{
		if (path[0] == '$')
		{
			return m_root + path.substr(1);
		}
		else if (path[0] == '%')
		{
			std::string cwd = __FILE__; // current working directory
			return cwd.substr(0, cwd.find_last_of('/') + 1) + "../" + path.substr(1);
		}
		else
		{
			printf("No root specififer, assuming file is absolute.\n");
			return path;
		}

	}

	virtual void load() {}
	inline std::string get_path()
	{
		return m_filepath;
	}

protected:
	std::string m_filepath; // Total file path...

private:
	inline static std::string m_root = ""; // Will be root of the resources...
	std::string uid;
};

} // namespace gquake
