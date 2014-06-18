#ifndef IASSET_HPP
#define IASSET_HPP

#include<string>
using std::string;

namespace esc
{
	class IAsset
	{

	public:

		IAsset(){}
		virtual ~IAsset(){}
		virtual bool loadFromFile(const string &oname, const string & path) = 0;
		virtual bool deleteFromAssetLibrary(const string &aname) = 0;
	
	};
}

#endif