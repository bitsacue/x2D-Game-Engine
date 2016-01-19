#ifndef CGF_RESOURCE_MANAGER_H
#define CGF_RESOURCE_MANAGER_H

#include <CGF/Config.h>

/*********************************************************************
**	Resource manager												**
**********************************************************************/

BEGIN_CGF_NAMESPACE

/**
 * \brief This class handles resource loading and handling.
 *
 * Resources in this context are objects which are loaded from the hard drive
 * and which should only be read once.
 *
 * Resources are loaded as follows \code ResouceClassPtr resource = ResourceManager::get<ResourceClass>("path_to_file.res"); \endcode
 * Where ResourceClass is the name the class of the type of resource you are trying to load.
 * ResouceManager can currently load image files and font files.
 */

// TODO: Separate resources from instances of resources.
// 
// For example changing the color of a FontPtr loaded with ResourceManager
// will change the color of all instances loaded with ResourceManager.
//  
// To fix this, separate the Font class into FontInstance and FontResource,
// where FontInstance holds all instance related data, and FontResurce the
// shader resource data.
class CGF_API ResourceManager
{
	friend class Game;
public:
	/**
	 * Returns a resource given a file path. If this is the first time the
	 * resource was accessed, it will be loaded from the disk. If it was
	 * already loaded, this returns a pointer to the existing resource.
	 *
	 * \param filePath The file path to the resource file
	 * \note This can only load Texture2D and Font.
	 */
	template<typename T>
	static shared_ptr<T> get(string fileName)
	{
		util::toAbsoluteFilePath(fileName);

		// NOTE TO SELF: I need to notify the resource manager of resources that have been deleted so I can remove it from s_resources.
		if(s_resources->find(fileName) != s_resources->end())
		{
			return *(shared_ptr<T>*)(*s_resources)[fileName];
		}

		shared_ptr<T> resource = T::loadResource(fileName);
		(*s_resources)[fileName] = new shared_ptr<T>(resource);
		return resource;
	}

private:
	static map<string, void*> *s_resources;
};

END_CGF_NAMESPACE

#endif // CGF_RESOURCE_MANAGER_H
