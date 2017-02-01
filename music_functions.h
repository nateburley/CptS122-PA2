#ifndef MUSIC_M_H
#define MUSIC_M_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct duration
{
  unsigned int seconds;
  unsigned int minutes;
}Duration;

typedef struct record
{
  char artist[50];
  char album[50];
  char title[50];
  char genre[50];
  Duration length;
  int num_plays;
  int rating;
  struct record *previous;
  struct record *next;
}Record;

//Function that creates a node; adds to front of list
//Precondition: no commas in artist name, song title, album, or genre
//              Because seriously. Who listens to "Swfit, Taylor"
Record *create_node(FILE *infile);

//Function that prints the playlist (either whole thing, or one artist)
void print_list(struct record *pList);

//Function that inserts a new node at the end of the list
void insert_at_end(struct record **head_ptr, FILE *infile);

//Function that inserts a new node at the beginning of the list
void insert_at_front(struct record **head_ptr, FILE *infile);

//Function that creates the list
void create_list(struct record **head_ptr, FILE *infile);

//Function that stores the list back in the csv FILE
void store_list(struct record *head, FILE *infile);

//Function that allows a user to edit the list
void edit_list(struct record *head);

//Function that frees the list
void freeList(struct record *head);

#endif
