#ifndef OBJECTLAYER_HPP
#define OBJECTLAYER_HPP

#include<iostream>
using std::cout;
using std::endl;

#include<string>
using std::string;

#include<map>
using std::map;
using std::pair;

#include<memory>
using std::unique_ptr;

#include<SFML/Graphics.hpp>

#include "ILayer.hpp"

namespace esc
{
	template<class MANAGEDTYPE>
	class ObjectLayer : public ILayer, protected MANAGEDTYPE
	{

	using MANAGEDTYPE::update;
	using MANAGEDTYPE::draw;
	using MANAGEDTYPE::getID;

	typedef unique_ptr<MANAGEDTYPE> ObjectPtr;
	typedef map<int, ObjectPtr> TypeLayer;

	public:

		virtual ~ObjectLayer(){};

		void addNewObject(MANAGEDTYPE*);
		bool deleteObject(int);
		MANAGEDTYPE * getObject(int);

		virtual void refreshLayer(float, sf::RenderWindow *, bool = true);

		int getLayerSize() const;
		MANAGEDTYPE * getRecentObject() const;

	protected:

		MANAGEDTYPE * recent;
		TypeLayer layer;

	};

	template<class MANAGEDTYPE>
	void ObjectLayer<MANAGEDTYPE>::addNewObject(MANAGEDTYPE* mtype)
	{
		int id = mtype->getID();
		layer.insert(pair<int, ObjectPtr>(id,ObjectPtr(mtype)));
		recent = layer[id].get();
	}

	template<class MANAGEDTYPE>
	bool ObjectLayer<MANAGEDTYPE>::deleteObject(int id)
	{	
		auto iter = layer.find(id);

		if (iter == layer.end())
			return false;

		layer.erase(id);
		return true;
	}

	template<class MANAGEDTYPE>
	MANAGEDTYPE * ObjectLayer<MANAGEDTYPE>::getObject(int id)
	{
		auto iter = layer.find(id);

		if (iter != layer.end())
			return nullptr;

		return iter->second.get();
	}

	template<class MANAGEDTYPE>
	void ObjectLayer<MANAGEDTYPE>::refreshLayer(float e, sf::RenderWindow * window, bool pause)
	{
		for (size_t i = 0; i < layer.size(); ++i)
		{
			if (!pause)
				layer[i].get()->update(e);

			layer[i].get()->draw(window);
		}
	}

	template<class MANAGEDTYPE>
	int ObjectLayer<MANAGEDTYPE>::getLayerSize() const
	{
		return layer.size();
	}

	template<class MANAGEDTYPE>
	MANAGEDTYPE * ObjectLayer<MANAGEDTYPE>::getRecentObject() const
	{
		return recent;
	}
}

#endif