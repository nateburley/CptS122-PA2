#include "music_functions.h"

//Function that creates a node; adds to front of list
Record *create_node(FILE *infile)
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

//Function that prints the playlist
void print_list(struct record *pList)
{
       Record *current = pList;
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
