#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

unsigned ip_to_int(const char* ip) {
    unsigned a, b, c, d;
    sscanf(ip, "%u.%u.%u.%u", &a, &b, &c, &d);
    return (a << 24) | (b << 16) | (c << 8) | d;
}

struct prefix* create_prefix(const char* ip, unsigned char len) {
    struct prefix* new_prefix = (struct prefix*)malloc(sizeof(struct prefix));
    if (new_prefix == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    new_prefix->ip = ip_to_int(ip);
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

void input(const char* filename, struct prefix** head) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char line[20];
    int count = 0;
    
    while (fgets(line, sizeof(line), file)) {
        char ip[20];
        unsigned char len;
        
        if (sscanf(line, "%[^/]/%hhu", ip, &len) == 2) {
            struct prefix* new_prefix = create_prefix(ip, len);
            insert_prefix(head, new_prefix);
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
                case 1: len = 8; break;  // x.0.0.0
                case 2: len = 16; break; // x.y.0.0
                case 3: len = zero_flag ? 24 : 32; break; // x.y.z.0 or x.y.z.w
            }

            line[strcspn(line, "\n")] = '\0';
            //printf("IP: %s, Assigned Prefix Length: /%d\n", line, len);

            struct prefix* new_prefix = create_prefix(line, len);
            insert_prefix(head, new_prefix);
            count++;
        }
    }

    fclose(file);

    const char* base_filename = strrchr(filename, '/');
    if (base_filename) {
        base_filename++; // Move past the '/' character
    } else {
        base_filename = filename; // No '/' in the path, use the entire string
    }

    printf("The total number of prefixes in the %s is : %d\n", base_filename, count);
}

struct prefix* create_prefix2(unsigned ip, unsigned char len) {
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

void group_len(struct prefix* head, struct prefix* groups[]) {
    for (int i = 0; i < 33; i++) {
        groups[i] = NULL;
    }

    struct prefix* current = head;
    unsigned char len;
    while (current != NULL) {
        len = current->len;
        if (len <= 32) {
            insert_prefix(&groups[len], create_prefix2(current->ip, len));
        }
        current = current->next;
    }
}

void length_distribution(struct prefix* groups[]) {
    struct prefix* current = NULL;
    int count = 0;
    for (int i=0; i<=32; i++) {
        count = 0;
        current = groups[i];
        while (current!=NULL) {
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
                insert_prefix(&hash_tables[i][bucket], create_prefix2(current->ip, current->len));
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

    while (insertCurr != NULL) {
        len = insertCurr->len;
        bucket = (insertCurr->ip >> 24) & 0xFF;

        head = &hash_tables[len][bucket];
        new_prefix = create_prefix2(insertCurr->ip, len);
        
        if (*head == NULL || (*head)->ip > new_prefix->ip) {
            new_prefix->next = *head;
            *head = new_prefix;
        }
        else {
            hashCurr = *head;
            while (hashCurr->next != NULL && hashCurr->next->ip < new_prefix->ip) {
                hashCurr = hashCurr->next;
            }
            new_prefix->next = hashCurr->next;
            hashCurr->next = new_prefix;
        }

        insertCurr = insertCurr->next;
    }
}

void prefix_delete(struct prefix* delete_list, struct prefix* hash_tables[][256]) {
    struct prefix* deleteCurr = delete_list;
    unsigned char bucket = 0;
    unsigned char len = 0;
    struct prefix** head = NULL;
    struct prefix* hashCurr = NULL;
    struct prefix* prev = NULL;

    while (deleteCurr != NULL) {
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
                break;
            }
            prev = hashCurr;
            hashCurr = hashCurr->next;
        }
        deleteCurr = deleteCurr->next;
    }
}

void search(struct prefix* trace_list, struct prefix* hash_tables[][256]) {
    struct prefix* traceCurr = trace_list;
    unsigned char bucket;
    struct prefix* hashCurr;
    int found;

    while (traceCurr != NULL) {
        found = 0;

        for (int len = 32; len >= 0 && !found; len--) {
            bucket = (traceCurr->ip >> 24) & 0xFF;
            hashCurr = hash_tables[len][bucket];

            while (hashCurr != NULL) {
                if ((traceCurr->ip & (~0 << (32 - len))) == (hashCurr->ip & (~0 << (32 - len)))) {
                    printf("Search for %u.%u.%u.%u/%d: Successful\n",
                           (traceCurr->ip >> 24) & 0xFF,
                           (traceCurr->ip >> 16) & 0xFF,
                           (traceCurr->ip >> 8) & 0xFF,
                           traceCurr->ip & 0xFF,
                           len);
                    found = 1;
                    break;
                }
                hashCurr = hashCurr->next;
            }
        }
        
        if (!found) {
            printf("Search for %u.%u.%u.%u: Failed\n",
                   (traceCurr->ip >> 24) & 0xFF,
                   (traceCurr->ip >> 16) & 0xFF,
                   (traceCurr->ip >> 8) & 0xFF,
                   traceCurr->ip & 0xFF);
        }
        
        traceCurr = traceCurr->next;
    }
    return;
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

    //segment(routingGroups, routingGroupsHash);
    //print_hash_table(routingGroupsHash);

    //prefix_insert(insert, routingGroupsHash);

    //prefix_delete(delete, routingGroupsHash);

    //search(trace, routingGroupsHash);

    return 0;
}