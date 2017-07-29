#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BF_SZ 10000

struct node{
  int *arr;
  int arr_size;
  struct node* prev;
  struct node* next;
};

struct linked_list{
  struct node *head;
  struct node *tail;
  int num_elems;
};

struct node* add_node(struct linked_list *list, int size_of_node);
void free_list(struct linked_list *list);
int max(int n1, int n2);
void remove_newline(char *buffer);

int main(){
  char buffer[BF_SZ];
  FILE *fp;

  struct linked_list *list = (struct linked_list*)malloc(sizeof(struct linked_list));
  list->head = NULL;
  list->tail = NULL;
  list->num_elems = 0;

  printf("Enter the name of the input file: ");
  
  fgets(buffer, BF_SZ, stdin);
  remove_newline(buffer);

  fp = fopen(buffer, "r");
  if(fp == NULL){
    perror("Could not open file");
    return 1;
  }

  int curr_elems = 1;
  while(fgets(buffer, BF_SZ, fp)){
    remove_newline(buffer);
    struct node* node = add_node(list, curr_elems);

    char *p = buffer;
    for(int i=0; i<curr_elems; i++){
      int number = atoi(p);
      node->arr[i] = number;
      if(i != curr_elems-1){
        do{
          p++;
        }while(*p != ' ');
        p++;
      }
    }

    curr_elems++;
  }

  fclose(fp);

  printf("There are a total of %d rows.\n", list->num_elems);

  struct node* curr = list->tail;
  while(curr->prev != NULL){
    struct node* prev = curr->prev;
    for(int i=0; i<prev->arr_size; i++){
      prev->arr[i] += max(curr->arr[i], curr->arr[i+1]);
    }
    curr = prev;
  }

  printf("If you can trust me, the result you are looking for is %d.\n", curr->arr[0]);
  free_list(list);
  free(list);
  
  return 0;
}

void remove_newline(char *buffer){
  char *p = buffer;
  while(*p != '\0'){
    if(*p == '\n'){
      *p = '\0';
      break;
    }
    p++;
  }
}

int max(int n1, int n2){
  return n1 > n2 ? n1 : n2;
}

void free_list(struct linked_list *list){
  struct node* curr = list->head;
  while(curr != NULL){
    free(curr->arr);
    struct node* next = curr->next;
    free(curr);
    curr = next;
  }
  list->head = NULL;
  list->tail = NULL;
  list->num_elems = 0;
}

struct node* add_node(struct linked_list *list, int size_of_node){
  struct node* res = (struct node*)malloc(sizeof(struct node));
  res->arr = (int*)malloc(sizeof(int)*size_of_node);
  res->arr_size = size_of_node;
  res->prev = NULL;
  res->next = NULL;
  if(list->num_elems == 0){
    list->head = res;
    list->tail = res;
  }else{
    list->tail->next = res;
    res->prev = list->tail;
    list->tail = res;
  }
  list->num_elems++;
  return res;
}

