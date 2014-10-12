#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include<memory>
using std::unique_ptr;

#include<string>
using std::string;

#include<map>
using std::map;
using std::pair;

#include<SFML/Graphics.hpp>
#include<SFML/Audio/SoundBuffer.hpp>
#include<SFML/Audio/Music.hpp>

#include "Asset.hpp"

namespace esc
{
	class AssetManager
	{

	typedef unique_ptr<IAsset> IAssetType;
	typedef map<string, IAssetType> AssetContainer;
	typedef map<string, string> Definition;

	public:

		virtual ~AssetManager(){};

		void addAsset(const string &, IAsset*);
		bool removeAsset(const string &);
		IAsset * getAsset(const string &);

		bool addResourceToAsset(const string &, const string & , const string &);
		bool removeResourceToAsset(const string &, const string &);

		void clear();
		bool isAsset(const string &);

	private:

		AssetContainer a_container;
		Definition definition;
	};
}

#endif