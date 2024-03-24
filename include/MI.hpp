#ifndef JMIM_INCLUDE_MI_H_
#define JMIM_INCLUDE_MI_H

namespace MI
{
    /* To include classes: 
        + ParseCSV (Functions: readCSV, sniffDataTypes, convertDataTypes)
        + TransformData (Functions: isDiscrete, discretise, targetEncode)
        
       In this namespace:
       Classes:
        + Entropy (Functions: calcEntropy, calcJointEntropy calcTrivatiateEntropy)
        + MutualInfo (Functions: calcMI, calcJMI, calcJMIM)
        
       Nice to haves: 
        - User to verify if sniffed data types are correct?
        - Parallelise encoding data functions instead of looping through each column.
        - Once data types have been confirmed compress them when possible i.e., int64 -> int32. 
    */
}

#endif