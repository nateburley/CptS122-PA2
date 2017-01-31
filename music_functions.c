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

  //Stores the length
  char *length = NULL;
  temp = strtok(NULL, delim);
  length = strtok(temp, ":");
  if (length != '\0')
  {
    new_node->length.minutes = atoi(length);
    length = strtok(NULL, ":");
    new_node->length.seconds = atoi(length);
  }
  else
  {
    new_node->length.minutes = 0;
    new_node->length.minutes = 0;
  }

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
    printf("FIRST NODE ARTIST: %s\n\n", (*head_ptr)->artist);
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

//Function that creates the list
void create_list(struct record **head_ptr, FILE *infile)
{
  while (!feof(infile))
  {
    insert_at_end(head_ptr, infile);
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
