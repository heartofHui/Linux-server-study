
#include <stdio.h>
#include <string.h>
#include "DataType.h"

int main()
{
    struct DataType_UNION data;
    const uint16_t i=10;
    data=i;
    printf(data.miDataType);
    return 0;
}