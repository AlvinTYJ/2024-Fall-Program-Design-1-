#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PREFIXES 100000
#define MAX_TIME_SLOTS 100000
#define TIME_RANGE 1000

unsigned long long int rdtsc()//32-bit
{
	unsigned long long int x;
	asm   volatile ("rdtsc" : "=A" (x));
	return x;
}

unsigned long long int perform_insert[MAX_TIME_SLOTS + 10] = {0};
unsigned long long int perform_delete[MAX_TIME_SLOTS + 10] = {0};
unsigned long long int perform_search[MAX_TIME_SLOTS + 10] = {0};

struct prefix {
    unsigned ip; // The full 32-bit IP addresses
    unsigned char len; // The prefix length (length of subnet mask)
    struct prefix* next; // singly linked-list pointer
};

struct prefix* routing = NULL;
struct prefix* insert = NULL;
struct prefix* delete = NULL;
struct prefix* trace = NULL;
struct prefix* routingGroups[33] = {NULL};
struct prefix* routingGroupsHash[33][256] = {NULL};

static struct prefix* input_array[MAX_PREFIXES];
static int idx = 0;

static struct prefix* group_array[33][MAX_PREFIXES];
static int group_idx[33] = {0};

unsigned ip_to_int(const char* ip) {
    unsigned a, b, c, d;
    sscanf(ip, "%u.%u.%u.%u", &a, &b, &c, &d);
    return (a << 24) | (b << 16) | (c << 8) | d;
}

struct prefix* create_prefix(unsigned ip, unsigned char len) {
    struct prefix* new_prefix = (struct prefix*)malloc(sizeof(struct prefix));
    if (new_prefix == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    new_prefix->ip = ip;
    new_prefix->len = len;
    new_prefix->next = NULL;
    return new_prefix;
}

void insert_prefix(struct prefix** head, struct prefix* new_prefix) {
    if (*head == NULL) {
        *head = new_prefix;
    } else {
        struct prefix* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_prefix;
    }
}

void build_list(struct prefix** head, struct prefix* array[], int length) {
    if (length <= 0) {
        *head = NULL;
        return;
    }

    *head = array[0];
    struct prefix* current = *head;
    for (int i = 1; i < length; i++) {
        current->next = array[i];
        current = current->next;
    }
    current->next = NULL;
}

void input(const char* filename, struct prefix** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char line[20];
    int count = 0;

    memset(input_array, 0, sizeof(input_array));
    idx = 0;
    
    while (fgets(line, sizeof(line), file)) {
        char ip[20];
        unsigned char len;
        
        if (sscanf(line, "%[^/]/%hhu", ip, &len) == 2) {
            input_array[idx++] = create_prefix(ip_to_int(ip), len);
            count++;
        }
		else {
            int segments = 0;
            char* c = line;
            int zero_flag = 0;

            while (*c != '\0') {
                if (*c == '.') {
                    segments++;
                    if (*(c + 1) == '0') {
                        zero_flag = 1;
						break;
                    }
                }
				c++;
            }

            switch (segments) {
                case 1:
                    len = 8;
                    break;  // x.0.0.0
                case 2:
                    len = 16;
                    break; // x.y.0.0
                case 3:
                    len = (zero_flag ? 24 : 32);
                    break; // x.y.z.0 or x.y.z.w
            }

            line[strcspn(line, "\n")] = '\0';
            //printf("IP: %s, Assigned Prefix Length: /%d\n", line, len);

            input_array[idx++] = create_prefix(ip_to_int(line), len);
            count++;
        }
    }

    fclose(file);

    build_list(head, input_array, idx);

    const char* base_filename = strrchr(filename, '/');
    if (base_filename) {
        base_filename++; // Move past the '/' character
    } else {
        base_filename = filename;
    }

    printf("The total number of prefixes in the %s is : %d\n", base_filename, count);
}

void group_len(struct prefix* head, struct prefix* groups[]) {
    for (int i = 0; i < 33; i++) {
        groups[i] = NULL;
        group_idx[i] = 0;
    }

    struct prefix* current = head;
    while (current != NULL) {
        unsigned char l = current->len;
        if (l <= 32) {
            group_array[l][ group_idx[l] ] = create_prefix(current->ip, current->len);
            group_idx[l]++;
        }
        current = current->next;
    }

    for (int i = 0; i < 33; i++) {
        if (group_idx[i] > 0) {
            build_list(&groups[i], group_array[i], group_idx[i]);
        }
    }
}

void length_distribution(struct prefix* groups[]) {
    for (int i = 0; i <= 32; i++) {
        int count = 0;
        struct prefix* current = groups[i];
        while (current != NULL) {
            count++;
            current = current->next;
        }
        if (count > 0) {
            printf("the number of prefixes with prefix length %d = %d\n", i, count);
        }
    }
}

void segment(struct prefix* groups[], struct prefix* hash_tables[][256]) {
    for (int i = 0; i <= 32; i++) {
        if (groups[i] != NULL) {
            struct prefix* current = groups[i];
            while (current != NULL) {
                unsigned char bucket = (current->ip >> 24) & 0xFF;
                insert_prefix(&hash_tables[i][bucket], create_prefix(current->ip, current->len));
                current = current->next;
            }
        }
    }
}

void print_hash_table(struct prefix* hash_tables[][256]) {
    struct prefix* current = NULL;
    int count = 0;

    for (int i = 24; i < 25; i++) {
        for (int j = 65; j < 66; j++) {
            count=0;
            current = hash_tables[i][j];
            if (current != NULL) {
                printf("Group %d, Bucket %d: ", i, j);
                while (current != NULL) {
                    /*
                    printf("%u.%u.%u.%u/%d -> ",
                           (current->ip >> 24) & 0xFF,
                           (current->ip >> 16) & 0xFF,
                           (current->ip >> 8) & 0xFF,
                           current->ip & 0xFF,
                           current->len);
                    */
                    count++;
                    current = current->next;
                }
                printf("count: %d\n", count);
                //printf("NULL\n");
            }
        }
    }
}

void prefix_insert(struct prefix* insert_list, struct prefix* hash_tables[][256]) {
    struct prefix* insertCurr = insert_list;
    unsigned char bucket = 0;
    unsigned char len = 0;
    struct prefix** head = NULL;
    struct prefix* new_prefix = NULL;
    struct prefix* hashCurr = NULL;

    unsigned long long int begin, end, cycles, index;
    while (insertCurr != NULL) {
        begin = rdtsc();

        len = insertCurr->len;
        bucket = (insertCurr->ip >> 24) & 0xFF;
        head = &hash_tables[len][bucket];
        new_prefix = create_prefix(insertCurr->ip, len);

        if (*head == NULL || (*head)->ip > new_prefix->ip) {
            new_prefix->next = *head;
            *head = new_prefix;
        } else {
            hashCurr = *head;
            while (hashCurr->next != NULL && hashCurr->next->ip < new_prefix->ip) {
                hashCurr = hashCurr->next;
            }
            new_prefix->next = hashCurr->next;
            hashCurr->next = new_prefix;
        }

        insertCurr = insertCurr->next;

        end = rdtsc();
        cycles = end - begin;
        index = cycles / TIME_RANGE;

        if (index < MAX_TIME_SLOTS) {
            perform_insert[index]++;
        }
    }
}

void prefix_delete(struct prefix* delete_list, struct prefix* hash_tables[][256]) {
    struct prefix* deleteCurr = delete_list;
    unsigned char bucket = 0;
    unsigned char len = 0;
    struct prefix** head = NULL;
    struct prefix* hashCurr = NULL;
    struct prefix* prev = NULL;

    unsigned long long int begin, end, cycles, index;
    while (deleteCurr != NULL) {
        begin = rdtsc();

        len = deleteCurr->len;
        bucket = (deleteCurr->ip >> 24) & 0xFF;
        head = &hash_tables[len][bucket];
        hashCurr = *head;
        prev = NULL;

        while (hashCurr != NULL) {
            if (hashCurr->ip == deleteCurr->ip && hashCurr->len == deleteCurr->len) {
                if (prev == NULL) {
                    *head = hashCurr->next;
                } else {
                    prev->next = hashCurr->next;
                }
                free(hashCurr);
                break;
            }
            prev = hashCurr;
            hashCurr = hashCurr->next;
        }

        deleteCurr = deleteCurr->next;

        end = rdtsc();
        cycles = end - begin;
        index = cycles / TIME_RANGE;

        if (index < MAX_TIME_SLOTS) {
            perform_delete[index]++;
        }
    }
}

void search(struct prefix* trace_list, struct prefix* hash_tables[][256]) {
    struct prefix* traceCurr = trace_list;
    unsigned char bucket;
    struct prefix* hashCurr;
    int found;

    unsigned long long int begin, end, cycles, index;
    while (traceCurr != NULL) {
        begin = rdtsc();
        found = 0;

        for (int len = 32; len >= 0 && !found; len--) {
            bucket = (traceCurr->ip >> 24) & 0xFF;
            hashCurr = hash_tables[len][bucket];

            while (hashCurr != NULL) {
                if ((traceCurr->ip & (~0 << (32 - len))) == (hashCurr->ip & (~0 << (32 - len)))) {
                    /*
                    printf("Search for %u.%u.%u.%u/%d: Successful\n",
                           (traceCurr->ip >> 24) & 0xFF,
                           (traceCurr->ip >> 16) & 0xFF,
                           (traceCurr->ip >> 8) & 0xFF,
                           traceCurr->ip & 0xFF,
                           len);
                    */
                    found = 1;
                    break;
                }
                hashCurr = hashCurr->next;
            }
        }
        
        if (!found) {
            /*
            printf("Search for %u.%u.%u.%u: Failed\n",
                   (traceCurr->ip >> 24) & 0xFF,
                   (traceCurr->ip >> 16) & 0xFF,
                   (traceCurr->ip >> 8) & 0xFF,
                   traceCurr->ip & 0xFF);
            */
        }
        
        traceCurr = traceCurr->next;
        end = rdtsc();
        cycles = end - begin;
        index = cycles / TIME_RANGE;
        if (index < MAX_TIME_SLOTS) {
            perform_search[index]++;
        }
    }
}

void print_histogram(const char *operation, unsigned long long int *histogram) {
    printf("\nHistogram for %s:\n", operation);
    for (int i = 0; i < MAX_TIME_SLOTS; i++) {
        if (histogram[i] > 0) {
            printf("Range %d-%d: %llu occurrences\n",
                   i * TIME_RANGE, (i + 1) * TIME_RANGE - 1, histogram[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    printf("The file initializing the routing table: %s\n", argv[1]);
    printf("The file for extra insertion into the routing table: %s\n", argv[2]);
    printf("The file to delete specific IPs from the routing table: %s\n", argv[3]);
    printf("The file for IP lookups: %s\n", argv[4]);
    printf("\n");

    input(argv[1], &routing);
    printf("\n");

    input(argv[2], &insert);
    input(argv[3], &delete);
    input(argv[4], &trace);

    group_len(routing, routingGroups);

    length_distribution(routingGroups);

    segment(routingGroups, routingGroupsHash);
    //print_hash_table(routingGroupsHash);

    prefix_insert(insert, routingGroupsHash);
    prefix_delete(delete, routingGroupsHash);
    search(trace, routingGroupsHash);

    print_histogram("Insertion", perform_insert);
    print_histogram("Deletion", perform_delete);
    print_histogram("Search", perform_search);

    return 0;
}