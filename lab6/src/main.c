#include <stdio.h>
#include <malloc.h>

struct tree_vertex{
    int value;
    int height;
    struct tree_vertex *left;
    struct tree_vertex *right;
};

struct tree_vertex *createVertex(int value){
    struct tree_vertex *new_vertex = (struct tree_vertex*)malloc(sizeof(struct tree_vertex));
    new_vertex->value = value;
    new_vertex->height = 1;
    new_vertex->left = NULL;
    new_vertex->right = NULL;
    return new_vertex;
}

void calcHeight(struct tree_vertex *tree){
    if (tree->left == NULL && tree->right == NULL) tree->height = 0;
    else if (tree->left == NULL) tree->height = tree->right->height;
    else if (tree->right == NULL) tree->height = tree->left->height;
    else if (tree->left->height < tree->right->height) tree->height = tree->right->height;
    else tree->height = tree->left->height;
    tree->height++;
}

int avlTreeBalance(struct tree_vertex *tree){
    if (tree->left == NULL && tree->right == NULL) return 0;
    if (tree->left == NULL) return -tree->right->height;
    if (tree->right == NULL) return tree->left->height;
    return tree->left->height - tree->right->height;
}

struct tree_vertex *rotateTreeRight(struct tree_vertex *tree){
    struct tree_vertex *tmp;
    tmp = tree->left;
    tree->left = tmp->right;
    tmp->right = tree;
    calcHeight(tree);
    calcHeight(tmp);
    return tmp;
}

struct tree_vertex *rotateTreeLeft(struct tree_vertex *tree){
    struct tree_vertex *tmp;
    tmp = tree->right;
    tree->right = tmp->left;
    tmp->left = tree;
    calcHeight(tree);
    calcHeight(tmp);
    return tmp;
}

struct tree_vertex *avlTreeAdd(struct tree_vertex *tree, int value){
    if (tree == NULL){
        tree = createVertex(value);
        return tree;
    }
    if (value < tree->value) tree->left = avlTreeAdd(tree->left, value);
    else tree->right = avlTreeAdd(tree->right, value);
    calcHeight(tree);
    if (avlTreeBalance(tree) == 2){
        if (avlTreeBalance(tree->left) < 0) tree->left = rotateTreeLeft(tree->left);
        tree = rotateTreeRight(tree);
    }
    else if (avlTreeBalance(tree) == -2){
        if (avlTreeBalance(tree->right) > 0) tree->right = rotateTreeRight(tree->right);
        tree = rotateTreeLeft(tree);
    }
    return tree;
}

void avlTreeFree(struct tree_vertex *tree){
    if (tree != NULL){
        avlTreeFree(tree->left);
        avlTreeFree(tree->right);
        free(tree);
    }
}

int main(void) {
    int num_of_vertexes, value;
    struct tree_vertex *tree = NULL;
    if (scanf("%d", &num_of_vertexes) != 1) return 1;
    for (int i = 0; i < num_of_vertexes; i++){
        if (scanf("%d", &value) != 1) return 1;
        tree = avlTreeAdd(tree, value);
    }
    if (num_of_vertexes == 0) printf("0");
    else printf("%d", tree->height);
    avlTreeFree(tree);
    return 0;
}
