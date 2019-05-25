#ifndef HEURISTIC_EQUITABLE_COLORATION_METHODDE_OPTIONS
#define HEURISTIC_EQUITABLE_COLORATION_METHODDE_OPTIONS
#include <bits/stdc++.h> 
#include "Individual.h"
class Individual;
typedef struct HeuristicEquitableColorationMethodeOptions
{
    int differenceBetweenClasses;
    int maxUselessIteration;
    int maxNewColorstoAddWhenMAxUselessiterationIsExceeded;
}HeuristicEquitableColorationMethodeOptions;


#endif