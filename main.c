//NAME: Nathaniel Burley 11507009
//Computer Science 122
//Lab Section 04

//Note: My text editor saves a blank line at the end of files.
//      Thats where the weird "Unknown" song comes from

#include "music_functions.h"
#include "music_functions.c"

int main(void)
{
  Record *head = NULL;
  Record **head_ptr = &head;
  Record *current = head;
  FILE *infile = NULL;
  int current_action = 0;
  int keep_playing = 1;
  int c;

  infile = fopen("musicPlayList.csv", "r+");
  if (infile == NULL)
  {
    printf("ERROR OPENING FILE");
    return 1;
  }
  /*
  create_list(head_ptr, infile);
  sort_by_artist(head_ptr);
  printf("\n\n");
  while(current != NULL)
  {
    printf("Artist: %s\n", current->artist);
    current = current->next;
  }
  current = head;
  */
  create_list(head_ptr, infile);
  while(keep_playing == 1)
  {
    display_main_menu();

    do{
    printf("Enter your choice of action: ");
    scanf(" %d", &current_action);
  }while((current_action < 1) && (current_action > 10));

    switch(current_action)
    {
      case 1:
        printf("Songs loaded from storage.\n");
        system( "read -n 1 -s -p \"Press any key to continue...\"" );
        system("clear");
        break;

      case 2:
        store_list(head, infile);
        printf("Storage updated.\n");
        system( "read -n 1 -s -p \"Press any key to continue...\"" );
        system("clear");
        break;

      case 3:
        print_list(head);
        system( "read -n 1 -s -p \"Press any key to continue...\"" );
        system("clear");
        break;

      case 4:
        prompt_and_insert(head_ptr);
        system( "read -n 1 -s -p \"Press any key to continue...\"" );
        system("clear");
        break;

      case 5:
        delete_song(head_ptr);
        system( "read -n 1 -s -p \"Press any key to continue...\"" );
        system("clear");
        break;

      case 6:
        edit_list(head);
        system( "read -n 1 -s -p \"Press any key to continue...\"" );
        system("clear");
        break;

      case 7:
        printf("Uh oh! This feature is not available for Potify Lite!\n");
        printf("You must upgrade to Potify Pro for access\n");
        system( "read -n 1 -s -p \"Press any key to continue...\"" );
        system("clear");
        break;

      case 8:
        rate_song(head);
        system( "read -n 1 -s -p \"Press any key to continue...\"" );
        system("clear");
        break;

      case 9:
        play_song(head);
        system( "read -n 1 -s -p \"Press any key to continue...\"" );
        system("clear");
        break;

      case 10:
        printf("Uh oh! This feature is not available for Potify Lite!\n");
        printf("You must upgrade to Potify Pro for access\n");
        system( "read -n 1 -s -p \"Press any key to continue...\"" );
        system("clear");
        break;

      case 11:
        printf("Thanks for using Potify!\n");
        keep_playing = 0;

      }
  }

  //store_list(head, infile);
  fclose(infile);
  freeList(*head_ptr);
  return 0;
}
