


#include <unistd.h> /* alarm, pause */
#include <sys/types.h>
#include <signal.h> /* signal,kill */


unsigned long long  currentcycles()
{
  unsigned hi, lo;

  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));

  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

unsigned long long cpuhz()
{
    unsigned long long c1, c2, c = 0;

    for(int n = 0; n < 10; n ++)
    {
	c1 = currentcycles();
	sleep(1);
	c2 = currentcycles();
	c += c2 - c1;
    }
    return c/10;
}

