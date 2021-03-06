#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <assert.h>
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Environment.h"
#include "Object.h"
/*============================================================================||
| A tile on the map
|-----------------------------------------------------------------------------||
| A tile has an environment and up to 4 objects
\=============================================================================*/

class Tile
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	Tile();
	~Tile();

	// SETTERS
    void setObject(Direction i_Dir, Object* i_Obj);
    void setEnvironment(EnvType i_Type);

	// REMOVE
    void removeObject(Direction i_Dir);

	// GETTERS
    Object* getObject(Direction i_Dir) const;
	const Environment& getEnvironment() const;

	// HAS
    bool hasObject(Direction i_Dir) const;
	bool hasObject() const;

	// STATUS
	bool isPassable() const;

private:
	Object**    m_Objs;
	Environment m_Env;
};