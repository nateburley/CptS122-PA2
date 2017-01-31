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
Record *create_node(FILE *infile);

//Function that prints the playlist
void print_list(struct record *pList);

//Function that inserts a new node at the end of the list
void insert_at_end(struct record **head_ptr, FILE *infile);

//Function that creates the list
void create_list(struct record **head_ptr, FILE *infile);

//Function that frees the list
void freeList(struct record *head);

#endif
