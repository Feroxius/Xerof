#pragma once

//===========================================================================\\
//  | =   =   =   =   =   =   =   =   STL   =   =   =   =   =   =   =   =   = ||
#include <iomanip>
//  | =   =   =   =   =   =   =   =   LIB   =   =   =   =   =   =   =   =   = ||
#include "easylogging++.h"
//  | =   =   =   =   =   =   =   =   SRC   =   =   =   =   =   =   =   =   = ||
#include "..\Parameters.h"
/*============================================================================||
| Progress (percentage) logger
|-----------------------------------------------------------------------------||
| Build the ProgressLogger with the total number of iterations to process, and
| it will display the progression in percentage every PGI*100 percent.
\=============================================================================*/

class ProgressLogger
{
public:
    // CONSTRUCTOR/DESTRUCTOR
    ProgressLogger(UINT i_NumIters, const std::string& i_Msg) :
        ProgressLogger(i_NumIters, i_Msg.c_str())
    {}
    ProgressLogger(UINT i_NumElem, const char* i_Msg) :
        m_N(max(1, i_NumElem * PGI)),
        m_Step(m_N == 1 ? 100.0 / (double) i_NumElem : PGI * 100.0),
        m_Progress(0),
        m_Msg(i_Msg)
    {}

    // NEXT
    void next()
    {
        if (m_Progress < 100.0) {
            LOG_EVERY_N(m_N, DEBUG) << m_Msg << "[" << std::setw(3)
                << std::setprecision(3) << (m_Progress += m_Step) << "%]";
        }
    }
private:
    UINT        m_N;
    double      m_Step;
    double      m_Progress;
    const char* m_Msg;
};