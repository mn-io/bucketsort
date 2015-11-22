#include "bucketsort.h"

#define PRINT_LINEBREAK 40
#define MAX_LOOKAHEAD 1000

void bucketsort(int values[], int values_length, int amount_of_buckets) {
    int current_i, total_i = 0;

    int lookahead = values_length > MAX_LOOKAHEAD ? MAX_LOOKAHEAD : values_length;
    int pivot_step = determine_pivot_step(values, lookahead, amount_of_buckets);

    Bucket **buckets = buckets_init(pivot_step, amount_of_buckets);

    buckets_sort_values(buckets, amount_of_buckets, values, values_length);

    for (current_i = 0; current_i < amount_of_buckets; current_i++) {
        Bucket *bucket = buckets[current_i];

        bucket->list_as_array = (int *)malloc(sizeof(int) * (bucket->list->size));

        list_to_array(bucket->list, bucket->list_as_array);
        bucket->array_length = bucket->list->size;
        list_destroy(bucket->list);//TODO: performance
        array_insertion_sort(bucket->list_as_array, bucket->array_length);
    }

    for (current_i = 0; current_i < amount_of_buckets; current_i++) {
        Bucket *bucket = buckets[current_i];

        memcpy(values + total_i, bucket->list_as_array, sizeof(int) * bucket->array_length);
        total_i += bucket->array_length;
    }
}

Bucket *bucket_init(int pivot) {
    Bucket *new_bucket = (Bucket *)malloc(sizeof(Bucket));

    if(new_bucket == NULL) {
        fprintf(stderr, "Couldn't create Bucket.\n");
        exit(EXIT_FAILURE);
    }

    new_bucket->list = list_create();
    new_bucket->pivot = pivot;

    return new_bucket;
}

Bucket **buckets_init(int pivot_step, int amount_of_buckets) {
    Bucket ** new_buckets = (Bucket **)malloc(sizeof(Bucket *) * amount_of_buckets);

    if(new_buckets == NULL) {
        fprintf(stderr, "Couldn't create Buckets.\n");
        exit(EXIT_FAILURE);
    }

    int i;
    int current_pivot = 0;
    for (i = 0; i < amount_of_buckets; i++) {
        new_buckets[i] = bucket_init(current_pivot);
        current_pivot += pivot_step;
    }

    return new_buckets;
}

void buckets_sort_values(Bucket **buckets, int amount_of_buckets, int values[], int values_length) {
    int i, j;

    for (i = 0; i < values_length; i++) {
        int last_suitable_bucket_index = 0;

        for (j = 0; j < amount_of_buckets; j++) {
            if(buckets[j]->pivot > values[i]) {
                break;
            }
            last_suitable_bucket_index = j;
        }

        //printf("Sorting %i into bucket %i with pivot %i\n", values[i], last_suitable_bucket_index, buckets[last_suitable_bucket_index]->pivot);
        Element *element = list_create_element(&values[i]);
        list_append(buckets[last_suitable_bucket_index]->list, element);
    }
}

int determine_max_within_values(int values[], int length) {
    int i, max = INT_MIN;

    for (i = 0; i < length; i++) {
        if(values[i] > max) {
            max = values[i];
        }
    }

    return max;
}

int determine_pivot_step(int values[], int values_length, int amount_of_buckets) {
    int max = determine_max_within_values(values, values_length);
    return max / amount_of_buckets;
}

void array_insertion_sort(int values[], int length) {
    int current_value, i, j;

    for(i = 1; i < length; i++) {
        current_value = values[i];
        j = i-1;
        while(current_value < values[j] && j >= 0) {
            values[j+1] = values[j];
            j = j-1;
        }
        values[j+1] = current_value;
    }
}

void array_fill_random_int(int values[], int length, int min_rand, int max_rand) {
    srand (time(NULL));
    int i;

    for (i = 0; i < length; ++i) {
        values[i] = rand_within_range(min_rand, max_rand);
    }
}

void array_print(int values[], int length) {
    int i;

    for (i = 0; i < length; ++i) {
        printf("%i ", values[i]);
        if(0 == i+1 % PRINT_LINEBREAK) {
            printf("\n");
        }
    }
    printf("\n");
}

int rand_within_range(unsigned int min, unsigned int max) {
    double scaled = (double)rand()/RAND_MAX;
    return (max - min +1)*scaled + min;
}
