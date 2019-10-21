#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char **argv)
{
  int i;

  if(argc < 2){
    printf(2, "usage: sleep seconds...\n");
    exit();
  }

  for(i=1; i<argc; i++)
  if (atoi(argv[i]) != 1)
    sleep(atoi(argv[i]) * 100);
  exit();
}
