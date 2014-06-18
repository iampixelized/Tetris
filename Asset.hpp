#ifndef ASSET_HPP
#define ASSET_HPP

#include<map>
using std::map;
using std::pair;

#include<functional>
using std::function;

#include<string>
using std::string;

#include<memory>
using std::unique_ptr;

#include "IAsset.hpp"

namespace esc
{

	template<class T> 
	class Asset : public IAsset
	{

		protected:

			typedef map<string, unique_ptr<T>> AssetLibrary;
			typedef function<T*(const string &)> LoadMethod;

			AssetLibrary library;
		
		public:

			explicit Asset(const LoadMethod &);
			virtual ~Asset();

			bool loadFromFile(const string & oname, const string & path);
			bool deleteFromAssetLibrary(const string &aname);

			size_t getSize() const;
			virtual T * getResource(const string &);
			bool isResource(const string &) const;

		private:

			LoadMethod loadMethod;
	};

	template<class T>
	Asset<T>::Asset(const LoadMethod &_m)
		: loadMethod(_m)
	{

	}

	template<class T>
	Asset<T>::~Asset()
	{
	
	}

	template<class T>
	bool Asset<T>::loadFromFile(const string &oname, const string &path)
	{
		if(T * asset = loadMethod(path))
		{
			library.insert(pair<string, unique_ptr<T>>(oname, unique_ptr<T>(asset)));
			return true;
		}

		return false;
	}

	template<class T>
	bool Asset<T>::deleteFromAssetLibrary(const string &oname)
	{
		if (!isResource(oname)) return false;
		library.erase(oname);
		return true;
	}

	template<class T>
	size_t Asset<T>::getSize() const
	{
		return library.size();
	}

	template<class T>
	T * Asset<T>::getResource(const string &oname)
	{
		return (isResource(oname)) ? library[oname].get() : nullptr;
	}

	template<class T>
	bool Asset<T>::isResource(const string & oname) const
	{
		auto iter = library.find(oname);

		if (iter == library.end())
			return false;

		return true;
	}
}

#endif