// C program to delete a node from AVL Tree
#include <stdio.h>
#include <stdlib.h>

// An AVL tree node
typedef struct stu_avl_tree
{
} stu_avl;
typedef struct course_for_lecture{

}course_lecture;
typedef struct course_for_exam{

}course_exam;
typedef struct LinkedList_tag
{

    int coursename;
    int reg_students;
    stu_avl *student_root;
    struct LinkedList_tag *next;
} LinkedList;

struct Node // node of tree of slot
{
    int slot;
    LinkedList *head;
    LinkedList *tail;
    struct Node *left;
    struct Node *right;
    int height;
};
// initial avial tree according to courseid
typedef struct avl_tree
{
    int slot;
    int coursenum;
    struct avl_tree *left;
    struct avl_tree *right;
    int height_avl;
} avl_coursenum;


typedef struct class_rooms{
    int roomno;
    int numseats;
    int height;
    int seating[10][12];
    course_lecture*L;
    //pointer to classrooms assigned to it for lectures
    course_exam*E;//pointer to classrooms assigned to it for exams
    struct class_rooms*left;
    struct class_rooms*right;
}classroom;





int max(int a, int b);

// A utility function to get height of the tree
int height_coursename(avl_coursenum *N)
{
    if (N == NULL)
    {
        return 0;
    }
    return N->height_avl;
}

/*int height_stu_avl(stu_avl *N ){
if (N == NULL){
  return 0;
}
 return N->height_student;
}*/

int height(struct Node *N)
{
    if (N == NULL)
    {
        return 0;
    }
    return N->height;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

/* Helper function that allocates a new node with the given key and
 NULL left and right pointers. */
struct Node *newNode(int coursename, int slot)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->slot = slot;

    LinkedList *newLinkedList = (LinkedList *)malloc(sizeof(LinkedList));
    newLinkedList->coursename = coursename;
    newLinkedList->reg_students = 0;
    newLinkedList->student_root = NULL;
    newLinkedList->next = NULL;
    node->head = node->tail = newLinkedList;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially added at leaf
    return (node);
}

avl_coursenum *newNode_coursename(int coursenum, int slot)
{
    avl_coursenum *node = (avl_coursenum *)malloc(sizeof(avl_coursenum));
    node->coursenum = coursenum;
    node->slot = slot;
    node->left = NULL;
    node->right = NULL;
    node->height_avl = 1; // new node is initially added at leaf
    return (node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

avl_coursenum *rightRotate_coursename(avl_coursenum *y)
{
    avl_coursenum *x = y->left;
    avl_coursenum *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height_avl = max(height_coursename(y->left), height_coursename(y->right)) + 1;
    x->height_avl = max(height_coursename(x->left), height_coursename(x->right)) + 1;

    // Return new root
    return x;
}
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

avl_coursenum *leftRotate_coursename(avl_coursenum *x)
{
    avl_coursenum *y = x->right;
    avl_coursenum *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height_avl = max(height_coursename(x->left), height_coursename(x->right)) + 1;
    y->height_avl = max(height_coursename(y->left), height_coursename(y->right)) + 1;

    // Return new root
    return y;
}
// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

int getBalance_coursename(avl_coursenum *N)
{
    if (N == NULL)
        return 0;
    return height_coursename(N->left) - height_coursename(N->right);
}

avl_coursenum *insert_coursename(avl_coursenum *node, int coursename, int slot)
{
    /* 1. Perform the normal BST rotation */
    if (node == NULL)
        return (newNode_coursename(coursename, slot));

    if (coursename < node->coursenum)
        node->left = insert_coursename(node->left, coursename, slot);
    else if (coursename > node->coursenum)
        node->right = insert_coursename(node->right, coursename, slot);
    else
    {
        return node;
    }

    /* 2. Update height of this ancestor node */
    node->height_avl = 1 + max(height_coursename(node->left), height_coursename(node->right));

    /* 3. Get the balance factor of this ancestor
     node to check whether this node became
     unbalanced */
    int balance = getBalance_coursename(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && coursename < node->left->coursenum)
    {
        return rightRotate_coursename(node);
    }
    // Right Right Case
    if (balance < -1 && coursename > node->right->coursenum)
    {
        return leftRotate_coursename(node);
    }
    // Left Right Case
    if (balance > 1 && coursename > node->left->coursenum)
    {
        node->left = leftRotate_coursename(node->left);
        return rightRotate_coursename(node);
    }

    // Right Left Case
    if (balance < -1 && coursename < node->right->coursenum)
    {
        node->right = rightRotate_coursename(node->right);
        return leftRotate_coursename(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

struct Node *insert(struct Node *node, int coursename, int slot)
{

    if (node == NULL)
        return (newNode(coursename, slot)); // this case wil happen when slot of the course which we r trying to insert does not exist earlier

    if (slot < node->slot)
        node->left = insert(node->left, coursename, slot);
    else if (slot > node->slot)
        node->right = insert(node->right, coursename, slot);
    else
    { // we assume that the slot to which course is to be added already exists and is found
        if (node->head != NULL)
        {
            LinkedList *newnode = (LinkedList *)malloc(sizeof(LinkedList));
            newnode->coursename = coursename;
            newnode->reg_students = 0;
            newnode->student_root = NULL;
            newnode->next = NULL;
            if (node->tail != NULL)
            {
                node->tail->next = newnode;
                node->tail = newnode;
            }
            else
            {
                node->tail = newnode;
                node->head = newnode;
            }
        }
    }

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this ancestor
     node to check whether this node became
     unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && slot < node->left->slot)
    {
        return rightRotate(node);
    }
    // Right Right Case
    if (balance < -1 && slot > node->right->slot)
    {
        return leftRotate(node);
    }
    // Left Right Case
    if (balance > 1 && slot > node->left->slot)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && slot < node->right->slot)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}
/* Given a non-empty binary search tree, return the
node with minimum key value found in that tree.
Note that the entire tree does not need to be
searched. */
struct Node *minValueNode(struct Node *node)
{
    struct Node *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}
avl_coursenum *minValueNode_coursenum(avl_coursenum *node)
{
    avl_coursenum *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
struct Node *deleteNode(struct Node *root, int key,int min_node)
{

    if (root == NULL)
    {

        return root;
    }

    else if (key < root->slot)
    {

        root->left = deleteNode(root->left, key,min_node);
    }

    else if (key > root->slot)
    {

        root->right = deleteNode(root->right, key,min_node);
    }

    else
    {
        // if key is same as root's key, then This is
        // the node to be deleted
        printf("slot to be deleted is found %d\n", root->slot);
        if (root->head != NULL && min_node==0)
        {
            printf("cant delete this slot as some courses have already been alloted this slot\n");
            printf("%d\n", root->head->coursename);
            exit(0);
        }
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {

            struct Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
                printf("deleted slot succesfully\n");
            }
            else
            {

                *root = *temp;
            } // One child case
              // Copy the contents of
              // the non-empty child
            free(temp);
            printf("deleted slot successfully\n");
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct Node *temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            // note that height and left right pointers have not been copied deliberately
            root->head = temp->head;
            root->tail = temp->tail;
            root->slot = temp->slot;
            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->slot,1);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left),
                           height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// so as to delete course from initial avial tree of courses
// we need not take slot as argument over here as we can identify the node by coursename itself and easily delete it
avl_coursenum *delete_coursename(avl_coursenum *root, int coursename)
{
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if (coursename < root->coursenum)
        root->left = delete_coursename(root->left, coursename);

    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if (coursename > root->coursenum)
        root->right = delete_coursename(root->right, coursename);

    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {
            avl_coursenum *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            { // cant we free root directly?
                temp = root;
                root = NULL;
            }
            else               // One child case
                *root = *temp; // Copy the contents of
                               // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            avl_coursenum *temp = minValueNode_coursenum(root->right);

            // Copy the inorder successor's data to this node
            root->coursenum = temp->coursenum; // note that only key is getting copied

            // Delete the inorder successor
            root->right = delete_coursename(root->right, temp->coursenum);
        }
    }
    // If the tree had only one node then return
    if (root == NULL)
        return root;

    root->height_avl = 1 + max(height_coursename(root->left),
                               height_coursename(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance_coursename(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance_coursename(root->left) >= 0)
        return rightRotate_coursename(root);

    // Left Right Case
    if (balance > 1 && getBalance_coursename(root->left) < 0)
    {
        root->left = leftRotate_coursename(root->left);
        return rightRotate_coursename(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance_coursename(root->right) <= 0)
        return leftRotate_coursename(root);

    // Right Left Case
    if (balance < -1 && getBalance_coursename(root->right) > 0)
    {
        root->right = rightRotate_coursename(root->right);
        return leftRotate_coursename(root);
    }

    return root;
}

struct Node *delete(struct Node *root, int coursename, int slot)
{
    // If the tree had only one node then return
    if (root == NULL)
    {
        printf("the slots tree is empty\n");
        return root;
    }

    if (slot < root->slot)
    {

        root->left = delete (root->left, coursename, slot);
    }

    else if (slot > root->slot)
    {

        root->right = delete (root->right, coursename, slot);
    }

    // if key is same as root's key, then This is
    // the slot form which course has to be deleted
    else
    {
        printf("corresponding slot %dfound\n", root->slot);
        if (root->head == NULL)
        {
            printf("cant delete course as linked list is empty\n");
            exit(0);
        }
        LinkedList *ptr = root->head;
        LinkedList *prev = root->head;
        while (ptr != NULL && ptr->coursename != coursename)
        {

            ptr = ptr->next;

            printf("pointer traversal occured\n");
        }
        if (ptr == NULL)
        {
            printf("this course does not exist in %d slot\n", root->slot);
        }
        else if (ptr->student_root != NULL)
        {
            printf("cant delete this course as soe people have opted for it\n");
        }
        else if (ptr == root->head)
        { // delete at first
            printf("this is the head node getting deleted\n");

            if (root->head == root->tail)
            {
                printf("emptying the linked linest now\n");
                root->head = NULL;
                root->tail = NULL;
                free(ptr);
            }
            else
            {
                root->head = ptr->next;

                free(ptr);
            }
            printf("deleted course %d succesfully\n", coursename);
        }
        else
        {
            while (prev->next != ptr)
            {
                prev = prev->next;
            }
            prev->next = ptr->next;
            if (root->tail == ptr)
            {
                root->tail = prev;
            }
            free(ptr);
            printf("deleted course %d succesfully\n", coursename);
        }
    }

    
    return root;
}

 classroom* minValueNode(classroom* node)
{
	classroom* current = node;


	while (current->left != NULL)
		current = current->left;

	return current;
}
int getBalance(classroom*N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}
classroom *leftRotate(classroom *x)
{
	classroom *y = x->right;
	classroom *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;

	// Return new root
	return y;
}
classroom *rightRotate(classroom *y)
{
	classroom *x = y->left;
	classroom *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left), height(y->right))+1;
	x->height = max(height(x->left), height(x->right))+1;

	// Return new root
	return x;
}

classroom* new_classroom(int numseats,int RNo)
{
	classroom* node = (classroom*)
						malloc(sizeof(classroom*));
    
	node->roomno = RNo;
    node->numseats=numseats;
    node->E=NULL;
    node->L=NULL;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; // new node is initially added at leaf
	return(node);
}

classroom* insert_classroom(classroom* node, int numseats ,int RNo)
{
	//numstudents to be calculated from BPR inside main function itself
	if (node == NULL)
		return(new_classroom(numseats,RNo));//to be checked;

	if (numseats < node->numseats)
		node->left = insert_classroom(node->left, numseats,RNo);
	else if (numseats > node->numseats)
		node->right = insert_classroom(node->right, numseats,RNo);
	else // Equal keys not allowed
		return node;

	
	node->height = 1 + max(height(node->left),
						height(node->right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance(node);

	// If this node becomes unbalanced, then there are 4 cases

	// Left Left Case
	if (balance > 1 && numseats < node->left->numseats)
		return rightRotate(node);

	// Right Right Case
	if (balance < -1 && numseats > node->right->numseats)
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && numseats > node->left->numseats)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && numseats < node->right->numseats)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	
	return node;
}


classroom* delete_classroom(classroom* root, int numseats)
{
	

	if (root == NULL)
		return root;


	if ( numseats < root->numseats )
		root->left = delete_classroom(root->left, numseats);

	else if( numseats > root->numseats )
		root->right = delete_classroom(root->right, numseats);

	// if key is same as root's key, then This is
	// the node to be deleted
	else
	{
		// node with only one child or no child
		if( (root->left == NULL) || (root->right == NULL) )
		{
			classroom*temp = root->left ? root->left :
											root->right;

			// No child case
			if (temp == NULL)
			{  
				temp = root;
				root = NULL;
			}
			else // One child case
			*root = *temp; // Copy the contents of
							// the non-empty child
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder
			// successor (smallest in the right subtree)
			classroom* temp = minValueNode(root->right);

			// Copy the inorder successor's data to this node
			root->numseats = temp->numseats;
            root->roomno = temp->roomno;
         root->seating[10][12] = temp->seating[10][12]; //note that only key is getting copied
         root->L=temp->L;
         root->E=temp->E;

			// Delete the inorder successor
			root->right = delete_classroom(root->right, temp->numseats);
		}
	}
  
	// If the tree had only one node then return
	if (root == NULL)
	return root;

	
	root->height = 1 + max(height(root->left),  
						height(root->right));


	int balance = getBalance(root);

	// If this node becomes unbalanced, then there are 4 cases

	// Left Left Case
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}


// A utility function to print preorder traversal of
// the tree.
// The function also prints height of every node
void preOrder(struct Node *root)
{
    if (root != NULL)
    {
        LinkedList *tail = root->head;
        printf("%d ", root->slot);
        while (tail != NULL)
        {
            printf("%d ", tail->coursename);
            tail = tail->next;
        }
        printf("\n");
        preOrder(root->left);
        preOrder(root->right);
    }
}

void preOrder_coursename(avl_coursenum *root)
{
    if (root != NULL)
    {
        printf("%d %d\n", root->coursenum, root->slot);
        preOrder_coursename(root->left);
        preOrder_coursename(root->right);
    }
}
/* Driver program to test above function*/
// int main()
// {
// struct Node *root = NULL;
// avl_coursename *croot=NULL;
// FILE *fptr1;
// char line[100];
// int coursename,slot;
// fptr1=fopen("courseinfo.txt","r");
// printf("--------------------------------------------------------------------\n");
// printf("COURSENAME  -  SLOT\n");
// while((fgets(line,100,fptr1))!=NULL){
// sscanf(line,"%d %d",&coursename,&slot);
// printf("%d %d\n",coursename,slot);
// root=insert(root,coursename,slot);
// croot=insert_coursename(croot,coursename,slot);
// }
// fclose(fptr1);

//  printf("Preorder traversal of the constructed AVL "
//   "tree is \n");
//  preOrder(root);

// printf("Preorder traversal of the constructed AVL tree on coursenames is \n");
//  preOrder_coursename(croot);

//  root = deleteNode(root,2);
//  printf("\nPreorder traversal after deletion of 10 \n");
//  preOrder(root);

//  return 0;
// }

int main()
{
    struct Node *root = NULL;
    avl_coursenum *croot = NULL;

    root = insert(root, 8, 4);
    croot = insert_coursename(croot, 8, 4);
    root = insert(root, 6, 6);
    croot = insert_coursename(croot, 6, 6);
    root = insert(root, 4, 4);
    croot = insert_coursename(croot, 4, 4);
    root = insert(root, 7, 2);
    croot = insert_coursename(croot, 7, 2);
    root = insert(root, 2, 2);
    croot = insert_coursename(croot, 2, 2);
    root = insert(root, 3, 1);
    croot = insert_coursename(croot, 3, 1);
    root = insert(root, 1, 2);
    croot = insert_coursename(croot, 1, 2);
    root = insert(root, 5, 3);
    croot = insert_coursename(croot, 5, 3);
    root = insert(root, 9, 4);
    croot = insert_coursename(croot, 9, 4);
    root = insert(root, 10, 5);
    croot = insert_coursename(croot, 10, 5);

    printf("Preorder traversal of the constructed AVL "
           "tree is \n");
    preOrder(root);

    printf("Preorder traversal of the constructed AVL tree on coursenames is \n");
    preOrder_coursename(croot);
    root = delete (root, 2, 2);
    root = delete (root, 7, 2);
    root = delete (root, 1, 2);
    root = deleteNode(root, 2,0);//third argument stand for flag value
    printf("\nPreorder traversal after deletion of slot 2 \n");
    preOrder(root);

    return 0;
}
