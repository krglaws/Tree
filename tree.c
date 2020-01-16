
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>


char* appname;

int depth = 0;


void tree(char*);

int main(int argc, char** argv)
{
  appname = argv[0];

  if (argc > 1)
  {
    if (chdir(argv[1]))
    {
      perror(argv[1]);
      exit(EXIT_FAILURE);
    }
    printf("- %s\n", argv[1]);  
    tree(argv[1]);
  }
  else
  {
    printf("- .\n");
    tree(".");
  }

  return 0;
}


void tree(char* dirname)
{
  if (dirname == NULL)
    return;

  if (chdir(dirname))
  {
    perror(dirname);
    exit(EXIT_FAILURE);
  }
  depth++;

  DIR* dr;
  struct dirent* de;

  if ((dr = opendir(".")) == NULL)
  {
    perror(dirname);
    exit(EXIT_FAILURE);
  }
  while ((de = readdir(dr)) != NULL)
  {
    if (de->d_name[0] != '.')
    {
      int i;
      for (i = 0; i < depth; i++)
        printf("  ");

      printf("|-%s\n", de->d_name);

      if (de->d_type == DT_DIR)
        tree(de->d_name);
    }
  }

  closedir(dr);
  chdir("..");
  depth--;
}

