/**
*   @file Cu2OSeO3.h
*   @brief Extends Sample class; stores information about the Cu2OSeO3 crystal.
*   @author Ross Knapman
*   @date 22/08/2018
*/


#ifndef INC_3DDIPOLEFIELD_CU2OSEO3_H
#define INC_3DDIPOLEFIELD_CU2OSEO3_H

#include "../Sample.h"


class Cu2OSeO3 : public Sample
{
public:
    Cu2OSeO3(MomentField momentFieldIn);
};


#endif //INC_3DDIPOLEFIELD_CU2OSEO3_H
