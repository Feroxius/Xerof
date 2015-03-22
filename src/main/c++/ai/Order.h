#pragma once
#include <stdarg.h>

enum PossibleOrders
{
	WALK
};

class Order
{
public:
	// CONSTRUCTOR/DESTRUCTOR
	Order(PossibleOrders i_Action, 
          int            i_Param1 = -1, 
          int            i_Param2 = -1, 
          int            i_Param3 = -1);

	// GETTERS
	inline PossibleOrders getAction() const;
	inline int* getParams() const;

private:
	PossibleOrders m_Action;
	int* m_Params;
};