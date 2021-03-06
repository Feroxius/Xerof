#include "Order.h"

//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                          CONSTRUCTOR/DESTRUCTOR                            //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

Order::Order(PossibleOrders i_Action, int i_Param1, int i_Param2, int i_Param3):
m_Action(i_Action)
{
    m_Params[0] = i_Param1;
    m_Params[1] = i_Param2;
    m_Params[2] = i_Param3;
}


//= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
//                                   GETTERS                                  //
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

PossibleOrders Order::getAction() const 
{ 
    return m_Action; 
}

int Order::getParam(UINT i_ID) const
{
    assert(i_ID < 4);
    return m_Params[i_ID];
}
