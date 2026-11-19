// resource.h || Base class for the Resource class

#ifndef GQ_RESOURCE_H
#define GQ_RESOURCE_H

#define MAX_RESOURCE_ALLOC		257

class gqResource 
{
public:
	gqResource();
	~gqResource();

	virtual 			void InitEmpty();
	virtual 			void Init();

private:
	const char*			filepath;
	void* 				data;
};

class gqResourceManager
{
public:

	gqResourceManager();
	~gqResourceManager();

	gqResource* GetResource( const char* name );
	void LoadFromFile( const char* name );

private:

	gqResource* resourcePool[MAX_RESOURCE_ALLOC];
	

};

#endif
