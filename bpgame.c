// CS211 Project 4
// Author: Julian Mackenzie and Janki Patel, UIC, Fall 2021
// 
// This file contains all functions necessary to run bpop, a small balloon popping game.
// It incorporates a 2d array of chars and contains a destruction function which will
// free all associated memory.
//

// file:  bpgame.c


#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include "bpgame.h"

/** TYPEDEFS / STRUCTs HERE ***/

struct bpgame {


   // YOU DECIDE WHAT TO PUT IN HERE TO CAPTURE THE STATE OF
   //   A "RUN" OF THE GAME.....
   char** m;
   int nrows;
   int ncols;
   int score;
   int frame;
   struct mystack* stack;

};



struct my_stack {
  struct bpgame* data;
  int size;
  int top;
};

struct my_stack* init () {
  
  struct my_stack* stack = (struct my_stack*) malloc(sizeof(struct my_stack));; 
  stack->top = -1;  // empty, first item will have index 0
  stack->size = 2;  // minimum size, will double when needed.
  
  stack->data = (struct bpgame*)malloc(2 * sizeof(struct bpgame*));
  return stack;
}

int is_empty (struct my_stack* stack) {
  if (stack->top == -1) return 1;
  return 0;
}


void push (struct my_stack* stack, BPGame * toPush) {
  stack->top++;
  
  if (stack->top == stack->size) {
    struct bpgame *temp = stack->data;
    stack->data = (struct bpgame *) malloc (stack->size * 2 * sizeof(struct bpgame));
    int i;
    for ( i = 0 ; i < stack->size ; i++)
        stack->data[i] = temp[i];
    free (temp);
    stack->size = stack->size * 2;
    
    
  }
   
   stack->data[stack->top] = *toPush;
   return;
   
}


BPGame * pop (struct my_stack* stack) {
  struct bpgame * toPop = &stack->data[stack->top];
  stack->top--;
  return toPop;
}


BPGame * top (struct my_stack* stack) {
  return &stack->data[stack->top];
}







/*** IMPLEMENTATION OF bp_XXXX FUNCTIONS HERE  ****/

extern BPGame * bp_create(int nrows, int ncols) {
   if (nrows < 1 || nrows > MAX_ROWS || ncols < 1 || ncols > MAX_COLS) {
      fprintf(stderr, "\n**ERROR: invalid matrix size\n");
      return NULL;
   }
   
   struct bpgame *b = malloc(sizeof(struct bpgame)); 
   
   

   
   b->nrows = nrows;
   b->ncols = ncols;
   b->score = 0;
   b->frame = 0;
   
   
   
   char **m = (char**) malloc(nrows * sizeof(char*));
   for (int i = 0; i < nrows; i++) {
      m[i] = (char*) malloc(sizeof(char) * ncols);
   }
   
   

   // populate board randomly
   srand(time(NULL));
   
   for (int r=0; r < b->nrows; r++) {
      for (int c=0; c < b->ncols; c++) {
         int rint = rand();
          if (rint % 4 == 0) m[r][c] = '^';
         else if (rint % 4 == 1) m[r][c] = '=';
         else if (rint % 4 == 2) m[r][c] = 'o';
         else if (rint % 4 == 3) m[r][c] = '+';
         
         // printf("%c", m[r][c]);
      }
      
      // printf("\n");
      
   }
   
   b->m = m;
   
   
   b->stack = init();
   

   return b;
}



extern BPGame * bp_create_from_mtx(char mtx[][MAX_COLS], int nrows, int ncols) {
   if (nrows < 1 || nrows > MAX_ROWS || ncols < 1 || ncols > MAX_COLS) {
      fprintf( stderr, "\n**ERROR: invalid matrix size\n");
      return NULL;
   }
   
   struct bpgame *b = malloc(sizeof(struct bpgame)); 
   
   b->nrows = nrows;
   b->ncols = ncols;
   b->score = 0;
   b->frame = 0;
   
   char **m = (char**) malloc(nrows * sizeof(char*));
   for (int i = 0; i < nrows; i++) {
      m[i] = (char*) malloc(sizeof(char) * ncols);
   }
   
   // populate board from mtx
   for (int r=0; r < b->nrows; r++) {
      for (int c=0; c < b->ncols; c++) {
         if (mtx[r][c] != '.' && mtx[r][c] != '^' && mtx[r][c] != '='
         && mtx[r][c] != 'o' && mtx[r][c] != '+') {
            fprintf( stderr, "\n**ERROR: invalid matrix contents\n");
            return NULL;
         }
         
         m[r][c] = mtx[r][c];
      }
   }
   
   b->m = m;
   
   return b;
}



extern void bp_destroy(BPGame * b) {
   for(int i = 0; i < b->nrows; i++)
      free(b->m[i]);
   free(b->m);
   return;
}



extern void bp_display(BPGame * b) {
   printf("\n   +-");
   for (int i=0; i < (*b).ncols; i++) {
      printf("--");
   }
   printf("+");
   
   for (int r=0; r < (*b).nrows; r++) {
      if (r < 10) printf("\n %d | ", r);
      else printf("\n%d | ", r);
      for (int c=0; c < (*b).ncols; c++) {
         printf("%c ", (*b).m[r][c]);
      }
      printf("|");
      
   }
   
   printf("\n   +-");
   for (int i=0; i < b->ncols; i++) {
      printf("--");
   }
   printf("+");
   
   printf("\n     ");
   for (int i=0; i < b->ncols; i++) {
      if (i < 10) printf("0 ");
      else if (i < 20) printf("1 ");
      else if (i < 30) printf("2 ");
      else printf("3 ");
   }
   
   printf("\n     ");
   for (int i=0; i < b->ncols; i++) {
      printf("%d ", i % 10);
   }
   printf("\n");
   
   return;
}



void bp_display_STD(BPGame * b) {

   
   for (int r=0; r < b->nrows; r++) {
      for (int c=0; c < b->ncols; c++) {
         printf("%c", b->m[r][c]);
      }
      printf("\n");
   }
   
   return;
}



// used in bp_pop(), contains commented-out code that is very helpful for debugging
void findcluster(BPGame *b, int r, int c, char balloon, int *numpopped, char exclude) {
   // printf("\nBalloon here: %c, exclude %c\nnrows: %d, ncols: %d\n", bp_get_balloon(b, r, c), exclude, b->nrows, b->ncols);
   if (bp_get_balloon(b, r, c) == balloon) {
      
      if (!(exclude == 'N') && r-1 >= 0) {
         // printf("\nlooking north of %d, %d...\n", r, c);
         b->m[r][c] = '.';
         findcluster(b, r-1, c, balloon, numpopped, 'S');
      }
      if (!(exclude == 'S') && r+1 < b->nrows) {
         // printf("\nlooking south of %d, %d...\n", r, c);
         b->m[r][c] = '.';
         findcluster(b, r+1, c, balloon, numpopped, 'N');
      }
      if (!(exclude == 'E') && c+1 < b->ncols) {
         // printf("\nlooking east of %d, %d...\n", r, c);
         b->m[r][c] = '.';
         findcluster(b, r, c+1, balloon, numpopped, 'W');
      }
      if (!(exclude == 'W') && c-1 >= 0) {
         // printf("\nlooking west of %d, %d...\n", r, c);
         b->m[r][c] = '.';
         findcluster(b, r, c-1, balloon, numpopped, 'E');
      }
      
      // printf("\nNumber of balloons popped: %d\n", *numpopped);
      if (*numpopped == 0 && exclude == 'O') {
         b->m[r][c] = balloon;
         return;
      }
      
      
      
      (*numpopped)++;
      
      return;
   }
   
   return;
}



extern int bp_pop(BPGame * b, int r, int c) {
   int numpopped = 0;
   int* npaddress = &numpopped;
   
   b->frame++;
   
   if (bp_get_balloon(b, r, c) == '.') return 0;
   
   findcluster(b, r, c, bp_get_balloon(b, r, c), npaddress, 'O');
   
   b->score += (numpopped * (numpopped-1));
   
   return numpopped;
} 


// Used in bp_can_pop() to check surrounding balloons
int checkneighbors(BPGame * b, int r, int c, char balloon) {
   if (b->m[r][c] == '.') return 0;
   if (r-1 >= 0) {
      if (b->m[r-1][c] == balloon) return 1;
   }
   if (r+1 < b->nrows) {
      if (b->m[r+1][c] == balloon) return 1;
   }
   if (c-1 >= 0) {
      if (b->m[r][c-1] == balloon) return 1;
   }
   if (c+1 < b->ncols) {
      if (b->m[r][c+1] == balloon) return 1;
   }
   return 0;
}



extern int bp_can_pop(BPGame * b) {
   for (int r=0; r < b->nrows; r++) {
      for (int c=0; c < b->ncols; c++) {
         char balloon = bp_get_balloon(b, r, c);
         if (checkneighbors(b, r, c, balloon) == 1) return 1;
      }
   }
   
   
   return 0;
}



extern int bp_is_compact(BPGame * b) {
   for (int r = b->nrows-1; r > 0; r--) {
      for (int c = 0; c < b->ncols; c++) {
         if (b->m[r][c] != '.' && b->m[r-1][c] == '.') {
            return 0;
         }
      }
   }
   return 1;
}



extern void bp_float_one_step(BPGame * b) {
   for (int r = 1; r < b->nrows; r++) {
      for (int c = 0; c < b->ncols; c++) {
         if (b->m[r-1][c] == '.') {
            char swap = b->m[r][c];
            b->m[r][c] = '.';
            b->m[r-1][c] = swap;
         }
      }
   }
   return;
}



extern int bp_score(BPGame * b) {
   return b->frame;
}



extern int bp_get_balloon(BPGame * b, int r, int c) {
   if (r >= 0 && r < b->nrows && c >= 0 && c < b->ncols) {
      return b->m[r][c];
   }
   return -1;   
}






extern int bp_undo(BPGame * b){
   return 0;
}





//int main() {
//  BPGame * board=NULL;
//  board = bp_create(15, 12);
//  
//  printf("%c", board->m[0][0]);
//  
//  
//}

