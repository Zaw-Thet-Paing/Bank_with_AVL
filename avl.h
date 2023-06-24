#include<stdio.h>
#include<stdlib.h>
#include "z_library.h"

struct History{
    char note[100];
};

struct Data{
    int id;
    char name[50];
    char phone[15];
    char email[50];
    char password[50];
    char nrc[25];
    char address[50];
    char account_type[10];
    unsigned int monthly_income;
    unsigned int loan_amount;
    unsigned int cur_amount;
    unsigned int wallet_capacity;
    unsigned int amount_limit_per_day;
    struct History hist[100];
};

struct Node{
    struct Data data;
    struct Node* left;
    struct Node* right;
    int height;
};

typedef struct Node Node;
typedef struct Data Data;

Node* root = NULL;
int space_array[100];

//avl functions
int getHeight(Node* node);
int getBalanceFactor(Node* node);
void updateHeight(Node* node);
Node* rotateLeft(Node* x);
Node* rotateRight(Node* y);
Node* insertNode(Node* node, Data data);
void printInOrder(Node* node);
int count_node(Node* node);

int getHeight(Node* node)
{
    if(node == NULL){
        return 0;
    }
    return node->height;
}

int getBalanceFactor(Node* node)
{
    if(node == NULL){
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(struct Node* node)
{
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

Node* rotateLeft(Node* x)
{
    Node* y = x->right;
    Node* tmp = y->left;

    y->left = x;
    x->right = tmp;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* rotateRight(Node* y)
{
    Node* x = y->left;
    Node* tmp = x->right;

    x->right = y;
    y->left = tmp;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* insertNode(Node* node, Data data)
{
    if(node == NULL){
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if(node->data.id > data.id){
        node->left = insertNode(node->left, data);
    }else if(node->data.id < data.id){
        node->right = insertNode(node->right, data);
    }else{
        return node;
    }

    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);

    //left left case
    if(balanceFactor > 1 && node->left->data.id > data.id){
        return rotateRight(node);
    }

    //left right case
    if(balanceFactor > 1 && node->left->data.id < data.id){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    //right right case
    if(balanceFactor < -1 && node->right->data.id < data.id){
        return rotateLeft(node);
    }

    //right left case
    if(balanceFactor < -1 && node->right->data.id > data.id){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;

}

void printInOrder(Node* node)
{
    if(node != NULL){
        printInOrder(node->left);

        printf("%d %s %s %s %s %s %s %s %u %u %u %u %u", node->data.id, node->data.name, node->data.phone, node->data.email, node->data.password, node->data.nrc, node->data.address, node->data.account_type, node->data.monthly_income, node->data.loan_amount, node->data.cur_amount, node->data.wallet_capacity, node->data.amount_limit_per_day);
        
        for(int i = 0; i<(space_array[node->data.id - 1001] - 12); i++){
            printf(" %s", node->data.hist[i].note);
        }
        // for(int i = 0; i<2; i++){
        //     printf(" %s", node->data.hist[i].note);
        // }
        printf("%c", '\n');

        printInOrder(node->right);
    }
}

int count_node(Node* node)
{
    if(node == NULL){
        return 0;
    }else{
        int leftCount = count_node(node->left);
        int rightCount = count_node(node->right);
        return leftCount +  rightCount + 1;
    }
}