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
	class ObjectLayer : protected MANAGEDTYPE , public ILayer
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
		
		virtual void refreshLayer(float e , sf::RenderWindow * , bool = false);

		MANAGEDTYPE * getRecentObject() const;
		int getSize() const;

	protected:

		virtual void preRoutine();
		virtual void postRoutine();

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
		preRoutine();

		//cout << "Refreshing layer..." << endl;
		for (auto iter = layer.begin(); iter != layer.end(); ++iter)
		{
			if (!pause) 
				iter->second->update(e);

			iter->second->draw(window);
		}

		postRoutine();
	}

	template<class MANAGEDTYPE>
	MANAGEDTYPE * ObjectLayer<MANAGEDTYPE>::getRecentObject() const
	{
		return recent;
	}

	template<class MANAGEDTYPE>
	int ObjectLayer<MANAGEDTYPE>::getSize() const
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