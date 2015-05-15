#include <stdio.h>
#include "rdtsc.h"

int main()
{
    long long t0 = 0;

    rdtscll(t0);

    printf("%016Lx\n",t0);
}
