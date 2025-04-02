#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PREFIXES 100000

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

void build_list(struct prefix** head, struct prefix* array[], int length) {
    // If no elements, just set *head = NULL
    if (length <= 0) {
        *head = NULL;
        return;
    }

    // Link all array elements
    *head = array[0];
    struct prefix* current = *head;
    for (int i = 1; i < length; i++) {
        current->next = array[i];
        current = current->next;
    }
    // Ensure the last one points to NULL
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
        base_filename = filename; // No '/' in the path, use the entire string
    }

    printf("The total number of prefixes in the %s is : %d\n", base_filename, count);
}

void group_len(struct prefix* head, struct prefix* groups[]) {
    // Clear everything first
    for (int i = 0; i < 33; i++) {
        groups[i] = NULL;
        group_idx[i] = 0;
    }

    // Walk the 'head' list and stash the prefixes in their group_array bucket
    struct prefix* current = head;
    while (current != NULL) {
        unsigned char l = current->len;
        if (l <= 32) {
            group_array[l][ group_idx[l] ] = create_prefix(current->ip, current->len);
            group_idx[l]++;
        }
        current = current->next;
    }

    // Now build a separate linked list for each prefix length
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

int main(int argc, char *argv[]) {
    printf("The file initializing the routing table: %s\n", argv[1]);
    printf("The file for extra insertion into the routing table: %s\n", argv[2]);
    printf("The file to delete specific IPs from the routing table: %s\n", argv[3]);
    printf("The file for IP lookups: %s\n", argv[4]);
    printf("\n");

    input(argv[1], &routing);
    printf("\n");

    //input(argv[2], &insert);
    //input(argv[3], &delete);
    //input(argv[4], &trace);

    group_len(routing, routingGroups);

    length_distribution(routingGroups);

    return 0;
}