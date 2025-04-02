#include <stdlib.h>
#include <stdio.h>

#define MAX_TIME_SLOTS 100000 // Depends on your computer performance
#define TIME_RANGE 100        // Depends on your needs

unsigned long long int perform_search[MAX_TIME_SLOTS + 10] = {0};

unsigned long long int rdtsc()//32-bit
{
	unsigned long long int x;
	asm   volatile ("rdtsc" : "=A" (x));
	return x;
}

void search() {
    // Simulate the search operation
    for (volatile int i = 0; i < 1000; i++) { /* no-op */ }
}

int main() {
    for (int i = 0; i < 10000; i++) {
        unsigned long long int begin, end;
        begin = rdtsc();
        search();
        end = rdtsc();

        unsigned long long int cycles = end - begin;
        unsigned long long int index = cycles / TIME_RANGE;

        if (index < MAX_TIME_SLOTS) {
            perform_search[index]++;
        } else {
            printf("Warning: Cycle count %llu exceeds max time slot range\n", cycles);
        }
    }

    // Print histogram
    for (int i = 0; i < MAX_TIME_SLOTS; i++) {
        if (perform_search[i] > 0) {
            printf("Range %d-%d: %llu occurrences\n", i * TIME_RANGE, (i + 1) * TIME_RANGE - 1, perform_search[i]);
        }
		
    }

    return 0;
}