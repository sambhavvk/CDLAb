#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct SymbTab {
    char label[10], symbol[10];
    int addr;
    struct SymbTab *next;
} SymbTab;

SymbTab *first = NULL, *last = NULL;
int size = 0;

void insert();
void display();
void delete();
int search(char lab[]);
void modify();

int main() {
    int op, y;
    char la[10];

    do {
        printf("\n1.INSERT\n2.DISPLAY\n3.DELETE\n4.SEARCH\n5.MODIFY\n6.END\n");
        printf("\nEnter your option : ");
        scanf("%d", &op);

        switch (op) {
            case 1: insert(); break;
            case 2: display(); break;
            case 3: delete(); break;
            case 4:
                printf("\nEnter the label to be searched : ");
                scanf("%s", la);
                y = search(la);
                printf("\nSearch Result: %s present in the symbol table\n", y ? "Label is" : "Label is not");
                break;
            case 5: modify(); break;
            case 6: exit(0);
        }
    } while (op < 6);

    return 0;
}

void insert() {
    char l[10];

    printf("\nEnter the label : ");
    scanf("%s", l);

    if (search(l)) {
        printf("\nLabel exists already in the symbol table. Duplicate can't be inserted.");
    } else {
        SymbTab *p = malloc(sizeof(SymbTab));
        strcpy(p->label, l);
        printf("\nEnter the symbol : ");
        scanf("%s", p->symbol);
        printf("\nEnter the address : ");
        scanf("%d", &p->addr);
        p->next = NULL;

        if (size == 0) {
            first = last = p;
        } else {
            last->next = p;
            last = p;
        }
        size++;
        printf("\nLabel inserted\n");
    }
}

void display() {
    SymbTab *p = first;
    printf("\nLABEL\t\tSYMBOL\t\tADDRESS\n");

    for (int i = 0; i < size; i++) {
        printf("%s\t\t%s\t\t%d\n", p->label, p->symbol, p->addr);
        p = p->next;
    }
}

int search(char lab[]) {
    SymbTab *p = first;

    for (int i = 0; i < size; i++) {
        if (strcmp(p->label, lab) == 0) return 1;
        p = p->next;
    }
    return 0;
}

void modify() {
    char l[10], nl[10];
    int add, choice, s;
    SymbTab *p = first;

    printf("\nWhat do you want to modify?\n");
    printf("\n1.Only the label\n2.Only the address\n3.Both the label and address\n");
    printf("\nEnter your choice : ");
    scanf("%d", &choice);

    printf("\nEnter the old label : ");
    scanf("%s", l);
    s = search(l);

    if (s == 0) {
        printf("\nLabel not found\n");
        return;
    }

if (choice == 1 || choice == 3) {
    printf("\nEnter the new label : ");
    scanf("%s", nl);
}

if (choice == 2 || choice == 3) {
    printf("\nEnter the new address : ");
    scanf("%d", &add);
}

for (int i = 0; i < size; i++) {
    if (strcmp(p->label, l) == 0) {
        if (choice == 1 || choice == 3) {
            strcpy(p->label, nl);
        }
        if (choice == 2 || choice == 3) {
            p->addr = add;
        }
    }
    p = p->next;
}
printf("\nAfter Modification:\n");
display();
}

void delete() {
    char l[10];
    SymbTab *p = first, *q;

    printf("\nEnter the label to be deleted : ");
    scanf("%s", l);

    if (!search(l)) {
        printf("\nLabel not found\n");
        return;
    }

    if (strcmp(first->label, l) == 0) {
        first = first->next;
    } else if (strcmp(last->label, l) == 0) {
        while (p->next != last) {
            p = p->next;
        }
        p->next = NULL;
        last = p;
    } else {
        q = p->next;
        while (strcmp(q->label, l) != 0) {
            p = p->next;
            q = q->next;
        }
        p->next = q->next;
    }
    size--;
    printf("\nAfter Deletion:\n");
    display();
}

