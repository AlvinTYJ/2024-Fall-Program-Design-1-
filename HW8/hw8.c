#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void splitList(Node* head, Node** oddList, Node** evenList) {
    while (head != NULL) {
        if (head->data % 2 == 1) {
            append(oddList, head->data);
        }
        else {
            append(evenList, head->data);
        }
        head = head->next;
    }
}

void reverseList(Node** head) {
    Node* prev = NULL;
    Node* current = *head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;  // Store next node
        current->next = prev;  // Reverse current node's pointer
        prev = current;        // Move prev to current
        current = next;        // Move to the next node
    }
    *head = prev;  // Update head to the new first node
}

Node* search_list(Node* list, int n) {
    Node* p;
    for (p = list; p != NULL; p = p->next) {
        if (p->data == n)
            return p;
    }
    return NULL;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;
    Node* oddList = NULL;
    Node* evenList = NULL;

    append(&head, 1);
    append(&head, 3);
    append(&head, 2);
    append(&head, 4);

    splitList(head, &oddList, &evenList);
    printf("Odd Value List: ");
    printList(oddList);
    printf("Even Value List: ");
    printList(evenList);

    printf("Initial List: ");
    printList(head);
    printf("After Reversed: ");
    reverseList(&head);
    printList(head);

    int searchValue = 3;
    Node* searchResult = search_list(head, searchValue);
    if (searchResult != NULL) {
        printf("Value %d found in the list.\n", searchValue);
    } else {
        printf("Value %d not found in the list.\n", searchValue);
    }

    return 0;
}

/*
Odd Value List: 1 -> 3 -> NULL
Even Value List: 2 -> 4 -> NULL
Initial List: 1 -> 3 -> 2 -> 4 -> NULL
After Reversed: 4 -> 2 -> 3 -> 1 -> NULL
Value 3 found in the list.
*/