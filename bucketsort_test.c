#include <stdio.h>
#include <stdlib.h>
#include "lib/minunit.h"
#include "bucketsort.c"

#define ARRAY_LENGTH 10000
#define ARRAY_LENGTH_PENETRATION 2000000

static void test_array_filled_with_random_values() {
    int values[ARRAY_LENGTH];
    int i;
    array_fill_random_int(values, ARRAY_LENGTH, 1, 250);

    for (i = 0; i < ARRAY_LENGTH; i++) {
        assert((1 <= values[i] && values[i] <= 250));
    }
}

static void test_find_max_of_values() {
    int values[] = {30,14,65,38,27,5,79,44,63,99};
    int length = sizeof(values)/sizeof(int);

    int max = determine_max_within_values(values, length);
    assert(values[length-1] == max);

    values[0] = 100;
    max = determine_max_within_values(values, length);
    assert(values[0] == max);

    values[5] = 100000;
    max = determine_max_within_values(values, length);
    assert(values[5] == max);
}

static void test_find_pivot_step() {
    int values[] = {30,14,65,38,27,5,79,44,63,99,23,41,36,55,01,11,42,76,22,87};
    int length = sizeof(values)/sizeof(int);

    int amount_of_buckets = 4;
    int max = determine_max_within_values(values, length);

    int pivot_step = max / amount_of_buckets;
    assert(pivot_step == 24); // floor(99 / 4) == 24

    int pivot_step_calc = determine_pivot_step(values, length, amount_of_buckets);

    assert(pivot_step == pivot_step_calc);
}

static void test_init_and_destroy_bucket() {
    Bucket *bucket = bucket_init(5);

    assert(bucket->pivot == 5);

    free(bucket);
    assert(bucket->pivot == 0);
}

static void test_create_buckets_by_pivot() {
    int values[] = {30,14,65,38,27,5,79,44,63,99,23,41,36,55,01,11,42,76,22,87};
    int length = sizeof(values)/sizeof(int);

    int amount_of_buckets = 4;
    int pivot_step = determine_pivot_step(values, length, amount_of_buckets);

    Bucket **buckets = buckets_init(pivot_step, amount_of_buckets);

    assert(buckets[0]->pivot == 0);
    int i;
    for (i = 1; i < amount_of_buckets; i++) {
        assert(buckets[i]->pivot != 0);
    }
    assert(buckets[amount_of_buckets-1]->pivot == pivot_step * (amount_of_buckets-1)); // == 72
}

static void test_sort_array_values_into_buckets() {
    int values[] = {30,14,65,38,27,5,79,44,63,99,23,41,36,55,01,11,42,76,22,87};
    int values_length = sizeof(values)/sizeof(int);

    int amount_of_buckets = 4;
    int pivot_step = determine_pivot_step(values, values_length, amount_of_buckets);
    Bucket **buckets = buckets_init(pivot_step, amount_of_buckets);

    buckets_sort_values(buckets, amount_of_buckets, values, values_length);

    int i;
    for (i = 0; i < amount_of_buckets; i++) {
        //printf("bucket with pivot %i contains: ", buckets[i]->pivot);
        //list_print(buckets[i]->list);

        assert(buckets[i]->pivot <= *(buckets[i]->list->head->ptr));
        assert(buckets[i]->pivot <= *(buckets[i]->list->last->ptr));
        assert(buckets[i]->list->head->ptr != buckets[i]->list->last->ptr);
    }
}

static void test_sort_array_values_into_buckets_heavy_penetration() {
    int values_length = ARRAY_LENGTH_PENETRATION;

    int values[ARRAY_LENGTH_PENETRATION];
    array_fill_random_int(values, values_length, 1, 9999);

    int amount_of_buckets = 100;
    int pivot_step = determine_pivot_step(values, values_length, amount_of_buckets);
    Bucket **buckets = buckets_init(pivot_step, amount_of_buckets);

    buckets_sort_values(buckets, amount_of_buckets, values, values_length);

    int i;
    for (i = 0; i < amount_of_buckets; i++) {
        assert(buckets[i]->pivot <= *(buckets[i]->list->head->ptr));
        assert(buckets[i]->pivot <= *(buckets[i]->list->last->ptr));
        assert(buckets[i]->list->head->ptr != buckets[i]->list->last->ptr);
    }
}

static void test_array_insertion_sort() {
    int values1[10] = {4,2,6,5,1,0,7,8,9,3};
    int values2[10] = {0,1,2,3,4,5,6,7,8,9};

    array_insertion_sort(values1, 10);

    int i;
    for (i = 0; i < 10; i++) {
        assert(values1[i] == values2[i]);
    }
}

static void test_array_insertion_sort_penetration() {
    int values_length = ARRAY_LENGTH;

    int values[ARRAY_LENGTH];
    array_fill_random_int(values, values_length, 1, 9999);

    array_insertion_sort(values, values_length);
    int i, last_element = 0;
    for (i = 0; i < 10; i++) {
        assert(last_element <= values[i]);
        last_element = values[i];
    }
}

static void test_bucketsort() {
    int values1[10] = {4,2,6,5,1,0,7,8,9,3};
    int values2[10] = {0,1,2,3,4,5,6,7,8,9};

    bucketsort(values1, 10, 3);

    int i;
    for (i = 0; i < 10; i++) {
        //printf("%i == %i\n", values1[i], values2[i]);
        assert(values1[i] == values2[i]);
    }
}

static void test_bucketsort_penetration() {
    int values_length = ARRAY_LENGTH_PENETRATION;

    int values[ARRAY_LENGTH_PENETRATION];
    array_fill_random_int(values, values_length, 1, 9999);

    int amount_of_buckets = 1000;

    bucketsort(values, values_length, amount_of_buckets);

    int i, last_element = 0;
    for (i = 0; i < values_length; i++) {
        assert(last_element <= values[i]);
        last_element = values[i];
    }
}

static void all_tests() {
    mu_run_test(test_array_filled_with_random_values);
    mu_run_test(test_find_max_of_values);
    mu_run_test(test_find_pivot_step);
    mu_run_test(test_init_and_destroy_bucket);
    mu_run_test(test_create_buckets_by_pivot);
    mu_run_test(test_sort_array_values_into_buckets);
    mu_run_test(test_sort_array_values_into_buckets_heavy_penetration);
    mu_run_test(test_array_insertion_sort);
    mu_run_test(test_array_insertion_sort_penetration);
    mu_run_test(test_bucketsort);
    mu_run_test(test_bucketsort_penetration);
}

int main(int argc, char **argv) {
    all_tests();

    printf("ALL TESTS PASSED\n");
    printf("Tests run: %d\n", tests_run);

    return EXIT_SUCCESS;
}
