#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#include "../../utils/primes.hpp"

#define ONE_OVER_MILLION 1E-6

#define BUFFER_INITIAL_SIZE 10
#define MULTIPLIER 2

struct operation_step{
    uint64_t value;
    uint64_t numerator;
    int64_t denominator;
};

struct operation_step* step_buffer = NULL;
uint32_t step_buffer_size = 0;

uint64_t square(uint64_t number){
    uint64_t min = 1;
    uint64_t max = 2;
    while (max * max <= number) {
        max <<= 1;
    }
    min = max >> 1;
    bool handler = false;
    while (min < max) {
        handler = !handler;
        uint64_t mid = (min + max + handler) >> 1;
        uint64_t square = mid * mid;
        if (square < number) {
            min = mid;
        } else if (square > number) {
            max = mid - 1;
        } else {
            return mid;
        }
    }
    return min;
}

uint64_t periodic_continued_fractions_period(int64_t number) {
    int64_t squareNumber = square(number);
    if (squareNumber * squareNumber == number) return 0;
    uint64_t index = 0;
    uint64_t res = 0;

    struct operation_step* step = &step_buffer[index++];
    step->value = squareNumber;
    step->numerator = 1;
    step->denominator = -squareNumber;
    bool running = true;

    // printf("%lu: \n", step->value);

    for (; running; index++) {
        if (index == step_buffer_size) {
            step_buffer_size *= MULTIPLIER;
            step_buffer = (struct operation_step*)realloc(step_buffer,
                sizeof(struct operation_step) * step_buffer_size);
        }
        struct operation_step* prev = step;
        step = &step_buffer[index];
        uint64_t temp_mul = prev->numerator;
        int64_t temp1 = -prev->denominator;
        int64_t temp_denominator = number - (temp1 * temp1);

        // fprintf(stderr, "\t\tTEMP_MUL: %lu\n", temp_mul);
        // fprintf(stderr, "\t\tTEMP1: %ld\n", temp1);
        // fprintf(stderr, "\t\tTEMP_DENOMINATOR: %lu\n", temp_denominator);

        // Sanity check
        if (temp_denominator % temp_mul != 0) {
            fprintf(stderr, "Well, something went wrong with number %lu",
                number);
            exit(EXIT_FAILURE);
        }

        temp_denominator /= temp_mul;
        uint64_t temp_value = 0;
        while (temp1 - temp_denominator >= -squareNumber) {
            temp1 -= temp_denominator;
            temp_value++;
        }

        fprintf(stderr, "\n");
        fprintf(stderr, "\t\tTEMP_VALUE BECAME       %lu\n", temp_value);
        fprintf(stderr, "\t\tTEMP_DENOMINATOR BECAME %lu\n", temp_denominator);
        fprintf(stderr, "\t\tTEMP1 BECAME            %ld\n", temp1);

        step->value = temp_value;
        step->numerator = temp_denominator;
        step->denominator = temp1;

        // printf("\t%lu\n", temp_value);

        uint64_t chk_index = index - 1;
        for (; chk_index > 0; chk_index--) {
            if (memcmp(step, &step_buffer[chk_index],
                    sizeof(struct operation_step)) == 0) {
                running = false;
                res = index - chk_index;
                break;
            }
        }
    }

    // printf("\n");

    return res;
}

uint64_t magic() {
    step_buffer_size = BUFFER_INITIAL_SIZE;
    step_buffer = (struct operation_step*)
        malloc(sizeof(struct operation_step) * step_buffer_size);

    if (step_buffer == NULL) {
        fprintf(stderr, "Could not allocate memory for buffer.\n");
        exit(EXIT_FAILURE);
    }

    uint64_t res = 0;
    for (uint64_t number = 1; number <= 10; number++) {
        // printf("Processing number %lu\n", number);
        uint64_t period = periodic_continued_fractions_period(number);
        printf("%lu - %lu\n", number, period);
        if (period != 0 && period % 2 != 0) {
            res++;
        }
    }

    return res;
}

int main() {
    // Calculate time taken by a request
    struct timespec requestStart, requestEnd;
    clock_gettime(CLOCK_REALTIME, &requestStart);
    uint64_t res = magic();
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    printf("If you can trust me, the number you are "
            "looking for is %lu\n", res);
    double accum = (requestEnd.tv_sec - requestStart.tv_sec)
      + (requestEnd.tv_nsec - requestStart.tv_nsec)
      * ONE_OVER_MILLION;
    printf("Execution time: %.3lf ms\n", accum);
    return 0;
}
