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
	class ObjectLayer : private MANAGEDTYPE , public ILayer
	{

	using MANAGEDTYPE::update;
	using MANAGEDTYPE::draw;
	using MANAGEDTYPE::getID;
	using MANAGEDTYPE::isGarbageCollectible;

	typedef unique_ptr<MANAGEDTYPE> ObjectPtr;
	typedef map<int, ObjectPtr> TypeLayer;

	public:
		
		ObjectLayer();
		virtual ~ObjectLayer(){};

		MANAGEDTYPE * addNewObject(MANAGEDTYPE *, bool * check = nullptr);
		bool deleteObject(int);
		MANAGEDTYPE * getObject(int);
		
		virtual void drawLayer(sf::RenderWindow *);
		virtual void updateLayer(float e);

		size_t getSize() const;

	protected:

		virtual void preRoutine();
		virtual void postRoutine();

		MANAGEDTYPE * recent;
		TypeLayer layer;

	};

	template<class MANAGEDTYPE>
	ObjectLayer<MANAGEDTYPE>::ObjectLayer()
		: recent(nullptr)
	{
	
	}

	template<class MANAGEDTYPE>
	MANAGEDTYPE * ObjectLayer<MANAGEDTYPE>::addNewObject(MANAGEDTYPE* mtype , bool * check)
	{
		int id = mtype->getID();

		if (layer.find(id) != layer.end())
		{	
			if (check != nullptr) *check = false;
			return layer[id].get();
		}

		layer.insert(pair<int, ObjectPtr>(id,ObjectPtr(mtype)));
		recent  = layer[id].get();
		if(check != nullptr) *check  = true;  

		return recent;
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

		if (iter == layer.end())
			return nullptr;

		return iter->second.get();
	}

	template<class MANAGEDTYPE>
	void ObjectLayer<MANAGEDTYPE>::drawLayer(sf::RenderWindow * window)
	{
		for (auto iter = layer.begin(); iter != layer.end(); ++iter)
			iter->second->draw(window);
	}

	template<class MANAGEDTYPE>
	void ObjectLayer<MANAGEDTYPE>::updateLayer(float e)
	{
		for (auto iter = layer.begin(); iter != layer.end();)
		{ 
			if (iter->second->isGarbageCollectible())
				iter = layer.erase(iter);
			else
				++iter;
		}

		preRoutine();

		for (auto iter = layer.begin(); iter != layer.end(); ++iter)
			iter->second->update(e);

		postRoutine();
	}

	template<class MANAGEDTYPE>
	size_t ObjectLayer<MANAGEDTYPE>::getSize() const
	{
		return layer.size();
	}

	template<class MANAGEDTYPE>
	void ObjectLayer<MANAGEDTYPE>::preRoutine()
	{
		//
	}

	template<class MANAGEDTYPE>
	void ObjectLayer<MANAGEDTYPE>::postRoutine() 
	{
		//
	}
}

#endif