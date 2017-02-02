#include "music_functions.h"
#include "music_functions.c"

int main(void)
{
  Record *head = NULL;
  Record **head_ptr = &head;
  FILE *infile = NULL;

  infile = fopen("musicPlayList.csv", "rw");
  if (infile == NULL)
  {
    printf("ERROR OPENING FILE");
    return 1;
  }

  create_list(head_ptr, infile);
  //print_list(head);
  store_list(head, infile);
  edit_list(head);

  fclose(infile);
  freeList(*head_ptr);
  return 0;
}
