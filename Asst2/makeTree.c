//#include "makeTree.h"

makeTree * Tree(CharCounts * counts){

        makeTree * root;
        TreeQueue * queue;
        TreeQueue * toAdd;
        makeTree * temp;
        makeTree * temp2;
        CharCounts * tempCount;

        root = NULL;
        queue = NULL;
        toAdd = NULL;
        temp = NULL;
        temp2 = NULL;
        tempCount = NULL;

        tempCount = counts;
        while(tempCount != NULL){
                toAdd = createBranch(tempCount);
                tempCount = tempCount->next;
                queue = insertInQueue(queue,toAdd);
        }
        toAdd = NULL;

        while(isEmpty(queue)==0){
                if(toADD != NULL){
                        queue = insertInQueue(queue,toAdd);
                }
        temp1 = queue->root;
       queue = queue->next;
        temp2 = queue->root;
        queue = queue->next;
        temp2 = insertInTree(temp2,temp1);
        toAdd = createBranchFromTree(temp2);
        }
        root = toAdd->root;
        return(root);
}
int treeNodeCount(makeTree * root){
        makeTree * temp;
        int nodeCount;

        temp = root;
        nodeCount = 0;

        if(temp == NULL){
                return (nodeCount);
        }
        else {
                return(nodeCount + 1 + treeNodeCount(root->lChild) + treeNodeCount(root->rChild);
        }
}
makeTree * insertInTree(makeTree * root, makeTree * toAdd){
        int nodeCount;
        makeTree * newRoot;

        nodeCount = treeNodeCount(root);
        newRoot = malloc(sizeof(makeTree));
        if(newRoot == NULL){
                        printf("error\n");
                exit(0);
        }
        newRoot->letter = '\0';
        newRoot->count = root->count + toAdd->count;

        if(nodeCount == 0){
                free(newRoot);
                return(toAdd);
        }else {
                newRoot->lChild = toAdd;
                newRoot->rChild = root;

                return (newRoot);
        }
}
void printTree(makeTree * root){
        if(root != NULL){
                printf("ROOT\n");
                printf("%c %d\n",root->letter,root->count);
                printf("LeftChild\n");
                printTree(root->lChild);
                printf("\n");
                printf("RightChild\n");
                printTree(root->rChild);
                printf("/n");
        }
}
makeTree * freeTree(makeTree * tree){
        if(tree !=NULL){
                if(tree->lChild !=NULL){
                        tree->lChild = freeTree(tree->lChild);
                }
                if(tree->rChild !=NULL){
                        tree->rChild = freeTree(tree->rchild);
                }
                free(tree);
        }
        return(NULL);
}
makeTree * createBranch(CharCounts * count){
        TreeQueue * branch;
        branch = malloc(sizeof(TreeQueue));
        if(branch == NULL){
                printf("error\n");
                exit(0);
        }
        branch->root = malloc(sizeof(makeTree));
        if(banch->root == NULL){
                printf("error\n");
                exit(0);
        }
        branch->root->letter = count->letter;
        branch->root->count = count->count;
        branch->root->lChild = NULL;
        branch->root->rChild = NULL;
        branch->next = NULL;

        return(branch);
}
TreeQueue * createBranchFromTree(makeTree * root){
        TreeQueue * branch;
        branch = malloc(sizeof(TreeQueue));
        if(branch == NULL){
                printf("error\n");
                exit(0);
        }
        branch->root = root;
        branch->next = NULL;

        return (branch);
}
TreeQueue * insertInQueue(TreeQueue * root,TreeQueue * toAdd){
        TreeQueue * temp;
        temp = root;

        while(temp != NULL && temp->next !=NULL && temp->root->count< toAdd->root->count){
                temp = temp->next;
        }
        if(root == NULL){
                toAdd->next = NULL;
                return(toAdd);
        }
        else if(temp->next == NULL){
                temp->next = toAdd;
                toAdd->next = NULL;
                return(root);
        }else {
                toAdd->next = temp->next;
                temp->next = toAdd;
                return(root);
        }
}
int isEmpty(TreeQueue * root){
        if(root == NULL){
                return (1);
        }
        else {
                return (0);
        }
}


