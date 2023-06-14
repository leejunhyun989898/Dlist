#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef char element[MAX];
typedef struct DlistNode {
    element data;
    struct DlistNode* llink;
    struct DlistNode* rlink;
} DlistNode;

DlistNode* current;

void init(DlistNode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

void print_dlist(DlistNode* phead, DlistNode* current) {
    DlistNode* p;
    for (p = phead->rlink; p != phead; p = p->rlink) {
        if (p == current) {
            printf("<-| [%s] [0]|-> ", p->data);
        }
        else {
            printf("<-| [%s] |-> ", p->data);
        }
    }
    printf("\n");
}

void dinsert(DlistNode* before, element data) {
    DlistNode* newnode = (DlistNode*)malloc(sizeof(DlistNode));
    strcpy_s(newnode->data, sizeof(newnode->data), data);
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

void ddelete(DlistNode* head, DlistNode* removed) {
    if (removed == head) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

int main() {
    DlistNode* head = (DlistNode*)malloc(sizeof(DlistNode));
    init(head);
    char option;
    element fruit;



    do {
        printf("\n[Menu]\n");
        printf("n) ���� ����\n");
        printf("p) ���� ����\n");
        printf("d) ���� ���� ����\n");
        printf("i) ���� ���� ������ ���� �߰�\n");
        printf("o) ���� ����Ʈ ���\n");
        printf("e) ���α׷� ����\n");
        printf("�޴��� �����ϼ���: ");
        scanf_s(" %c", &option, sizeof(option));

        switch (option) {
        case 'n':  // ���� ����
            if (current->rlink != head) {
                current = current->rlink;
                printf("���� ���Ϸ� �̵�: %s\n", current->data);
            }
            else {
                printf("�� �̻� ���� ������ �����ϴ�.\n");
            }
            break;
        case 'p':  // ���� ����
            if (current->llink != head) {
                current = current->llink;
                printf("���� ���Ϸ� �̵�: %s\n", current->data);
            }
            else {
                printf("�� �̻� ���� ������ �����ϴ�.\n");
            }
            break;
        case 'd':  // ���� ���� ����
            ddelete(head, current);
            current = head->rlink;
            //printf("������ ���� : %s\n");
            break;

        case 'i':  // ���� ���� ������ ���� �߰�
            printf("�߰��� ������ �Է��ϼ���: ");
            scanf_s("%s", fruit, sizeof(fruit));
            
            dinsert(head, fruit);
            current = head->rlink;
            printf("���� �߰�: %s\n", fruit);
            break;

        case 'o':  // ���� ����Ʈ ���
            print_dlist(head, current);
            break;
        case 'e':  // ���α׷� ����
            printf("���α׷��� �����մϴ�.\n");
            break;
        default:
            printf("�߸��� �޴��� �����Ͽ����ϴ�.\n");
        }

        // �Է� ���ۿ� �����ִ� ���� ���� ó��
        while (getchar() != '\n');

    } while (option != 'e');

    DlistNode* p = head->rlink;
    while (p != head) {
        DlistNode* next = p->rlink;
        free(p);
        p = next;
    }
    free(head);

    return 0;
}

