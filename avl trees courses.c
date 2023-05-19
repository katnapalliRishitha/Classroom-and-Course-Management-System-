#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// An AVL tree node.....
typedef struct stu_avl_tree{
 char *name;
 char *enrollno;
 int roomnum;
 int classroom_alloted;
 int seatno;
 int benchno;
 int student_used_for_exams;
 int rowno;
 struct stu_avl_tree *left;
 struct stu_avl_tree *right;
 int height_student;
}stu_avl;


typedef struct LinkedList_tag{
int coursename;
int reg_students;
stu_avl *student_root;
struct LinkedList_tag *next;
int lecture_room;
}LinkedList;

typedef struct class_rooms{
    int roomno;
    int numseats;
    int slot_to_exams;
    int height_classroom;
    int alloted;
    //course_lecture*L;
    //pointer to classrooms assigned to it for lectures
    struct class_rooms*left;
    struct class_rooms*right;
}classroom;

typedef struct Pair_tag{
int students;
int is_alloted_perfectly;
}Pair;

typedef struct Student_tag{
int seatno;
int benchno;
int rowno;
}Student_info;

struct Node
{
 int slot;
 int num_courses_zero_reg;
 LinkedList *head;
 LinkedList *tail;
 struct Node *left;
 struct Node *right;
 int height;
};

typedef struct avl_tree{
int slot;
int coursename;
struct avl_tree *left;
struct avl_tree *right;
int height_avl;
}avl_coursename;
// A  function to get maximum of two integers

typedef struct Node_tag{
stu_avl *data;
struct Node_tag *next;
}Node;

 typedef struct Queue_tag{
 Node *head;
 Node *tail;	
 }queue;
 
 void Initialize_queue(queue *q){
 q->head=NULL;
 q->tail=NULL;	
 }
 
 Node* createNode(stu_avl *data)
 {
 	Node *newnode=(Node*)malloc(sizeof(Node));
 	newnode->data=data;
 	newnode->next=NULL;
 	return newnode;
 }
 void push(queue *q,stu_avl *data){
  Node *newnode= createNode(data);
 if(q->head==NULL){
 q->head=q->tail=newnode;	
 }
 else{
 	q->tail->next=newnode;
 	q->tail=newnode;
 }
 }
 
 void pop(queue *q){
 if(q->head!=NULL){
 Node *temp=q->head;
 q->head=q->head->next;
 free(temp);	
 }	
 }
 
 stu_avl *front(queue *q){
 stu_avl *ret_val=NULL;
 if(q->head!=NULL){
 	ret_val=q->head->data;
 }
 return ret_val;	
 }
 
 int empty(queue *q){
int ret_val=1;
if(q->head!=NULL){
	ret_val=0;
}
return ret_val;
 }
 
 

int max(int a, int b);

// A  function to get height of the tree
int height_coursename(avl_coursename *N ){
if (N == NULL){
  return 0;
}
 return N->height_avl;	
}

int height_stu_avl(stu_avl *N ){
if (N == NULL){
  return 0;
}
 return N->height_student;	
}

int height(struct Node *N)
{
 if (N == NULL){
  return 0;
}
 return N->height;
}

int height_classroom(classroom *N)
{
    if (N == NULL)
    {
        return 0;
    }
    return N->height_classroom;
}

// A  function to get maximum of two integers
int max(int a, int b)
{
 return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
 NULL left and right pointers. */
struct Node* newNode(int coursename,int slot)
{
 struct Node* node = (struct Node*)malloc(sizeof(struct Node));
 node->slot = slot;
 
   LinkedList *newLinkedList = (LinkedList *) malloc(sizeof(LinkedList));
    newLinkedList->coursename = coursename;
    newLinkedList->reg_students = 0;
    newLinkedList->lecture_room=-1;
    newLinkedList->student_root=NULL;
    newLinkedList->next = NULL;
    node->head = node->tail = newLinkedList;
    node->num_courses_zero_reg=1;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially added at leaf
    return (node);
}

avl_coursename* newNode_coursename(int coursename,int slot)
{
    avl_coursename* node = (avl_coursename*)malloc(sizeof(avl_coursename));
    node->coursename=coursename;
    node->slot = slot;
    node->left = NULL;
    node->right = NULL;
    node->height_avl= 1; // new node is initially added at leaf
    return (node);
}

stu_avl* newNode_stu_avl(char *name,char *enrollno)
{
	//printf("!!!!!!! Entered newnode function");
    stu_avl* node = (stu_avl*)malloc(sizeof(stu_avl));
    node->name=(char*)malloc(sizeof(name)+1);
    node->enrollno=(char*)malloc(sizeof(enrollno)+1);
    strcpy(node->name,name);
    strcpy(node->enrollno,enrollno);
    node->left = NULL;
    node->student_used_for_exams=0;
    node->right = NULL;
    node->height_student= 1; // new node is initially added at leaf
    return (node);
}

classroom* new_classroom(int numseats,int RNo)
{
	classroom* node = (classroom*)malloc(sizeof(classroom));
    
	node->roomno = RNo;
    node->numseats=numseats;
	node->left = NULL;
	node->slot_to_exams=-1;
	node->right = NULL;
	node->height_classroom= 1; // new node is initially added at leaf
	return(node);
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
 y->height= max(height(y->left), height(y->right))+1;
 x->height = max(height(x->left), height(x->right))+1;

 // Return new root
 return x;
}

avl_coursename *rightRotate_coursename(avl_coursename *y)
{
 avl_coursename *x = y->left;
 avl_coursename*T2 = x->right;

 // Perform rotation
 x->right = y;
 y->left = T2;

 // Update heights
 y->height_avl= max(height_coursename(y->left), height_coursename(y->right))+1;
 x->height_avl= max(height_coursename(x->left), height_coursename(x->right))+1;

 // Return new root
 return x;
}

stu_avl *rightRotate_stu_avl(stu_avl  *y)
{
	//printf("Entered right rotate\n");
 stu_avl *x = y->left;
 stu_avl*T2 = x->right;

 // Perform rotation
 x->right = y;
 y->left = T2;

 // Update heights
 y->height_student= max(height_stu_avl(y->left), height_stu_avl(y->right))+1;
 x->height_student= max(height_stu_avl(x->left), height_stu_avl(x->right))+1;

 // Return new root
 return x;
}

classroom *rightRotate_classroom(classroom *y)
{
	classroom *x = y->left;
	classroom *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height_classroom = max(height_classroom(y->left), height_classroom(y->right))+1;
	x->height_classroom = max(height_classroom(x->left), height_classroom(x->right))+1;

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
 x->height = max(height(x->left), height(x->right))+1;
 y->height = max(height(y->left), height(y->right))+1;

 // Return new root
 return y;
}


avl_coursename *leftRotate_coursename(avl_coursename *x)
{
 avl_coursename *y = x->right;
avl_coursename *T2 = y->left;

 // Perform rotation
 y->left = x;
 x->right = T2;

 // Update heights
 x->height_avl= max(height_coursename(x->left), height_coursename(x->right))+1;
 y->height_avl= max(height_coursename(y->left), height_coursename(y->right))+1;

 // Return new root
 return y;
}

stu_avl *leftRotate_stu_avl(stu_avl *x)
{
		//printf("Entered left rotate\n");
 stu_avl *y = x->right;
stu_avl *T2 = y->left;

 // Perform rotation
 y->left = x;
 x->right = T2;

 // Update heights

 x->height_student= max(height_stu_avl(x->left), height_stu_avl(x->right))+1;
  y->height_student= max(height_stu_avl(y->left), height_stu_avl(y->right))+1;


 // Return new root
 return y;
}

classroom *leftRotate_classroom(classroom *x)
{
	classroom *y = x->right;
	classroom *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height_classroom = max(height_classroom(x->left), height_classroom(x->right))+1;
	y->height_classroom = max(height_classroom(y->left), height_classroom(y->right))+1;

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


int getBalance_coursename(avl_coursename *N)
{
 if (N == NULL)
  return 0;
 return height_coursename(N->left) - height_coursename(N->right);
}



int getBalance_stu_avl(stu_avl *N)
{
 if (N == NULL)
  return 0;
 return height_stu_avl(N->left) - height_stu_avl(N->right);
}

int getBalance_classroom(classroom*N)
{
	if (N == NULL)
		return 0;
	return height_classroom(N->left) - height_classroom(N->right);
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

	
	node->height_classroom = 1 + max(height_classroom(node->left),
						height_classroom(node->right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = getBalance_classroom(node);

	// If this node becomes unbalanced, then there are 4 cases

	// Left Left Case
	if (balance > 1 && numseats < node->left->numseats)
		return rightRotate_classroom(node);

	// Right Right Case
	if (balance < -1 && numseats > node->right->numseats)
		return leftRotate_classroom(node);

	// Left Right Case
	if (balance > 1 && numseats > node->left->numseats)
	{
		node->left = leftRotate_classroom(node->left);
		return rightRotate_classroom(node);
	}

	// Right Left Case
	if (balance < -1 && numseats < node->right->numseats)
	{
		node->right = rightRotate_classroom(node->right);
		return leftRotate_classroom(node);
	}

	
	return node;
}

avl_coursename* insert_coursename(avl_coursename* node, int coursename,int slot)
{
 /* 1. Perform the normal BST rotation */
   if (node == NULL)
      return(newNode_coursename(coursename,slot));

  if (coursename < node->coursename)
      node->left = insert_coursename(node->left,coursename,slot);
 else if (coursename> node->coursename)
  node->right = insert_coursename(node->right,coursename,slot);
 else 
  {
   return node;
  }


 /* 2. Update height of this ancestor node */
 node->height_avl= 1 + max(height_coursename(node->left),height_coursename(node->right));

 /* 3. Get the balance factor of this ancestor
  node to check whether this node became
  unbalanced */
 int balance = getBalance_coursename(node);

 // If this node becomes unbalanced, then there are 4 cases

 // Left Left Case
 if (balance > 1 && coursename < node->left->coursename){
  return rightRotate_coursename(node);
}
 // Right Right Case
 if (balance < -1 && coursename > node->right->coursename){
  return leftRotate_coursename(node);
}
 // Left Right Case
 if (balance > 1 && coursename > node->left->coursename)
 {
  node->left = leftRotate_coursename(node->left);
  return rightRotate_coursename(node);
 }

 // Right Left Case
 if (balance < -1 && coursename< node->right->coursename)
 {
  node->right = rightRotate_coursename(node->right);
  return leftRotate_coursename(node);
 }

 /* return the (unchanged) node pointer */
 return node;
}


struct Node* insert(struct Node* node, int coursename,int slot)
{
 /* 1. Perform the normal BST rotation */
 if (node == NULL)
  return(newNode(coursename,slot));

 if (slot < node->slot)
  node->left = insert(node->left,coursename,slot);
 else if (slot > node->slot)
  node->right = insert(node->right,coursename,slot);
 else 
 {
 	if(node->head!=NULL){
 	 LinkedList *newnode=(LinkedList*)malloc(sizeof(LinkedList));
     newnode->coursename=coursename;
     newnode->lecture_room=-1;
     newnode->reg_students=0;
     node->num_courses_zero_reg++;
     newnode->student_root=NULL;
     newnode->next=NULL;
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
 node->height = 1 + max(height(node->left),height(node->right));

 /* 3. Get the balance factor of this ancestor
  node to check whether this node became
  unbalanced */
 int balance = getBalance(node);

 // If this node becomes unbalanced, then there are 4 cases

 // Left Left Case
 if (balance > 1 && slot < node->left->slot){
  return rightRotate(node);
}
 // Right Right Case
 if (balance < -1 && slot > node->right->slot){
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

stu_avl* Insert_stu_in_tree(stu_avl* node,char *name,char *enrollno)
{
 /* 1. Perform the normal BST rotation */
 if (node == NULL){
 	//printf("created newnode");
  return (newNode_stu_avl(name,enrollno));
}
 if (strcmp(enrollno,node->enrollno)<0){
 	 //printf("Entered leftside\n");
 	//printf("%s \n",node->enrollno);
  node->left = Insert_stu_in_tree(node->left,name,enrollno);
  //printf("Entered leftside\n");
}
 else if (strcmp(enrollno,node->enrollno)>0){
 	//printf("%s \n",node->enrollno);
 	 // printf("Entered rightside\n");
  node->right = Insert_stu_in_tree(node->right,name,enrollno);

}
 else 
 {
   return node;	
 }
 /* 2. Update height of this ancestor node */
 node->height_student= 1 + max(height_stu_avl(node->left),height_stu_avl(node->right));

 /* 3. Get the balance factor of this ancestor
  node to check whether this node became
  unbalanced */
 int balance = getBalance_stu_avl(node);

 // If this node becomes unbalanced, then there are 4 cases

 // Left Left Case
 if (balance > 1 && strcmp(enrollno,node->left->enrollno)<0){
 	//printf("LL case activated for %s\n",node->enrollno);
  return rightRotate_stu_avl(node);
}
 // Right Right Case
 if (balance < -1 && strcmp(enrollno,node->right->enrollno)>0){
 	//	printf("RR case activated for %s\n",node->enrollno);
  return leftRotate_stu_avl(node);
}
 // Left Right Case
 if (balance > 1 && strcmp(enrollno,node->left->enrollno)>0)
 {
 	//	printf("LR case activated for %s\n",node->enrollno);
  node->left = leftRotate_stu_avl(node->left);
  return rightRotate_stu_avl(node);
 }

 // Right Left Case
 if (balance < -1 && strcmp(enrollno,node->right->enrollno)<0)
 {
 	//	printf("RL case activated for %s\n",node->enrollno);
  node->right = rightRotate_stu_avl(node->right);
  return leftRotate_stu_avl(node);
 }
 
//printf("came out insert function\n");
 /* return the (unchanged) node pointer */
 return node;
}
/* Given a non-empty binary search tree, return the
node with minimum key value found in that tree.
Note that the entire tree does not need to be
searched. */
struct Node * minValueNode(struct Node* node)
{
 struct Node* current = node;

 /* loop down to find the leftmost leaf */
 while (current->left != NULL)
  current = current->left;

 return current;
}

avl_coursename *minValueNode_coursename(avl_coursename *node)
{
    avl_coursename *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}


stu_avl *minValueNode_stu_avl(stu_avl *node)
{
   stu_avl *current = node;
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}


 classroom* minValueNode_classroom(classroom* node)
{
	classroom* current = node;


	while (current->left != NULL)
		current = current->left;

	return current;
}
//so as to delete course from initial avial tree of courses
// we need not take slot as argument over here as we can identify the node by coursename itself and easily delete it
avl_coursename *delete_coursename(avl_coursename *root, int coursename)
  {
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if (coursename < root->coursename)
        root->left = delete_coursename(root->left, coursename);

// If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if (coursename > root->coursename)
        root->right = delete_coursename(root->right, coursename);

    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {
            avl_coursename *temp = root->left ? root->left : root->right;

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
            avl_coursename *temp = minValueNode_coursename(root->right);

            // Copy the inorder successor's data to this node
            root->coursename = temp->coursename; // note that only key is getting copied

            // Delete the inorder successor
            root->right = delete_coursename(root->right, temp->coursename);
        }
    }
    // If the tree had only one node then return
    if (root == NULL)
        return root;

    root->height_avl = 1 + max(height_coursename(root->left),height_coursename(root->right));

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



stu_avl *Delete_in_stu_avl_tree(stu_avl *root, char *enrollno)
  {
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if (strcmp(enrollno,root->enrollno)<0)
        root->left =Delete_in_stu_avl_tree (root->left,enrollno );

// If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if (strcmp(enrollno,root->enrollno)>0)
        root->right = Delete_in_stu_avl_tree(root->right,enrollno );

    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {
            stu_avl *temp = root->left ? root->left : root->right;

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
            stu_avl *temp = minValueNode_stu_avl(root->right);

            // Copy the inorder successor's data to this node
             *root = *temp;  // note that only key is getting copied

            // Delete the inorder successor
            root->right = Delete_in_stu_avl_tree(root->right, temp->enrollno);
        }
    }
    // If the tree had only one node then return
    if (root == NULL)
        return root;

    root->height_student = 1 + max(height_stu_avl(root->left),height_stu_avl(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance_stu_avl(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance_stu_avl(root->left) >= 0)
        return rightRotate_stu_avl(root);

    // Left Right Case
    if (balance > 1 && getBalance_stu_avl(root->left) < 0)
    {
        root->left = leftRotate_stu_avl(root->left);
        return rightRotate_stu_avl(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance_stu_avl(root->right) <= 0)
        return leftRotate_stu_avl(root);

    // Right Left Case
    if (balance < -1 && getBalance_stu_avl(root->right) > 0)
    {
        root->right = rightRotate_stu_avl(root->right);
        return leftRotate_stu_avl(root);
    }

    return root;
}


struct Node *deleteNode(struct Node *root, int key, int min_node)
{

    if (root == NULL)
    {

        return root;
    }

    else if (key < root->slot)
    {

        root->left = deleteNode(root->left, key, min_node);
    }

    else if (key > root->slot)
    {

        root->right = deleteNode(root->right, key, min_node);
    }

    else
    {
        // if key is same as root's key, then This is
        // the node to be deleted
        printf("slot to be deleted is found %d\n", root->slot);
        if (root->head != NULL && min_node == 0)
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
            root->right = deleteNode(root->right, temp->slot, 1);
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

struct Node *delete_stu(struct Node *root, int coursename, int slot)
{
    // If the tree had only one node then return
    if (root == NULL)
    {
        printf("the slots tree is empty\n");
        return root;
    }

    if (slot < root->slot)
    {

        root->left = delete_stu(root->left, coursename, slot);
    }

    else if (slot > root->slot)
    {

        root->right = delete_stu(root->right, coursename, slot);
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
			classroom* temp = minValueNode_classroom(root->right);

			// Copy the inorder successor's data to this node
			root->numseats = temp->numseats;
            root->roomno = temp->roomno;
         //root->seating[10][12] = temp->seating[10][12]; //note that only key is getting copied
         //root->L=temp->L;
         //root->E=temp->E;

			// Delete the inorder successor
			root->right = delete_classroom(root->right, temp->numseats);
		}
	}
  
	// If the tree had only one node then return
	if (root == NULL)
	return root;

	
	root->height_classroom = 1 + max(height_classroom(root->left),  
						height_classroom(root->right));


	int balance = getBalance_classroom(root);

	// If this node becomes unbalanced, then there are 4 cases

	// Left Left Case
	if (balance > 1 && getBalance_classroom(root->left) >= 0)
		return rightRotate_classroom(root);

	// Left Right Case
	if (balance > 1 && getBalance_classroom(root->left) < 0)
	{
		root->left = leftRotate_classroom(root->left);
		return rightRotate_classroom(root);
	}

	// Right Right Case
	if (balance < -1 && getBalance_classroom(root->right) <= 0)
		return leftRotate_classroom(root);

	// Right Left Case
	if (balance < -1 && getBalance_classroom(root->right) > 0)
	{
		root->right = rightRotate_classroom(root->right);
		return leftRotate_classroom(root);
	}

	return root;
}

classroom *get_classroom(classroom *root)
{
   
    classroom*ret_val;
    if(root!=NULL){

    printf("function running for roomnumber %d\n",root->roomno);
     printf("flag value is%d for room number %d\n",root->alloted,root->roomno);
    }
    if (root == NULL)
    {
        printf("!!!root is NULL !!!!\n");
        return NULL;
    }
    
    
      printf("entered here for roomnumber %d\n",root->roomno);
       

       ret_val =  get_classroom(root->right);
    if(root->roomno==2){
        //printf("right function returned now\n");
    }
       
    if(root->alloted!=0){
        printf("alloted not 0 for %d\n",root->roomno);
    }
    if (root->alloted == 1 && ret_val==NULL)
    {
        printf("entered here for root %d\n",root->roomno);
        ret_val=NULL;
        
    }
    else if(ret_val==NULL && root->alloted==0){
        if(root->roomno==2){

        //printf("returning root here\n");
        }
        root->alloted=1;
        ret_val=root;
    }
    else{
        return ret_val;//if ret_val!=NULL then no matter whatever is value for alloted it should return ret_val
    }
    // if (ret_val==NULL)
    if(root->left!=NULL && ret_val==NULL){
       ret_val= get_classroom(root->left);

    }
    

    
    return ret_val;
}
classroom *get_classroom_helper(classroom *root)
{
    if(root==NULL){
        printf("no classrooms over here\n");
    }
    else{

    //  int flag = 0;
    classroom*get_room=(classroom*)malloc(sizeof(classroom));
    get_room = NULL;
    get_room = get_classroom(root);
    return get_room;
    }
}
 void reset_classroom(classroom*rptr){
        if(rptr!=NULL){
            reset_classroom(rptr->left);
            rptr->alloted=0;
            reset_classroom(rptr->right);
        }
}

// A utility function to print preorder traversal of
// the tree.
// The function also prints height of every node


void preOrder_stu_avl(stu_avl *root)
{
  if(root==NULL){
  	return;
  }
  
 if(root != NULL)
 {
  	printf("!!!!!!!In preorder of stu_avl %s %s \n",root->name,root->enrollno);
  	printf("For exam : %d %d %d %d\n",root->roomnum,root->rowno,root->benchno,root->seatno);
  preOrder_stu_avl(root->left);
  preOrder_stu_avl(root->right);
 }
}

void InOrder_stu_avl(stu_avl *root)
{
  if(root==NULL){
  	return;
  }
  
 if(root != NULL)
 {
 	InOrder_stu_avl(root->left);
  	printf("!!!!!!!In INorder of stu_avl %s %s \n",root->name,root->enrollno);
  	printf("For exam : %d %d %d %d\n",root->seatno,root->benchno,root->rowno,root->classroom_alloted);
   InOrder_stu_avl(root->right);
 }
}
void preOrder(struct Node *root)
{
 if(root != NULL)
 {
 	LinkedList *tail=root->head;
 	 printf("!!!In slot treee  %d the num of courses where zero students are is %d\n", root->slot,root->num_courses_zero_reg);
    while(tail!=NULL){
  	printf("%d %d\n",tail->coursename,tail->reg_students);
  	InOrder_stu_avl(tail->student_root);
  	tail=tail->next;
  }
  printf("\n");
  preOrder(root->left);
  preOrder(root->right);
 }
}


void preOrder_coursename(avl_coursename *root)
{
 if(root != NULL)
 {
  	printf("%d %d\n",root->coursename,root->slot);
  preOrder_coursename(root->left);
  preOrder_coursename(root->right);
 }
}

void preOrder_classroom(classroom *root)
{
 if(root != NULL)
 {
  	printf("%d %d %d \n",root->roomno,root->numseats,root->slot_to_exams);
  preOrder_classroom(root->left);
  preOrder_classroom(root->right);
 }
}

void inorder_classroom(classroom*root){
    printf("inside print function\n");
    if(root==NULL){
        printf("its NULL\n");
    }
    if (root != NULL)
    {
    inorder_classroom(root->left);
        printf("roomno:%d numseats:%d alloted: %d\n", root->roomno, root->numseats,root->alloted);
    inorder_classroom(root->right);
    }
}





