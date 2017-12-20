/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// DataManager.h -- Copyright (c) 2006 David Henry
// last modification: feb. 25, 2006
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Definitions of a data manager class.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __DATAMANAGER_H__
#define __DATAMANAGER_H__

#include <Windows.h>
#include <gl/GL.h>
#include <stdexcept>
#include <string>
#include <map>
#include "DefExport.h"

using std::string;
using std::map;


/////////////////////////////////////////////////////////////////////////////
//
// class DataManagerException - Exception class for DataManager classes.
// This acts like a standard runtime_error exception but
// know the name of the resource which caused the exception.
//
/////////////////////////////////////////////////////////////////////////////

class DllExport DataManagerException : public std::runtime_error
{
public:
	// Constructors
	DataManagerException(const string &error)
		: std::runtime_error(error) { }
	DataManagerException(const string &error, const string &name)
		: std::runtime_error(error), _which(name) { }
	virtual ~DataManagerException() throw () { }

public:
	// Public interface
	virtual const char *which() const throw () {
		return _which.c_str();
	}

private:
	// Member variables
	string _which;
};


/////////////////////////////////////////////////////////////////////////////
//
// class DataManager -- a data manager which can register/unregister
// generic objects.  Destroy all registred objects at death.
//
// The data manager is a singleton.
//
/////////////////////////////////////////////////////////////////////////////

template <typename T, typename C>
class DllExport DataManager
{
protected:
	// Constructor/destructor
	DataManager()
	{

	}
	virtual ~DataManager()
	{
		purge();
	}

public:
	// Public interface
	T *request(const string &name)
	{
		typename DataMap::iterator itor;
		itor = _registry.find(name);

		if (itor != _registry.end())
		{
			// The object has been found
			return itor->second;
		}
		else
		{
			return NULL;
		}
	}

	void registerObject(const string &name, T *object)
		throw (DataManagerException)
	{
		std::pair<typename DataMap::iterator, bool> res;

		// Register the object as a new entry
		res = _registry.insert(typename DataMap::value_type(name, object));

		// Throw an exception if the insertion failed
		if (!res.second)
			throw DataManagerException("Name collision", name);
	}
	void unregisterObject(const string &name, bool deleteObject = false)
	{
		typename DataMap::iterator itor;
		itor = _registry.find(name);

		if (itor != _registry.end())
		{
			if (deleteObject)
				delete itor->second;

			_registry.erase(itor);
		}
	}



	void purge()
	{
		// Not exception safe!
		for (typename DataMap::iterator itor = _registry.begin();
			itor != _registry.end(); ++itor)
		{
			// Destroy object
			delete itor->second;
		}

		_registry.clear();
	}


private:
	// Member variables
	typedef map<string, T*> DataMap;
	DataMap _registry;

public:
	// Singleton related functions
	static C *getInstance()
	{
		if (_singleton == NULL)
			_singleton = new C;

		return _singleton;
	}

	static void kill()
	{
		delete _singleton;
		_singleton = NULL;
	}


private:
	// The unique instance of this class
	static C *_singleton;
};
// Singleton initialization.  At first, there is no object created.
template <typename T, typename C>
C  *DataManager<T, C>::_singleton = NULL;


#endif // __DATAMANAGER_H__
