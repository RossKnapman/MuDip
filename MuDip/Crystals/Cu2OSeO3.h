//
// Created by Ross Knapman on 10/08/2018.
//

#ifndef INC_3DDIPOLEFIELD_CU2OSEO3_H
#define INC_3DDIPOLEFIELD_CU2OSEO3_H

#include "../Sample.h"


class Cu2OSeO3 : public Sample
{
private:
    double a = 8.92500;

public:
    Cu2OSeO3(MomentField momentFieldIn);
};


#endif //INC_3DDIPOLEFIELD_CU2OSEO3_H
