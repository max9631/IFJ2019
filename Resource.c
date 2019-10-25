#include "Resource.h"
#include "TokenList.h"

void cleanResources() {
    if(tokenList != NULL)
        destroyList(tokenList);
}
