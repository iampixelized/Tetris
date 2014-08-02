#ifndef IASSETMANAGER_HPP
#define IASSETMANAGER_HPP

#include<string>
using std::string;

#include "IAsset.hpp"

namespace esc
{
	class IAssetManager
	{
	public:

		virtual ~IAssetManager(){}
		virtual void removeAsset(const string & , const string &) = 0;
	};
}

#endif