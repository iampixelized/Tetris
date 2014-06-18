#include "AssetManager.hpp"

namespace esc
{
	void AssetManager::addAsset(const string &aname, IAsset*a)
	{
		a_container.insert(pair<string, IAssetType>(aname, IAssetType(a)));
	}

	bool AssetManager::removeAsset(const string &aname)
	{
		if (!isAsset(aname))
			return false;

		a_container.erase(aname);
		return true;
	}

	IAsset * AssetManager::getAsset(const string &aname)
	{
		return (!isAsset(aname)) ? nullptr : a_container[aname].get();
	}

	bool AssetManager::addResourceToAsset(const string &aname, const string &oname, const string & path)
	{
		if (!isAsset(aname))
			return false;
	
		return a_container[aname].get()->loadFromFile(oname, path);
	}

	bool AssetManager::removeResourceToAsset(const string & aname, const string & oname)
	{
		if (!isAsset(aname))
			return false;

		return a_container[aname].get()->deleteFromAssetLibrary(oname);
	}

	void AssetManager::clear()
	{
		a_container.clear();
	}

	bool AssetManager::isAsset(const string & aname)
	{
		auto iter = a_container.find(aname);

		if (iter == a_container.end())
			return false;

		return true;
	}
}