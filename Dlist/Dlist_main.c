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
        printf("n) 다음 과일\n");
        printf("p) 이전 과일\n");
        printf("d) 현재 과일 삭제\n");
        printf("i) 현재 과일 다음에 과일 추가\n");
        printf("o) 과일 리스트 출력\n");
        printf("e) 프로그램 종료\n");
        printf("메뉴를 선택하세요: ");
        scanf_s(" %c", &option, sizeof(option));

        switch (option) {
        case 'n':  // 다음 과일
            if (current->rlink != head) {
                current = current->rlink;
                printf("다음 과일로 이동: %s\n", current->data);
            }
            else {
                printf("더 이상 다음 과일이 없습니다.\n");
            }
            break;
        case 'p':  // 이전 과일
            if (current->llink != head) {
                current = current->llink;
                printf("이전 과일로 이동: %s\n", current->data);
            }
            else {
                printf("더 이상 이전 과일이 없습니다.\n");
            }
            break;
        case 'd':  // 현재 과일 삭제
            ddelete(head, current);
            current = head->rlink;
            //printf("삭제할 과일 : %s\n");
            break;

        case 'i':  // 현재 과일 다음에 과일 추가
            printf("추가할 과일을 입력하세요: ");
            scanf_s("%s", fruit, sizeof(fruit));
            
            dinsert(head, fruit);
            current = head->rlink;
            printf("과일 추가: %s\n", fruit);
            break;

        case 'o':  // 과일 리스트 출력
            print_dlist(head, current);
            break;
        case 'e':  // 프로그램 종료
            printf("프로그램을 종료합니다.\n");
            break;
        default:
            printf("잘못된 메뉴를 선택하였습니다.\n");
        }

        // 입력 버퍼에 남아있는 개행 문자 처리
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

