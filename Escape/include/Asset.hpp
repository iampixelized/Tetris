#ifndef ASSET_HPP
#define ASSET_HPP

#include<fstream>
using std::ifstream;

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
			typedef map<string, string> AssetDefinition;
			typedef function<T*(const string &)> LoadMethod;

			AssetLibrary library;
			AssetDefinition paths;
			
		public:

			explicit Asset(const LoadMethod &);
			virtual ~Asset();

			bool checkAllAssets();

			void addPath(const string & , const string &);
			string getPath(const string &);

			bool loadFromFile(const string &, const string &);
			bool deleteFromAssetLibrary(const string &);
			bool deleteDefinition(const string &);

			size_t getSize() const;
			virtual T * getResource(const string &);

			bool isLoaded(const string &);
			bool isResource(const string &) const;

		private:

			LoadMethod loadMethod;
	};

	template<class T>
	Asset<T>::Asset(const LoadMethod &_m)
		: loadMethod(_m){}

	template<class T>
	Asset<T>::~Asset(){}
	
	template<class T>
	bool Asset<T>::checkAllAssets()
	{
		for (pair<string, string> p : paths)
		{
			ifstream f(p.second.c_str());

			if (!f.good())
				return false;

			f.close();
		}

		return true;
	}

	template<class T>
	void Asset<T>::addPath(const string &oname, const string &path)
	{
		paths.insert(pair<string, string>(oname, path));
	}

	template<class T>
	string Asset<T>::getPath(const string &oname)
	{
		if (!isResource(oname)) return "";

		return paths[oname];
	}

	template<class T>
	bool Asset<T>::loadFromFile(const string &oname, const string &path)
	{
		if(T * asset = loadMethod(path))
		{
			library[oname] = unique_ptr<T>(asset);
			paths.insert(pair<string, string>(oname,path));
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
	bool Asset<T>::deleteDefinition(const string &oname)
	{
		if (!isResource(oname)) return false;

		library.erase(oname);
		definition.erase(oname);

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
		if (!isLoaded(oname) && isResource(oname))
			loadFromFile(oname , paths[oname]); 

		return (isResource(oname)) ? library[oname].get() : nullptr;
	}
	
	template<class T>
	bool Asset<T>::isLoaded(const string & oname) 
	{
		if (!isResource(oname)) return false;

		return library[oname].get() != nullptr;
	}

	template<class T>
	bool Asset<T>::isResource(const string & oname) const
	{
		return (paths.find(oname) != paths.end())? true : false;
	}
}

#endif