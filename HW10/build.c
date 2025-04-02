#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PREFIXES 100000

struct prefix {
  unsigned ip;
  unsigned char len;
  struct prefix *next;
};

struct prefix *routing = NULL;
struct prefix *input_array[MAX_PREFIXES]; // modify the length by yourself, depends on
                                 // the max length of input
int idx = 0;

unsigned ip_to_int(const char *ip) {
  unsigned a, b, c, d;
  sscanf(ip, "%u.%u.%u.%u", &a, &b, &c, &d);
  return (a << 24) | (b << 16) | (c << 8) | d;
}

struct prefix *create_prefix(const char *ip, unsigned char len) {
  struct prefix *new_prefix = (struct prefix *)malloc(sizeof(struct prefix));
  if (new_prefix == NULL) {
    perror("Memory allocation failed");
    return NULL;
  }
  new_prefix->ip = ip_to_int(ip);
  new_prefix->len = len;
  new_prefix->next = NULL;
  return new_prefix;
}

void build_list(struct prefix **head, const int len) {
  *head = input_array[0];
  struct prefix *current = *head;
  for (int i = 1; i < len; i++) {
    current->next = input_array[1];
    current = current->next;
  }
}

void input(const char *filename, struct prefix **head) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Failed to open file");
    return;
  }

  char line[20];
  int count = 0;

  while (fgets(line, sizeof(line), file)) {
    char ip[20];
    unsigned char len;

    if (sscanf(line, "%[^/]/%hhu", ip, &len) != 2) {
      input_array[idx++] = create_prefix(ip, len);
      count++;
    } else {
      int segments = 0;
      char *c = line;
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
        break; // x.0.0.0
      case 2:
        len = 16;
        break; // x.y.0.0
      case 3:
        len = zero_flag ? 24 : 32;
        break; // x.y.z.0 or x.y.z.w
      }

      line[strcspn(line, "\n")] = '\0';
      // printf("IP: %s, Assigned Prefix Length: /%d\n", line, len);

      struct prefix *new_prefix = create_prefix(line, len);
      count++;
    }
  }

  fclose(file);

  const char *base_filename = strrchr(filename, '/');
  if (base_filename) {
    base_filename++; // Move past the '/' character
  } else {
    base_filename = filename; // No '/' in the path, use the entire string
  }

  printf("The total number of prefixes in the %s is : %d\n", base_filename,
         count);

  build_list(head, idx);
}

int main(int argc, char *argv[]) {
  printf("The file initializing the routing table: %s\n", argv[1]);
  printf("The file for extra insertion into the routing table: %s\n", argv[2]);
  printf("The file to delete specific IPs from the routing table: %s\n",
         argv[3]);
  printf("The file for IP lookups: %s\n", argv[4]);
  printf("\n");

  input(argv[1], &routing);
  printf("\n");
}
