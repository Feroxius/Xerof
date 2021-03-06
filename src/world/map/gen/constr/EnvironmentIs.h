#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "Constraint.h"
/*============================================================================||
| Environment to replace is restricted to one type
|-----------------------------------------------------------------------------||
| Binary selection
\=============================================================================*/

class EnvironmentIs: public Constraint
{
public:
	// CONSTRUCTOR/DESTRUCTOR
    EnvironmentIs(const Map& i_Map, EnvType i_Type) :
        Constraint(i_Map),
        m_Type(i_Type) 
    {}

	// WEIGHT
    double getWeightFor(Coord i_Coord) const
	{
        return m_Map.getTile(i_Coord).getEnvironment().getType() == m_Type;
	}

private:
	EnvType m_Type;
};