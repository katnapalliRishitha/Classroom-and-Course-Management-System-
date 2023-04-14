#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "avl trees courses.c"
#define MAX 5
#define MIN 2
#define t 3
typedef struct Student_info
{
    char *name;
    char *enrollno;
     int courses[5];
}Student;


typedef struct BTree_Node
{
    int count;
    Student keys[MAX];
    struct BTree_Node *child[MAX + 1]; // t=3
    bool leaf;
} BTreeN;

int searchAfterCourseName(avl_coursename *croot,int coursename){
if (croot!=NULL){
    if (coursename< croot->coursename){
        return searchAfterCourseName(croot->left,coursename );
    }
    else if (coursename>croot->coursename){
        return searchAfterCourseName(croot->right,coursename  );
    }
    else{
        if (coursename==croot->coursename){
               return croot->slot;
            }

        }
      }
else{
    printf("Not found");
}
}

Student *Initialize_student(char *str1, char *str2,int coursearr[5],avl_coursename *croot)
{
	int slots[6]={0,0,0,0,0,0},i,flag=0;
    Student *newstudent = (Student *)malloc(sizeof(Student));
    newstudent->name = (char *)malloc(strlen(str1) + 1);
    strcpy(newstudent->name, str1);
    newstudent->enrollno = (char *)malloc(strlen(str2) + 1);
    strcpy(newstudent->enrollno, str2);
     for(i=0;i<5 && flag==0;i++){
     	newstudent->courses[i]=coursearr[i];
      int slot1=searchAfterCourseName(croot,coursearr[i]);
      slots[slot1-1]++;
      if(slots[slot1-1]>1){
      	flag=1;
      	newstudent=NULL;
	  }
    }
    return newstudent;
}

void traverse_student(BTreeN *root)
{
    if(root!=NULL){
    printf("entering traverse function!!!!!!!!\n");
    int i;
    //printf("%d \n", root->count);
    //printf("root value inside traverse function %s",root->keys[0].enrollno);
    //printf("new child count inside traverse: %d\n",root->count);
    for (i = 0; i < root->count; i++)
    {
    	//printf("i value:%d\n",i);
        printf("\n%s %s %d %d %d %d %d\n", root->keys[i].name, root->keys[i].enrollno, root->keys[i].courses[0], root->keys[i].courses[1], root->keys[i].courses[2], root->keys[i].courses[3], root->keys[i].courses[4]);
    } 
    //if (root->child[0] != NULL)
   // {
        //printf("shakambari\n");
        //printf("what %s\n",root->child[0]->keys[0].enrollno);
        for (i = 0; i < root->count+1; i++)
        {
            if(root->child[i]!=NULL){

            traverse_student(root->child[i]);
            }
            	//printf("\nhello\n");
            //printf("%s %s %d %d %d %d %d %d\n", root->keys[i].name, root->keys[i].enrollno, root->keys[i].courses[0], root->keys[i].courses[1], root->keys[i].courses[2], root->keys[i].courses[3], root->keys[i].courses[4], root->keys[i].courses[5]);
        }
        //if(root->child[i]!=NULL){
       //printf("rishitha\n");
        //traverse_student(root->child[i]);
        //}
    //}
}
}

BTreeN *createNode_student(bool leaf1)
{
    BTreeN *newnode = (BTreeN *)malloc(sizeof(BTreeN));
    newnode->count = 0;
    newnode->leaf = leaf1;
    int i;
    for(i=0;i<MAX+1;i++){
     newnode->child[i]=NULL;
    }
    return newnode;
}

BTreeN *splitchild_student(int i, BTreeN *y, BTreeN *newroot)
{
	printf("entered splitchild\n");
    BTreeN *z = createNode_student(y->leaf);
    z->count = t - 1;

    int j = 0;
    for (j = 0; j < t-1 ; j++)
    {
        z->keys[j] = y->keys[j + t];
    }

    if (y->leaf == false)
    {
        int j = 0;
        for (j = 0; j < t; j++)
        {
            z->child[j] = y->child[j + t];
        }
    }
    y->count = t - 1;
    //printf(" The value of count is %d", newroot->count);
   //printf("The value of newroot is %s",newroot->keys[0].enrollno);
    for (j = newroot->count; j >= i + 1; j--)
    {  //print count here
        newroot->child[j + 1] = newroot->child[j];
    }
    newroot->child[i + 1] = z;

    for (j = newroot->count - 1; j >= i; j--)
    {
      
		newroot->keys[j + 1] = newroot->keys[j];
    }
    newroot->keys[i] = y->keys[t - 1];
    newroot->count = newroot->count + 1;
    return newroot;
}

BTreeN *insertNonFull_student(Student *k, BTreeN *node)
{
    printf("Entered insertNonFull\n");
    int i = node->count - 1;
    printf("%d",i);
    if (node->leaf == true)
    {
        printf("entered inside leaf case\n");
          /*if(strcmp(node->keys[i].enrollno, k->enrollno) == 0){
         printf("exiting from program as two children cant have same enrollment number.\n");
         exit(0);
		}*/
        while (i >= 0 && strcmp(node->keys[i].enrollno, k->enrollno) > 0)
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
          //if(strcmp(node->keys[i].enrollno, k->enrollno) == 0){
         //printf("exiting from program as two children cant have same enrollment number.\n");
         //exit(0);
		//}
        node->keys[i + 1] = *k;
        node->count = node->count + 1;
        //printf("reading while inserting non full %s %d\n", node->keys[i + 1].enrollno, node->count);
    }
    else
    {
    	/*if(strcmp(node->keys[i].enrollno, k->enrollno) == 0){
         printf("exiting from program as two children cant have same enrollment number.\n");
         exit(0);
		}*/
        while (i >= 0 && strcmp(node->keys[i].enrollno, k->enrollno) >0)
        {
            i--;
        }
        //printf("%d",i);
          //if(strcmp(node->keys[i].enrollno, k->enrollno) == 0){ // here for aditya BT21CSE005 its getting i=-1 and strcmp of i=-1 is error
         //printf("exiting from program as two children cant have same enrollment number.\n");
         //exit(0);
		//}
		//printf("The child count is %d\n",node->child[i + 1]->count);
        if (node->child[i + 1]->count == 2 * t - 1)
        {
        	printf("hello\n");
        	
           node=splitchild_student(i + 1, node->child[i + 1], node);
           //printf("new child count: %d\n",node->child[i+2]->count);
           
          // printf("\n %s %s\n",node->keys[0].enrollno,node->keys[1].enrollno);
           //printf("\n %s %s\n",node->child[0]->keys[0].enrollno,node->child[0]->keys[1].enrollno);
            if (strcmp(node->keys[i+1].enrollno, k->enrollno)< 0)
            {
            	//printf("Enetered here in newroot");
                i++;
            }
        }
        //printf("Enetering to insertnonfull");
       node->child[i+1]=insertNonFull_student(k, node->child[i + 1]);
    }
  return node;
}

BTreeN *Insert_student(Student *k, BTreeN *p)
{
    BTreeN *root = p;
    if (p == NULL)
    {
        //printf("root node created\n");
        root = createNode_student(true);
        root->keys[0] = *k;
        root->count = 1;
    }
    else
    {
        if (root->count == 2 * t - 1)
        {
            int i;
            printf("keys are full\n");
            //printf("%d\n",root->count);
            /*for (i = 0; i < root->count; i++)
            {
                printf("%s %s %d %d %d %d %d\n", root->keys[i].name, root->keys[i].enrollno, root->keys[i].courses[0], root->keys[i].courses[1], root->keys[i].courses[2], root->keys[i].courses[3], root->keys[i].courses[4]);
            }*/
            BTreeN *s = createNode_student(false);
            s->child[0] = root;
            s = splitchild_student(0, root, s);
            //printf("printing after splitchild function %s\n", s->keys[0].enrollno);
            //printf("printing child 0 after splitchild function %s %s\n", s->child[0]->keys[0].enrollno, s->child[0]->keys[1].enrollno);
            //printf("printing child 1 after splitchild function %s %s\n", s->child[1]->keys[0].enrollno, s->child[1]->keys[1].enrollno);
            i = 0;
            if (strcmp(s->keys[0].enrollno, k->enrollno) < 0)
            {
                i++;

                
                s->child[i] = insertNonFull_student(k, s->child[i]);

               // printf("came out!!!");
               // printf("printing after insertnonfull function %s\n", s->keys[0].enrollno);
               // printf("printing child 0 after insertnonfull function %s %s %s\n", s->child[0]->keys[0].enrollno, s->child[0]->keys[1].enrollno, s->child[0]->keys[2].enrollno);
                //printf("printing child 1 after insertnonfull function %s %s\n", s->child[1]->keys[0].enrollno, s->child[1]->keys[1].enrollno);

                root = s;
            }
            else{
            	
            	//if(strcmp(s->keys[i].enrollno, k->enrollno) == 0){
               //printf("exiting from program as two children cant have same enrollment number.\n");
               //exit(0);
              s->child[i] = insertNonFull_student(k, s->child[i]);

                //printf("came out!!!");
               // printf("printing after insertnonfull function %s\n", s->keys[0].enrollno);
                //printf("printing child 0 after insertnonfull function %s %s %s\n", s->child[0]->keys[0].enrollno, s->child[0]->keys[1].enrollno, s->child[0]->keys[2].enrollno);
                //printf("printing child 1 after insertnonfull function %s %s\n", s->child[1]->keys[0].enrollno, s->child[1]->keys[1].enrollno);

                root = s;
            }
        }
        else
        {
           
         root=insertNonFull_student(k, root);
           
               
        }
    }
    //printf("root roll number %s\n",root->keys[0].enrollno);
    return root;
}


void borrow_from_left_student(BTreeN *current, int i, BTreeN *left, BTreeN *right, BTreeN *cur)
{
    int j;//just to check j>=0 insteda of j>=1
    for (j = cur->count - 1; j >= 1; j--)
    { // cur
        cur->keys[j + 1] = cur->keys[j];
    }
    if (!cur->leaf)
    {
        int j;
        for (j = cur->count; j >= 0; j--)
{ // cur
            cur->child[j + 1] = cur->child[j];
        }
    }
    cur->keys[0] = current->keys[i - 1]; // cur
    if (!cur->leaf)
    { // cur
        cur->child[0] = left->child[left->count];
    }
    current->keys[i - 1] = left->keys[left->count - 1];
    cur->count++; // cur
    left->count--;
}
 
// Function to borrow a key from the right sibling 
void borrow_from_right_student(BTreeN *current, int i, BTreeN *left, BTreeN *right, BTreeN *cur)
{
    cur->keys[left->count] = current->keys[i]; // cur
    if (!cur->leaf)
    {
        cur->child[left->count + 1] = right->child[0]; // cur
    }
    current->keys[i] = right->keys[0];
    int j;
    for (j = 1; j < right->count; j++)
    {
        right->keys[j - 1] = right->keys[j];
    }
    if (!right->leaf)
    {
        int j;
        for (j = 1; j <= right->count; j++)
        {
            right->child[j - 1] = right->child[j];
        }
    }
    cur->count++; // cur
    right->count--;
}
 
// Function to merge two nodes 
void merge_student(BTreeN *current, int i, BTreeN *left, BTreeN *right) { 
    left->keys[t-1] = current->keys[i]; 
    int j;
    for ( j = 0; j < right->count; j++) { 
        left->keys[t+j] = right->keys[j]; 
    } 
    if (!left->leaf) { 
    int j ;
        for ( j = 0; j <= right->count; j++) { 
            left->child[t+j] = right->child[j]; 
        } 
    } 
    for ( j = i+1; j < current->count; j++) { 
        current->keys[j-1] = current->keys[j]; 
    } 
    for (j = i+2; j <= current->count; j++) { 
        current->child[j-1] = current->child[j]; 
    } 
    left->count += right->count + 1; 
    current->count--; 
    free(right); 
}
 
// Function to fill a node that has less than t-1 keys 
void fill_student(BTreeN *current, int i)
{
    BTreeN *left = current->child[i - 1];
    BTreeN *right = current->child[i + 1];
    BTreeN *cur = current->child[i];
    if (i > 0 && left->count >= t)
    {
        borrow_from_left_student(current, i, left, right, cur);
    }
    else if (i < current->count && right->count >= t)
    {
        borrow_from_right_student(current, i, left, right, cur);
    }
    else
    {
        if (i != current->count)
        {
            merge_student(current, i, left, right);
        }
        else
        {
            merge_student(current, i - 1, left, right);
        }
    }
}
// Function to get the predecessor key of a node 
char *get_pred_student(BTreeN *current) { 
    while (!current->leaf) { 
        current = current->child[current->count]; 
    } 
    return current->keys[current->count-1].enrollno; 
} 
 
// Function to get the successor key of a node 
char * get_succ_student(BTreeN *current) { 
    while (!current->leaf) { 
        current = current->child[0]; 
    } 
    return current->keys[0].enrollno; 
}

// Function to delete a key from a node 
void delete_key_student(BTreeN *current, char * key) { 
    int i = 0; 
    while (i < current->count && strcmp( key, current->keys[i].enrollno)>0) { 
        i++; 
    } 
    if (i < current->count && strcmp( key, current->keys[i].enrollno)==0) { 
        if (current->leaf) { 
         int j;
            for ( j = i+1; j < current->count; j++) { 
                current->keys[j-1] = current->keys[j]; 
            } 
            current->count--; 
        } else { 
            BTreeN*left = current->child[i]; 
           BTreeN *right = current->child[i+1]; 
            if (left->count >= t) { 
                char * pred ;
                pred=malloc(sizeof(char)*50);
				pred= get_pred_student(left); 
                current->keys[i].enrollno= pred; 
                delete_key_student(left, pred); 
            } else if (right->count>= t) { 
               char *succ ; 
               succ=malloc(sizeof(char)*50);
			  succ=get_succ_student(right);
                current->keys[i].enrollno = succ; 
                delete_key_student(right, succ); 
            } else { 
                merge_student(current, i, left, right); 
                delete_key_student(left, key); 
            } 
        } 
    } else { 
        if (current->leaf) { 
        //printf("hii\n");
         //printf("%s!!!!!!",current->keys[0].enrollno);
            printf("Error: Key not found\n"); 
            return;
        } 
        int flag = ((i==current->count)?1:0); 
       BTreeN *child = current->child[i]; 
        if (child->count < t) { 
            fill_student(current, i); 
        } 
        if (flag && i > current->count) { 
            delete_key_student(current->child[i-1], key); 
        } else { 
            delete_key_student(current->child[i], key); 
        } 
    } 
}
 
void delete_student(BTreeN **root, char *key) { 
    if (*root == NULL) { 
        printf("Error: Key not found\n"); 
        return; 
    } 
    delete_key_student(*root, key); 
    if ((*root)->count == 0) { 
       BTreeN *tmp = *root; 
        if ((*root)->leaf) { 
            *root = NULL; 
        } else { 
            *root = (*root)->child[0]; 
        } 
        free(tmp); 
    } 
}

struct Node *searchAfterSlot(int slot,struct Node *root1)
{
if (root1!=NULL){
    if (slot< root1->slot){
        return searchAfterSlot(slot,root1->left );
    }
    else if (slot>root1->slot){
        return searchAfterSlot(slot,root1->right);
    }
    else{
        if (slot==root1->slot){
               return root1;
           }
        }
    }
else{
    printf("Not found");
}
}

struct Node *Insert_student_in_courses(struct Node *root1,Student *k,avl_coursename *croot){
int i;
int flag=0;
for(i=0;i<5;i++){
int slot=searchAfterCourseName(croot,k->courses[i]);
//printf("IN Insert_student_courses %s %d %d\n",k->name,k->courses[i],slot);
struct Node *foundslot=searchAfterSlot(slot,root1);
LinkedList *ptr=foundslot->head;
//printf("%d \n",ptr->coursename);
flag=0;
while(ptr!=NULL){
	if(ptr->coursename==k->courses[i] && flag==0){
		//printf("Entered here");
		ptr->student_root=Insert_stu_in_tree(ptr->student_root,k->name,k->enrollno);
		if(ptr->reg_students==0){
			foundslot->num_courses_zero_reg--;
		}
		ptr->reg_students++;
		//printf("successfully inserted!!!!!\n");
		//preOrder_stu_avl(ptr->student_root);
		flag=1;
	}
	ptr=ptr->next;
}
}
return root1;
}

/*struct Student* search(char *enrollno, BTreeN *root) {
    printf("Entered");
    // Find the first key greater than or equal to k
    int i = 0;
    printf("count is %d", root->count);
    while (i < root->count && strcmp(enrollno, root->keys[i].enrollno) > 0) {
    	printf("%s",root->keys[i].enrollno);
        printf("%d \n", i);
        i++;
    }
    printf("%d",i);
    printf("something");
    // If the found key is equal to k, return this node
    if (strcmp(enrollno, root->keys[i].enrollno) == 0) {
        printf("searched\n");
        return &root->keys[i];
    } else {
        printf("anything");
        // If the key is not found here and this is a leaf node
        if (root->leaf == true) {
            printf("NULL");
            return NULL;
        } else {
            printf("go");
            // Go to the appropriate child
            if (i == root->count || strcmp(enrollno, root->keys[i].enrollno) < 0) {
                // The key is not in this node, but there are more child nodes to explore
                printf("child here");
                if (root->child[i] != NULL) {
                    return search(enrollno, root->child[i]);
                }
            } else {
                // The key is greater than all the keys in this node, but there are no more child nodes to explore
                printf("NULL");
                if (root->child[i+1] != NULL) {
                    return search(enrollno, root->child[i+1]);
                }
            }
        }
    }
}*/
Student* search(char *enrollno, BTreeN *root) {
    //printf("Entered\n");
    // Find the first key greater than or equal to k
    int i = 0;
    //printf("count is %d\n", root->count);
    while (i < root->count && strcmp(enrollno, root->keys[i].enrollno) > 0) {
    	printf("%s ",root->keys[i].enrollno);
        printf("%d \n", i);
        i++;
    }
    //printf("%d\n",i);
    //printf("something\n");
    // If the found key is equal to k, return this node
    if (i < root->count && strcmp(enrollno, root->keys[i].enrollno) == 0) {
        //printf("searched\n");
        return &root->keys[i];
    } else {
        //printf("anything\n");
        // If the key is not found here and this is a leaf node
        if (root->leaf == true) {
            printf("NULL\n");
            return NULL;
        } else {
            //printf("go\n");
            // Go to the appropriate child
            if (i == root->count || strcmp(enrollno, root->keys[i].enrollno) < 0) {
                // The key is not in this node, but there are more child nodes to explore
                //printf("child here\n");
                if (root->child[i] != NULL) {
                    return search(enrollno, root->child[i]);
                }
            } else {
                // The key is greater than all the keys in this node, but there are no more child nodes to explore
                //printf("NULL\n");
                if (root->child[i+1] != NULL) {
                    return search(enrollno, root->child[i+1]);
                }
            }
        }
    }
    // If we reach here, the key was not found in the tree
    return NULL;
}

struct Node *delete_student_from_courses(avl_coursename *croot,BTreeN *root,struct Node *root1,char *key){
int i=0,flag,j;
Student *get_student=search(key,root);
printf("IN del_student_courses %s %s %d %d\n",get_student->name,get_student->enrollno,get_student->courses[0]);
for(i=0;i<5;i++){
flag=0;
int slot=searchAfterCourseName(croot,get_student->courses[i]);
struct Node *foundslot=searchAfterSlot(slot,root1);
LinkedList *ptr=foundslot->head;
while(ptr!=NULL){
	if(ptr->coursename==get_student->courses[i] && flag==0){
		printf("Entered here");
		ptr->student_root=Delete_in_stu_avl_tree(ptr->student_root,get_student->enrollno);
		ptr->reg_students--;
		//printf("successfully inserted!!!!!\n");
		//preOrder_stu_avl(ptr->student_root);
		flag=1;
	}
	ptr=ptr->next;
}
}
return root1;
}	


struct Node *delete_course_regzero(struct Node *root1){
if(root1!=NULL)
  {
	if(root1->num_courses_zero_reg!=0)
	{
		LinkedList *ptr=root1->head,*prev=NULL;
		while(ptr!=NULL)
		  {
		   if(ptr->reg_students==0){
		 	 if(prev==NULL){
		 	 	root1->head=ptr->next;
			  }
			  else{
			  	prev->next=ptr->next;
			  }
			  free(ptr);
		   }
		   else{
		   	prev=ptr;
		   }
		   ptr=ptr->next;
		}
	}
  delete_course_regzero(root1->left);
  delete_course_regzero(root1->right);	
 }
return root1;	
}

LinkedList *merge_course(LinkedList *lptr, LinkedList *nptr)
{
    LinkedList *result, *ptr1, *ptr2, *tail;
    ptr1 = lptr;
    ptr2 = nptr;
    if (ptr1->reg_students > ptr2->reg_students )
    {
        result = ptr1;
        ptr1 = ptr1->next;
    }
    else
    {
        result = ptr2;
        ptr2 = ptr2->next;
    }
    tail = result;
    while (ptr1 != NULL && ptr2 != NULL)
    {
        if (ptr1->reg_students > ptr2->reg_students)
        {
            tail = tail->next = ptr1;
            ptr1 = ptr1->next;
        }
        else
        {
            tail = tail->next = ptr2;
            ptr2 = ptr2->next;
        }
    }
    if (ptr1 != NULL)
    {
        tail->next = ptr1;
    }
    else
    {
        tail->next = ptr2;
    }
    return result;
}

LinkedList *divide_course(LinkedList *lptr)
{
   LinkedList *fast, *slow, *nptr;
    slow = lptr;
    fast = lptr->next->next;
    while (fast != NULL)
    {
        fast = fast->next;
        slow = slow->next;
        if (fast != NULL)
        {
            fast = fast->next;
        }
    }
    nptr = slow->next;
    slow->next = NULL;
    return nptr;
}

LinkedList *merge_sort_course(LinkedList *list_ptr) // sorts in descending order.
{
    LinkedList *nptr, *lptr;
    lptr = list_ptr;
    if ((lptr != NULL) && (lptr->next != NULL))
    {
        nptr = divide_course(lptr);
        lptr = merge_sort_course(lptr);
        nptr = merge_sort_course(nptr);
        lptr = merge_course(lptr, nptr);
    }
    return lptr;
}


struct Node *Sort_courses(struct Node *root1){
int i;
 if(root1 != NULL)
 {
  	//printf("!!!!!!!In preorder of stu_avl %s %s\n",root1->name,root1->enrollno);
  	LinkedList *ptr=root1->head,*tail;
  	root1->head=merge_sort_course(ptr);
  	/*tail=ptr;
  	while(tail!=NULL){
  	printf(" IN tail %d %d\n",tail->coursename,tail->reg_students);
  	tail=tail->next;
    }*/
    Sort_courses(root1->left);
     Sort_courses(root1->right);
 }
 return root1;
}
void allot_for_lectures(struct Node *node, classroom *lptr)
{
    classroom*rptr=lptr;
   printf("reached here\n");
    if (node == NULL)
        return;
     reset_classroom(rptr);
     allot_for_lectures(node->right, lptr);

    LinkedList *qptr = node->head;
    if (qptr == NULL)
    {
        printf("no courses to allot in this %d slot\n", node->slot);
       // return;
    }
    else
    {
        int available = 1;

        qptr = merge_sort_course(qptr);
        LinkedList *temp = qptr;
        node->head = qptr; // now the courses for this slot have been sorted with respect to registered sutdents
        while (qptr != NULL && available == 1)
        {
          if(qptr->student_root==NULL){
          	printf("no students\n");
			  qptr=qptr->next;	
		  }
		  else{
            classroom *cptr = get_classroom_helper(lptr);
            if (cptr == NULL)
            {
                printf("no classrooms available to allot\n");
                available = 0;
            }
            else if (cptr->numseats < qptr->reg_students)
            {
                printf("no of students in this course are more than largest free classroom hence cant allot\n");
                qptr = qptr->next;
            }
        
            else
            {
                qptr->lecture_room = cptr->roomno;
                qptr = qptr->next;
                cptr->alloted = 1;
            }
        }
        }
        if (qptr == NULL)
        {
            printf("\n");
            printf("<<<<<allotment of courses of slot %d>>>>> : \n", node->slot);
            printf("\n");
            while (temp != NULL)
            {
            	if(temp->lecture_room==-1){
            		printf("for coursenumber %d which has registered students %d has no classroom allotted\n",temp->coursename, temp->reg_students);
            		temp=temp->next;
				}
				else{
                printf("\n\ncoursenumber %d which has registered students %d alloted to roomnumber %d \n\n", temp->coursename, temp->reg_students,temp->lecture_room);
                temp = temp->next;
              }
            }
        }
    }
     reset_classroom(rptr);
    allot_for_lectures(node->left, lptr);
}



void RangeSearch(avl_coursename *croot,int courseid1,int courseid2)
{
    if(croot != NULL)
      {
    if(croot->coursename>=courseid1 && croot->coursename<=courseid2)
    {
     RangeSearch(croot->left,courseid1,courseid2);
      printf("%d ",croot->coursename);
     RangeSearch(croot->right,courseid1,courseid2);
    }
    else if(croot->coursename<courseid1)
    {
       RangeSearch(croot->right,courseid1,courseid2);
    }
    else if(croot->coursename>courseid2)
    {
      RangeSearch(croot->left,courseid1,courseid2);
    }
    }
}



void allot_students_in_tree(queue *q,classroom *root,int slot,int reg_students){
if(!empty(q)){
int i=1;
int seatno=1,benchno=1,rowno=1;
while(!empty(q) && i<=((2*root->numseats)/3)){
stu_avl *frontnode=front(q);
frontnode->seatno=seatno;
frontnode->classroom_alloted=root->roomno;
frontnode->benchno=benchno;
frontnode->rowno=rowno;
pop(q);
if(seatno%3==0 && benchno%(root->numseats/12)==0){
		benchno=1;
		rowno++;
		seatno++;
	}
	else {
		if(seatno%3==0){
		seatno++;
	   benchno++;
	   }
	   else{
	   	seatno=	seatno+2;
	   }	
i++;	
}
}
}
}



Pair allot_students_for_exams(queue *q,classroom *root,int slot,int reg_students){
Pair ret_val;
if(root==NULL){
//printf("came to null\n");
ret_val.students=reg_students;
//printf("%d",reg_students);
ret_val.is_alloted_perfectly=0;	
}
else{
	
ret_val=allot_students_for_exams(q,root->right,slot,reg_students);
//printf("Entered just here to right allot_students_for_exams\n");
//printf("checking...%d %d\n",ret_val.students,ret_val.is_alloted_perfectly);

if(ret_val.is_alloted_perfectly==0){
	//printf("just made here\n");
	if(root->slot_to_exams==-1){
			//printf("before out here in allot_students_for_exams\n");
		allot_students_in_tree(q,root,slot,reg_students);
		//printf("CLASSROOM IS %d\n",root->roomno);
		//printf("came out here in allot_students_for_exams\n");
		root->slot_to_exams=slot;// do allotment to each student
	
	if(ret_val.students<=(root->numseats)-(root->numseats/3)){
		//printf("classroom is more\n");
		ret_val.is_alloted_perfectly=1;
		reg_students=0;
		ret_val.students=0;
      }
	else{
		//printf("registered students : %d\n",reg_students);
	  reg_students=	(reg_students-(root->numseats)-(root->numseats/3));
	  ret_val.students=reg_students;
     }
 }
}
if(ret_val.is_alloted_perfectly==0 && reg_students!=0){
//printf("here\n");
  ret_val=allot_students_for_exams(q,root->left,slot,reg_students);
}
}

//printf("returned\n");
return ret_val;
}



classroom *Initialize_classroom_slot(classroom *root){
if(root!=NULL){
  Initialize_classroom_slot(root->left);
  root->slot_to_exams=-1;
  Initialize_classroom_slot(root->right);
}
return root;	
}

 void fillQueue(queue *q,stu_avl *root)
{
  if(root!=NULL){
  	fillQueue(q,root->left);
  	push(q,root);
  	fillQueue(q,root->right);
  }	
}


void allotment(struct Node *root1,classroom *classroot){
  	  	Pair ret_val;
  	  	if(root1!=NULL){
  	  			//printf("Enter into allotment\n");
  	  	  allotment(root1->left,classroot);
  	  	  LinkedList *ptr=root1->head;
  	  	  //printf("Enter into linkedlist allotment\n");
  	  	  while(ptr!=NULL){
  	  	  	// printf("%d %d \n",ptr->coursename,ptr->reg_students);
  	  	  	    queue q;
               Initialize_queue(&q);
              fillQueue(&q,ptr->student_root);
		   ret_val=allot_students_for_exams(&q,classroot,root1->slot,ptr->reg_students);
		    //printf("control here");  
           // printf("is alloted = %d,students = %d\n",ret_val.is_alloted_perfectly,ret_val.students); 
           ptr=ptr->next;
	      }
	     classroot=Initialize_classroom_slot(classroot);
		allotment(root1->right,classroot);			 	
		}		
}
	
	
int main()
  {

struct Node *root1 = NULL;
classroom *classroot=NULL;
avl_coursename *croot=NULL;
FILE *fptr1,*fptr2,*fptr3;
char line[100];
int coursename,slot;
fptr1=fopen("courseinfo.txt","r");
printf("--------------------------------------------------------------------\n");
printf("COURSENAME  -  SLOT\n");
while((fgets(line,100,fptr1))!=NULL){
sscanf(line,"%d %d",&coursename,&slot);
printf("%d %d\n",coursename,slot);
root1=insert(root1,coursename,slot);
croot=insert_coursename(croot,coursename,slot);
}
fclose(fptr1);

  printf("Preorder traversal of the constructed AVL tree is \n");
   preOrder(root1);

  printf("Preorder traversal of the constructed AVL tree on coursenames is \n");
   preOrder_coursename(croot);
	
    BTreeN *root = NULL;
    char *str1,*str2;
    int course1,course2,course3,course4,course5,coursarr[5],i=1,j,ch,course;
	fptr2=fopen("stu.txt","r");
      while((fgets(line,100,fptr2))!=NULL)
	  {
        str1 = (char*) malloc(50 * sizeof(char));
          str2 = (char*) malloc(50 * sizeof(char));
            sscanf(line,"%s %s %d %d %d %d %d",str1,str2,&course1,&course2,&course3,&course4,&course5);
            //printf("%s %s %d %d %d %d %d\n",str1,str2,course1,course2,course3,course4,course5);
             coursarr[0]=course1;
             coursarr[1]=course2; 
             coursarr[2]=course3;
             coursarr[3]=course4;
             coursarr[4]=course5;
               Student *k = Initialize_student(str1,str2,coursarr,croot);
               if(k!=NULL){
               root = Insert_student(k, root);
               root1=Insert_student_in_courses(root1,k,croot);
               //traverse_student(root);
               }
               else{
               	printf("Student has same slot courses");
               	exit(0);
			   }
               free(str1);
               free(str2);    
       }
      fclose(fptr2);
      traverse_student(root);
      preOrder(root1);
      int roomno,no_ben_row,seats;
       fptr3=fopen("classroom.txt","r");
       printf("CLASSNUMBER -  SEATS\n");
      while(fgets(line,100,fptr3)!=NULL){
        sscanf(line,"%d %d",&roomno,&no_ben_row);
            // classroom capacity(no_of_seats)  must be a multiple of 12
        seats= no_ben_row*12;
       classroot=insert_classroom(classroot,seats,roomno);
     }
     
     preOrder_classroom(classroot);
     root1=Sort_courses(root1);
     
     fclose(fptr3);
      printf("--------------------------------------------------------------------\n");
do{
	printf("\t\tMENU");
    printf("\n-------------------------------------\n");
    printf("PRESS 1.Adding a student to the student-database. ");
    printf("\nPRESS 2.Deletion of a student from the student-database.");
    printf("\nPRESS 3.Adding a course to the course database.");
    printf("\nPRESS 4.Allotment of classrooms for lectures. ");
    printf("\nPRESS 5.Allotment of classrooms for exams.");
    printf("\nPRESS 6.Print the list of students and the exam seat allotted to each student for a given slot.");
    printf("\nPRESS 7.TO EXIT.");
    printf("\n-------------------------------------\n");
    printf("Enter Your Choice: ");
    scanf("%d",&ch);
    
switch(ch){
case 1:
     {
      printf("Enter Student name : ");
      str1 = (char*) malloc(50 * sizeof(char));
      scanf("%s",str1);
      printf("Enter Students Enrollment no: ");
      str2 = (char*) malloc(50 * sizeof(char));
      scanf("%s",str2);
      printf("Enter 5 courses to register: ");
      scanf("%d %d %d %d %d",&course1,&course2,&course3,&course4,&course5);
      coursarr[0]=course1;
      coursarr[1]=course2; 
      coursarr[2]=course3;
      coursarr[3]=course4;
      coursarr[4]=course5;
      Student *k = Initialize_student(str1,str2,coursarr,croot);
       if(k!=NULL){
      root = Insert_student(k, root);
      //printf("Entered successfully");
      root1=Insert_student_in_courses(root1,k,croot);
      }
	  else{
	  	 	printf("Student has same slot courses");
	  } 
      traverse_student(root);
      preOrder(root1);
      free(str1);
      free(str2); 
      break;
    }
case 2:
	{
      char *key;
      key=malloc(sizeof(char)*50);
      printf("Enter the key to delete: "); 
      scanf("%s", key); 
      root1=delete_student_from_courses(croot,root,root1,key);
       preOrder(root1);
      delete_student(&root, key); 
      traverse_student(root);
      break;
  }
  
 case 3:{
 	    int inputslot,coursenum,choice;
 	    printf("ENTER 1 TO ADD A COURSE TO DATABASE\n");
 	     printf("ENTER 2 TO DELETE A COURSE FROM DATABASE\n");
 	     scanf("%d",&choice);
 	     if(choice==1){
     	printf("Enter course number to add in Course_list : ");
        scanf("%d",&coursenum);
     	printf("Enter the slot for given course: ");
     	scanf("%d",&inputslot);
     	root1=insert(root1,coursenum,inputslot);
        croot=insert_coursename(croot,coursenum,inputslot);
        preOrder(root1);
	    preOrder_coursename(croot);
	   }
	   else if(choice==2)
	   {
	   	 root1=delete_course_regzero(root1);
	   	 root1=deleteNode(root1,7,0);
	   	 preOrder(root1);
	   } 
   	break;
 }
 
 case 4:
 	{ 
 	
 	  // root1=Sort_courses(root1);
 	  
 	    allot_for_lectures(root1,classroot);
 	
 	 break;	
	 }
	 
 case 5:
  {
  	    
  	   allotment(root1,classroot);
	  //preOrder_classroom(classroot);
	   preOrder(root1);
	  break;
  }
  
 case 7:{
 	  int courseid1,courseid2;
 	 printf("Enter courseid 1 to search:");
 	 scanf("%d",&courseid1);
 	  printf("Enter courseid 2 to search:");
 	 scanf("%d",&courseid2);
 	RangeSearch(croot,courseid1,courseid2);
    break;  
  }
  
}
} while(ch>=1 && ch<=7);
}
