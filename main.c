#include <limits.h>
#include <stdbool.h>
#include <stdio.h>


#define N_AREAS 6

static const unsigned flow_matrix[N_AREAS][N_AREAS] = {
    {  0, 100,  50,   0,   0,  50},
    { 25,   0,   0,  50,   0,   0},
    { 25,   0,   0,   0,  50,   0},
    {  0,  25,   0,   0,  20,   0},
    { 50,   0, 100,   0,   0,   0},
    { 10,   0,  20,   0,   0,   0},
};

// This is the Manhattan distance between the source and destination areas
static const unsigned distances[N_AREAS][N_AREAS] = {
    { 00, 20, 40, 20, 40, 60 },
    { 20, 00, 20, 40, 20, 40 },
    { 40, 20, 00, 60, 40, 20 },
    { 20, 40, 60, 00, 20, 40 },
    { 40, 20, 40, 20, 00, 20 },
    { 60, 40, 20, 40, 20, 00 },
};

static const char *process_names[N_AREAS] = {
    "Materials",
    "Welding",
    "Drills",
    "Lathes",
    "Grinders",
    "Benders",
};

// The lowest cost we have seen so far
static unsigned best_cost = UINT_MAX;
// Whether we should output solutions with the lowest cost
static bool output = false;


static unsigned get_cost(const unsigned (*restrict processes)[N_AREAS]) {
    unsigned total_cost = 0;

    for (unsigned source_area = 0; source_area < N_AREAS; source_area++) {
        // The row index is the source
        unsigned source_process = (*processes)[source_area];

        for (unsigned dest_area = 0; dest_area < N_AREAS; dest_area++) {
            // The column index is the destination
            unsigned dest_process = (*processes)[dest_area],
                     flow = flow_matrix[source_process][dest_process],
                     distance = distances[source_area][dest_area];

            total_cost += flow * distance;
        }
    }

    return total_cost;
}


static void check_solution(const unsigned (*restrict processes)[N_AREAS]) {
    unsigned cost = get_cost(processes);
    if (output)    {
        if (cost == best_cost) {
            unsigned w = N_AREAS/2, area = 0;
            for (unsigned y = 0; y < 2; y++, area += w) {
                for (unsigned x = 0; x < w; x++)
                    printf("%9d ", area + x + 1);
                putchar('\n');

                for (unsigned x = 0; x < w; x++) {
                    unsigned process = (*processes)[area + x];
                    printf("%9s ", process_names[process]);
                }
                putchar('\n');
            }
            putchar('\n');
        }
    }
    else if (best_cost > cost)
        best_cost = cost;
}


static void swap(unsigned *restrict x, unsigned *restrict y) {
    unsigned temp = *x;
    *x = *y;
    *y = temp;
}


// Based on
// https://www.geeksforgeeks.org/heaps-algorithm-for-generating-permutations/
static void permute(unsigned (*restrict a)[N_AREAS], unsigned size) {
    if (size == 1)
        check_solution(a);
    else for (unsigned i = 0; i < size; i++) {
        permute(a, size - 1);

        if (size & 1)
            swap(*a, *a + size - 1);
        else
            swap(*a + i, *a + size - 1);
    }
}


int main() {
    printf("Number of processes to locate: %u\n", N_AREAS);

    unsigned processes[N_AREAS];
    for (unsigned i = 0; i < N_AREAS; i++)
        processes[i] = i;

    permute(&processes, N_AREAS);
    printf("The smallest total rate-distance product cost found is %u\n"
           "The best area arrangements at this cost are:\n\n",
           best_cost);
    output = true;
    permute(&processes, N_AREAS);
   
    return 0;
}
