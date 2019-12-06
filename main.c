#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node Node;

struct node {
    int key, status;
    Node *left, *right, *parent;
};

Node *root;
int numberOfSequences, lengthOfTheInput;

void insertToBST(Node **p, int key, int insertionType, Node **previousNode) {
    if (*p == NULL) {
        *p = malloc(sizeof(Node));
        (*p)->right = NULL;
        (*p)->left = NULL;
        (*p)->key = key;
        (*p)->status = 0;
        (*previousNode)->status += insertionType;
        if ((*previousNode) == *p)
            (*p)->parent = NULL;
        else
            (*p)->parent = *previousNode;
    } else if (key > (*p)->key)
        insertToBST(&((*p)->right), key, 10, p);
    else
        insertToBST(&((*p)->left), key, 1, p);
}

void takeInput() {
    int temp;
    char ch;
    printf("Enter the numbers please: ");
    while (scanf("%d%c", &temp, &ch) != EOF) {
        lengthOfTheInput++;
        insertToBST(&root, temp, 0, &root);
        if (ch == '\n') break;
    }
    printf("\b");
}

void traverseTree(Node *node) {
    if (node != NULL) {
        traverseTree(node->right);
        printf("%d ", node->key);
        traverseTree(node->left);
    }
}

void printSequence(Node *sequence[], int size) {
    numberOfSequences++;
    printf("%d : [", numberOfSequences);
    int i = 0;
    while (i < size - 1) {
        printf("%d, ", sequence[i]->key);
        i++;
    }
    printf("%d", sequence[i]->key);
    printf("]\n");
}

void listSequences(Node *node, Node *sequence[], int size) {

    int location = 0;
    for (; location < size; ++location) {
        if (sequence[location] == NULL) {
            sequence[location] = node;
            break;
        }
    }

    int i = 0;
    while (i < size && sequence[i] != NULL) {
        // Status 10 means that right child should be inserted
        if (sequence[i]->status / 10 == 1) {
            sequence[i]->status -= 10;
            listSequences(sequence[i]->right, sequence, size);
        }
        //Status 1 means that left child should be inserted
        if (sequence[i]->status % 10 == 1) {
            sequence[i]->status -= 1;
            listSequences(sequence[i]->left, sequence, size);
        }
        i++;
    }

    if (sequence[size - 1] != NULL)
        printSequence(sequence, size);

    //Deleting the node
    if (sequence[location] != NULL && sequence[location]->parent != NULL) {
        if (sequence[location]->parent->key > sequence[location]->key)
            sequence[location]->parent->status += 1;
        else
            sequence[location]->parent->status += 10;
        sequence[location] = NULL;
    }
}

int main() {
    takeInput();

    //Initializing the array
    Node *sequence[lengthOfTheInput];
    for (int i = 0; i < lengthOfTheInput; ++i) {
        sequence[i] = NULL;
    }

    clock_t start, end;

    start = clock();
    listSequences(root, sequence, lengthOfTheInput);
    end = clock();

    double executionTime = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nBST using in-order:\n");
    traverseTree(root);
    printf("\n\nNumber of sequences that yield the same BST: %d", numberOfSequences);
    printf("\nExecution time : %f seconds", executionTime);
    return 0;
}