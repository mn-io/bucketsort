#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "linked_list.c"

typedef struct bucket_ {
  int pivot;
  struct list_ *list;

  int *list_as_array;
  int array_length;
} Bucket;

void bucketsort(int values[], int values_length, int amount_of_buckets);

Bucket *bucket_init(int pivot);

Bucket **buckets_init(int pivot_step, int amount_of_buckets);

void buckets_sort_values(Bucket **buckets, int amount_of_buckets, int values[], int values_length);

int determine_max_within_values(int values[], int length);

int determine_pivot_step(int values[], int values_length, int amount_of_buckets);

void array_insertion_sort(int values[], int length);

void array_fill_random_int(int values[], int length, int min_rand, int max_rand);

void array_print(int values[], int length);

int rand_within_range(unsigned int min, unsigned int max);
