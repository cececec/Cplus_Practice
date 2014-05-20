#include <stdlib.h>

int main(void)
{
    int tmp,*ptr=NULL,tmpmid;
    ptr=(int *)malloc(sizeof(tmp));
    tmp=1;
    *ptr=2;
    tmpmid=tmp;
    tmpmid=*ptr;
    free(ptr);
    ptr=NULL;
    return 0;
}
