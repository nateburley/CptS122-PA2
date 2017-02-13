//NAME: Nathaniel Burley 11507009
//Computer Science 122
//Lab Section 04

#ifndef MUSIC_M_H
#define MUSIC_M_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct duration
{
  unsigned int seconds;
  unsigned int minutes;
}Duration;

typedef struct record
{
  char artist[50]; //I'll user char stars and malloc() next time. Promise
  char album[50];
  char title[50];
  char genre[50];
  Duration length;
  int num_plays;
  int rating;
  struct record *previous;
  struct record *next;
}Record;

//Function that prints the main menu for the player
void display_main_menu(void);

//Function that creates a node; adds to front of list
//Precondition: no commas in artist name, song title, album, or genre
//              Because seriously. Who listens to "Swfit, Taylor"
struct record *create_node(FILE *infile);

//Function that prints the playlist (either whole thing, or one artist)
void print_list(struct record *pList);

//Function that inserts a new node at the end of the list
void insert_at_end(struct record **head_ptr, FILE *infile);

//Function that prompts for a new node, inserts at front of list
void prompt_and_insert(struct record **head_ptr);

//Function that inserts a new node at the beginning of the list
void insert_at_front(struct record **head_ptr, FILE *infile);

//Function that creates the list
void create_list(struct record **head_ptr, FILE *infile);

//Function that stores the list back in the csv FILE
void store_list(struct record *head, FILE *infile);

//Function that allows a user to edit the list
void edit_list(struct record *head);

//Function that allows a user to rate a song
void rate_song(struct record *head);

//Function that waits for a certain number of seconds;
//Courtesy of http://stackoverflow.com/questions/3930363/implement-time-delay-in-c
void waitFor(unsigned int seconds);

//Function that plays a song (not really. But that would be cool)
void play_song(struct record *head);

//Function that sorts a list alphabetically by artist
void sort_by_artist(struct record **head_ptr);

//Function that deletes a song from the list
void delete_song(struct record **head_ptr);

//Function that plays songs on Shuffle
void play_shuffle(struct record *head);

//Function that frees the list
void freeList(struct record *head);

#endif
