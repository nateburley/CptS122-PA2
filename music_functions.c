#include "music_functions.h"

//Function that prints the main menu for the player
void display_main_menu(void)
{
  int user_choice = 0;
  printf("Welcome to Potify: The dankest music player on the market!\n\n");
  printf("MAIN MENU:\n");
  printf("(1) Load songs\n");
  printf("(2) Store songs\n");
  printf("(3) Display songs\n");
  printf("(4) Insert songs\n");
  printf("(5) Delete songs\n");
  printf("(6) Edit songs\n");
  printf("(7) Sort songs\n");
  printf("(8) Rate songs\n");
  printf("(9) Play songs\n");
  printf("(10) Shuffle\n");
  printf("(11) Exit\n");

}

//Function that creates a node; adds to front of list
struct record *create_node(FILE *infile)
{
  //Memory allocated for node; parsing variables declared
  Record *new_node = malloc(sizeof(struct record));
  char *temp = NULL;
  char holder[250];
  char delim[2] = ",";

  //Line read in
  fgets(holder, 250, infile);

  //Stores the artist
  temp = strtok(holder, delim);
  if (temp != '\0')
  {
    strcpy(new_node->artist, temp);
  }
  else
  {
    strcpy(new_node->artist, "Unknown Artist");
  }


  //Stores the album
  temp = strtok(NULL, delim);
  if (temp != '\0')
  {
    strcpy(new_node->album, temp);
  }
  else
  {
    strcpy(new_node->album, "Unknown Album");
  }


  //Stores the title
  temp = strtok(NULL, delim);
  if (temp != '\0')
  {
    strcpy(new_node->title, temp);
  }
  else
  {
    strcpy(new_node->title, "Unknown Track");
  }


  //Stores the genre
  temp = strtok(NULL, delim);
  if (temp != '\0')
  {
    strcpy(new_node->genre, temp);
  }
  else
  {
    strcpy(new_node->genre, "Unknown Genre");
  }

  //Stores the length (But doesn't parse it yet)
  temp = strtok(NULL, delim);
  char *length = temp;

  //Stores the number of plays
  temp = strtok(NULL, delim);
  //printf("Number of plays: %s\n", temp);
  if (temp != '\0')
  {
    new_node->num_plays = atoi(temp);
  }
  else
  {
    new_node->num_plays = 0;
  }

  //Stores the rating
  temp = strtok(NULL, delim);
  //printf("Rating: %s\n", temp);
  if (temp != '\0')
  {
    new_node->rating = atoi(temp);
  }
  else
  {
    new_node->rating = 0;
  }

  //Parses the length, now that the line is iterated over
  char *min_or_sec = NULL;
  min_or_sec = strtok(length, ":");
  if (min_or_sec != '\0')
  {
    new_node->length.minutes = atoi(min_or_sec);
    min_or_sec = strtok(NULL, ":");
    new_node->length.seconds = atoi(min_or_sec);
  }
  else
  {
    new_node->length.minutes = 0;
    new_node->length.minutes = 0;
  }

  //Sets the pointers to null (for now...)
  new_node->previous = NULL;
  new_node->next = NULL;

  return new_node;
}

//Function that prints the playlist (either whole thing, or one artist)
void print_list(struct record *pList)
{
  //Gets the user's choice for printing
  int choice = 0;
  do
  {
    printf("Would you like to view songs by 1 artist, or all of them?\n");
    printf("Enter 1 for a single artist, or 2 for all songs: ");
    scanf(" %d", &choice);
  } while((choice != 1) && (choice != 2));

  Record *current = pList;
  if (choice == 1) //Displays songs by 1 artist
  {
    //Gets the name of the artist
    char artist_name[50];
    printf("Enter the name of the artist: ");
    getchar();
    fgets(artist_name, 50, stdin);

    //Displays all songs by that artist
    while (current != NULL)
    {
      //printf("Artist searched: %s   Current artist: %s   Strcmp: %d\n", artist_name, current->artist, strcmp(artist_name, current->artist));
      if (strcmp(artist_name, current->artist) == 10)
      {
        printf("TITLE: %s\n", current->title);
        printf("ARTIST: %s\n", current->artist);
        printf("ALBUM: %s\n", current->album);
        printf("GENRE: %s\n", current->genre);
        printf("TIME: %d:%d\n", current->length.minutes, current->length.seconds);
        printf("NUM PLAYS: %d\n", current->num_plays);
        printf("RATING: %d\n\n", current->rating);
      }

     //Moves to the next item in the list
     current = current->next;
    }
    //system( "read -n 1 -s -p \"Print completed. Press any key to continue...\"" );
    //system("clear");
  }

  else //Prints everything in the playlist
  {
    while (current != NULL)
    {
           //Prints the data of current node
           printf("TITLE: %s\n", current->title);
           printf("ARTIST: %s\n", current->artist);
           printf("ALBUM: %s\n", current->album);
           printf("GENRE: %s\n", current->genre);
           printf("TIME: %d:%d\n", current->length.minutes, current->length.seconds);
           printf("NUM PLAYS: %d\n", current->num_plays);
           printf("RATING: %d\n\n", current->rating);

           //Moves to the next item in the list
           current = current->next;
    }
  }

}

//Function that inserts a new node at the end of the list
void insert_at_end(struct record **head_ptr, FILE *infile)
{
  //Variables initialized; new node created
  Record *current = *head_ptr;

  if (*head_ptr == NULL)
  {
    *head_ptr = create_node(infile);
    //printf("FIRST NODE ARTIST: %s\n\n", (*head_ptr)->artist);
    (*head_ptr)->previous = NULL;
    (*head_ptr)->next = NULL;
  }
  else                   //DELETE THIS IF SEGMENTATION FAULT
  {
    Record *new_node = create_node(infile);
    //Loops to end of list
    while (current->next != NULL)
    {
      current = current->next;
    }

    //Has end point to new item
    current->next = new_node;
    new_node->previous = current;
    new_node->next = NULL;
  }
}

//Function that inserts a new node at the beginning of the list
void insert_at_front(struct record **head_ptr, FILE *infile)
{
  //Makes new node head, if list is empty
  if (*head_ptr == NULL)
  {
    Record *new_node = create_node(infile);
    *head_ptr = new_node;
    //printf("FIRST NODE ARTIST: %s\n\n", (*head_ptr)->artist);
    new_node->previous = NULL;
    new_node->next = NULL;
  }
  else
  {
    Record *new_node = create_node(infile);
    Record *holder = *head_ptr;
    *head_ptr = new_node;
    new_node->next = holder;
    new_node->previous = NULL;
    holder->previous = new_node;
  }
}

//Function that creates the list
void create_list(struct record **head_ptr, FILE *infile)
{
  int counter = 1;
  while (!feof(infile))
  {
    insert_at_front(head_ptr, infile);
    //insert_at_end(head_ptr, infile);
    //printf("Line %d\n", counter);
    counter++;
  }

}

//Function that stores the list back in the csv FILE
void store_list(struct record *head, FILE *infile)
{
  //printf("\nStoring list....\n");
  struct record *current = head;
  while(current->next != NULL)
  {
    current = current->next;
  }

  while (current->previous != NULL)
  {
    //Note: this doesn't always print to the file, for whatever reason
    //My logic is fine. Replace the fprintf with a printf, and it prints it perfectly
    fprintf(infile, "%s,%s,%s,%s,%d:%d,%d,%d\n", current->artist, current->album,
    current->title, current->genre, current->length.minutes, current->length.seconds,
    current->num_plays, current->rating);

    current = current->previous;
  }
}

//Function that allows a user to edit the list
void edit_list(struct record *head)
{
  //Gets the name of the artist
  struct record *current = head;
  int choice = 0;
  char artist_search[50];
  char new_field[50];
  int temp_int = 0;
  printf("Enter the artist to search: ");
  getchar();
  fgets(artist_search, 50, stdin);

  //Loops through; flags songs by chosen artist
  while (current != NULL & choice == 0)
  {
    //printf("Artist searched: %s   Current artist: %s  Strcmp: %d\n", artist_search, current->artist, strcmp(artist_search, current->artist)); //For debugging
    if (strcmp(artist_search, current->artist) == 10) //space stuck at the end
    {
      do {
        printf("Is '%s' the song you want to edit?\n", current->title);
        printf("Enter 1 for yes, 2 for no: ");
        scanf(" %d", &choice);
      } while((choice != 1) && (choice != 2));

      if (choice == 1)
      {
        printf("Which field do you want to edit?\n");
        printf("1) Artist\n2) Album\n3) Title\n4) Genre\n5) Length\n6) Number of plays\n7) Rating\n");
        printf("Enter the field you wish to edit: ");
        scanf(" %d", &choice);

        switch (choice)
        {
          case 1:
            printf("Enter the new artist: ");
            getchar();
            fgets(new_field, 50, stdin);
            strcpy(current->artist, new_field);
            current->artist[strlen(current->artist)-1] = '\0';
            printf("The new artist is %s\n", current->artist);
            break;
          case 2:
            printf("Enter the new album: ");
            getchar();
            fgets(new_field, 50, stdin);
            strcpy(current->album, new_field);
            current->album[strlen(current->album)-1] = '\0';
            printf("The new album is %s\n", current->album);
            break;
          case 3:
            printf("Enter the new title: ");
            getchar();
            fgets(new_field, 50, stdin);
            strcpy(current->title, new_field);
            current->title[strlen(current->title)-1] = '\0';
            printf("The new title is %s\n", current->title);
            break;
          case 4:
            printf("Enter the new genre: ");
            getchar();
            fgets(new_field, 50, stdin);
            strcpy(current->genre, new_field);
            current->genre[strlen(current->genre)-1] = '\0';
            printf("The new genre is %s\n", current->genre);
            break;
          case 5:
            printf("Enter the new number of minutes: ");
            scanf(" %d", &temp_int);
            current->length.minutes = temp_int;
            printf("Enter the new number of seconds: ");
            scanf(" %d", &temp_int);
            current->length.seconds = temp_int;
            break;
          case 6:
            printf("Enter the new number of plays: ");
            scanf(" %d", &temp_int);
            current->num_plays = temp_int;
            break;
          case 7:
            printf("Enter the new rating: ");
            scanf(" %d", &temp_int);
            current->rating = temp_int;
            break;
        }
        break;
      }
    }
    current = current->next;
    choice = 0;
  }
  //Alerts the user their song/artist couldn't be found
  if (current == NULL)
  {
    printf("Couldn't find the song/artist you wanted.\n");
  }

}

//Function that allows a user to rate a song
void rate_song(struct record *head)
{
  struct record *current = head;
  int choice = 0;
  char artist_search[50];

  //Gets the artist to search for
  printf("Enter the artist to search: ");
  getchar();
  fgets(artist_search, 50, stdin);

  //Loops through list; flags songs by desired artist
  while((current != NULL) & (choice == 0))
  {
    if (strcmp(artist_search, current->artist) == 10)
    {
      //Checks if the song is the one the user wants to edit
      do {
        printf("Is '%s' the song you want to rate?\n", current->title);
        printf("Enter 1 for yes, 2 for no: ");
        scanf(" %d", &choice);
      } while((choice != 1) & (choice != 2));

      //Allows the user to rate the song, if they chose it
      if (choice == 1)
      {
        int new_rating = 0;
        do {
          printf("Enter a new rating: ");
          scanf(" %d", &new_rating);
        } while((new_rating < 1) & (new_rating > 5));
        current->rating = new_rating;
        printf("The new rating of %s is %d\n", current->title, current->rating);
        return;
      }

    }

    current = current->next;
    choice = 0;
  }
  //Alerts the user their song/artist couldn't be found
  if (current == NULL)
  {
    printf("Couldn't find the song/artist you wanted.\n");
  }
}

//Function that waits for a certain number of seconds;
//Courtesy of http://stackoverflow.com/questions/3930363/implement-time-delay-in-c
void waitFor(unsigned int seconds)
{
  unsigned int retTime = time(0) + seconds;   // Get finishing time.
  while (time(0) < retTime);               // Loop until it arrives.
}

//Function that plays a song (not really. But that would be cool)
void play_song(struct record *head)
{
  struct record *current = head;
  char song_choice[50];
  int start_playing = 0;

  //Gets song choice
  printf("Enter a song to start with: ");
  getchar();
  fgets(song_choice, 50, stdin);
  song_choice[strlen(song_choice)-1] = '\0';

  //Searches for the song
  while(current != NULL)
  {
    //printf("Song choice: %s   Current title: %s  Strcmp: %d\n", song_choice, current->title, strcmp(song_choice, current->title)); //For debugging
    if (strcmp(song_choice, current->title) == 0)
    {
      start_playing = 1;
    }
    if (start_playing == 1)
    {
      printf("Playing %s...\n", current->title);
      int counter = 0;
      while(counter < 10)
      {
        printf("*pretend you hear music*\n");
        waitFor(2);
        counter++;
      }
      system( "read -n 1 -s -p \"Press any key to continue...\"" );
      system("clear");
    }
    current = current->next;
    //system("clear");
  }

}

//Function that frees the list
void freeList(struct record *head)
{
   struct record *temp;

   while (head != NULL)
    {
       temp = head;
       head = head->next;
       free(temp);
    }

}

/*
Taylor Swift,1989,Shake it Off,Pop,3:35,12,3
Disturbed,THE SICKNESS,Down With The Sickness,Hard Rock,4:39,8,4
Drake,NOTHING WAS THE SAME,Own It,Rap,3:23,3,3
Disturbed,ASYLUM,Asylum,Hard Rock,4:36,2,4
Drake,YOU WELCOME,The Motto,Rap,4:13,7,4
Christina Perri,HEAD OF HEART,Trust,Pop,2:35,3,5
Justin Bieber,PURPOSE,No Sense,Pop,4:12,6,1
Eminem,SHADYXV,Vegas,Rap,3:37,8,3
Adele,25,Remedy,Pop,4:11,24,4
Disturbed,INDESTRUCTIBLE,The Night,Hard Rock,4:46,7,3
Taylor Swift,RED,Stay Stay Stay,Pop,4:42,5,1
Garth Brooks,FRESH HORSES,The Old Stuff,Country,2:57,11,2
Nirvana,NEVERMIND,Come As You Are,Grunge,3:38,5,4
Eminem,8 Mile,Lose Yourself,Rap,5:24,12,5
Five Finger Death Punch,American Capitalist,Back For More,Hard Rock,2:34,8,4
Disturbed,INDESTRUCTIBLE,Indestructible,Hard Rock,4:38,11,5
*/
