#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 50
#define  num_students 12
#define num_assignments 3
#define num_groups 2
//1st
// Define struct for student record
typedef struct student_record {
    int student_id;
    char name[50];
    int group_partner_id;
    int group_id;
    int assignment_id;
    char assignment_name[50];
    char deadline[20];
    char status[20];
    int offline_marks;
    int viva_marks;
    struct student_record* next;
} student_record;

// Define struct for assignment record
typedef struct assignment_record {
    int assignment_id;
    char topic_name[50];
    char status[20];
    struct student_group_record* grp_head;
    struct student_group_record* grp_tail;
    struct assignment_record* next;
} assignment_record;

// Define struct for student group record
typedef struct student_group_record {
    int group_id;
    int student1_id;
    int student2_id;
    char status[20];
    int marks_given_student1;
    int marks_given_student2;
    struct student_group_record* next;
} student_group_record;

struct student_record *createsr(struct student_record *head)
{
    student_record* tail=head;
    FILE *fp1 = fopen("student_record_char.txt", "r");
    if (fp1 == NULL) {
        printf("Error opening file.\n");
        return head;
    }
    int i;
    for(i=0; i<num_students; i++)
    {
        struct student_record *sr = (student_record*)malloc(sizeof(struct student_record));
        fgets(sr->name, size, fp1);
        fgets(sr->assignment_name, size, fp1);
        fgets(sr->deadline, size, fp1);
        fgets(sr->status, size, fp1);
        sr->next = NULL;
        if (head == NULL)
        {
            head = tail = sr;
        }
        else
        {
            tail->next=sr;
            tail=sr;
        }
    }
    fclose(fp1);
    
    FILE *fp2 = fopen("student_record_num.txt", "r");
    if (fp2 == NULL)
    {
        printf("Error opening file.\n");
    }
    struct student_record *sr = head;
    while(sr != NULL)
    {
        fscanf(fp2, "%d", &sr->student_id);
        fscanf(fp2, "%d", &sr->group_partner_id);
        fscanf(fp2, "%d", &sr->group_id);
        fscanf(fp2, "%d", &sr->assignment_id);
        fscanf(fp2, "%d", &sr->offline_marks);
        fscanf(fp2, "%d", &sr->viva_marks);
        sr = sr->next;
    }
    fclose(fp2);
    return head;
    
}

struct assignment_record *createar(struct assignment_record *head)
{
    assignment_record* tail=head;
    FILE *fp1 = fopen("assignment_record_char.txt", "r");
    FILE *fp3 = fopen("student_group_record_char.txt", "r");
    FILE *fp4 = fopen("student_group_record_num.txt", "r");
    if (fp1 == NULL) {
        printf("Error opening file.\n");
        return head;
    }
    int i;
    for( i=0; i<num_assignments; i++)
    {
        struct assignment_record *ar = (assignment_record*)malloc(sizeof(struct assignment_record));
        fgets(ar->topic_name, size, fp1);
        fgets(ar->status, size, fp1);
        ar->grp_head=ar->grp_tail=NULL;
        int j;
        for(j=0; j<num_groups; j++)
        {
            struct student_group_record *sgr = (student_group_record*)malloc(sizeof(struct student_group_record));
            fgets(sgr->status, size, fp3);
            sgr->next = NULL;
            if (ar->grp_head == NULL)
            {
                ar->grp_head = ar->grp_tail = sgr;
            }
            else
            {
                ar->grp_tail->next=sgr;
                ar->grp_tail=sgr;
            }
            //struct student_record *temp_sgr = sgr_head;
            //while(temp_sgr != NULL)
            //{
                fscanf(fp4, "%d", &sgr->group_id);
                fscanf(fp4, "%d", &sgr->student1_id);
                fscanf(fp4, "%d", &sgr->student2_id);
                fscanf(fp4, "%d", &sgr->marks_given_student1);
                fscanf(fp4, "%d", &sgr->marks_given_student2);
            
                //sgr = sgr->next;
            //}
        }
        ar->next = NULL;
        if (head == NULL)
        {
            head = tail = ar;
        }
        else
        {
            tail->next=ar;
            tail=ar;
        }
        
    }
    fclose(fp1);
    fclose(fp3);
    fclose(fp4);
    FILE *fp2 = fopen("assignment_record_num.txt", "r");
    if (fp2 == NULL)
    {
        printf("Error opening file.\n");
    }
    struct assignment_record *ar = head;
    while(ar != NULL)
    {
        fscanf(fp2, "%d", &ar->assignment_id);
        ar = ar->next;
    }
    fclose(fp2);
    return head;
    
}

void print_student_record(struct student_record *head)
{
    struct student_record *current = head;

    while (current != NULL)
    {
        printf("Student ID: %d\n", current->student_id);
        printf("Name: %s", current->name);
        printf("Group Partner ID: %d\n", current->group_partner_id);
        printf("Group ID: %d\n", current->group_id);
        printf("Assignment ID: %d\n", current->assignment_id);
        printf("Assignment Name: %s", current->assignment_name);
        printf("Deadline: %s", current->deadline);
        printf("Status: %s", current->status);
        printf("Offline Marks: %d\n", current->offline_marks);
        printf("Viva Marks: %d\n", current->viva_marks);
        printf("--------------------------------------\n");
        current = current->next;
    }
}

void print_assignment_record(assignment_record *head)
{
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct assignment_record *ar = head;
    struct student_group_record *sgr = ar->grp_head;
    while (ar != NULL) {
        printf("Assignment topic: %s", ar->topic_name);
        printf("Assignment status: %s", ar->status);
        sgr=ar->grp_head;
        //struct student_group_record *sgr = ar->grp_head;
        while (sgr != NULL) {

            printf("Group status: %s", sgr->status);
            printf("Group ID: %d\n", sgr->group_id);
            printf("Student 1 ID: %d\n", sgr->student1_id);
            printf("Student 2 ID: %d\n", sgr->student2_id);
            printf("Marks for Student 1: %d\n", sgr->marks_given_student1);
            printf("Marks for Student 2: %d\n", sgr->marks_given_student2);
            sgr = sgr->next;
        }

        printf("Assignment ID: %d\n", ar->assignment_id);
        printf("--------------------------------------\n");

        ar = ar->next;
       
    }
}






student_record* insert_student_record(student_record* head)                                                            //1st
{
    student_record *tail,*new_student=NULL;
    if(head==NULL)
    {
        head = new_student = (student_record*)malloc(sizeof(student_record));
    }
    else
    {
        tail = head;
        while(tail->next!=NULL)
        {
            tail=tail->next;
        }
        tail->next=new_student=(student_record*)malloc(sizeof(student_record));
    }
    printf("Enter student id: ");
    scanf("%d", &new_student->student_id);
    printf("Enter student name: ");
    scanf("%s", new_student->name);
    printf("Enter group partner id: ");
    scanf("%d", &new_student->group_partner_id);
    printf("Enter group id: ");
    scanf("%d", &new_student->group_id);
    printf("Enter assignment id: ");
    scanf("%d", &new_student->assignment_id);
    printf("Enter assignment name: ");
    scanf("%s", new_student->assignment_name);
    printf("Enter deadline: ");
    scanf("%s", new_student->deadline);
    printf("Enter status of assignment(submitted/not-submitted/evaluated): ");
    scanf("%s", new_student->status);
    printf("Enter offline marks: ");
    scanf("%d", &new_student->offline_marks);
    printf("Enter viva marks: ");
    scanf("%d", &new_student->viva_marks);
    new_student->next=NULL;
    return head;
}

assignment_record* update_assignment_record(student_record* sr_head,assignment_record* ar_head)
{
    student_record* current_student = sr_head;
    assignment_record* current_assignment = ar_head;
    student_group_record *current_group=NULL;
    //int updated=0;
    int grp_exists=0;
    int assignment_exists=0;
    while(current_student->next!=NULL)
    {
        current_student=current_student->next;
    }
        assignment_record* prev_assignment=NULL;
        while(current_assignment!=NULL&&assignment_exists==0&&grp_exists==0)
        {
            //while(assignment_exists==0&&grp_exists==0)
            //{
                current_group=current_assignment->grp_head;
                if(current_student->assignment_id==current_assignment->assignment_id)
                {
                    assignment_exists=1;
                    student_group_record *prev_group = NULL;
                    while(current_group!=NULL)
                    {
                        printf("Srihitha");
                        //assignment_exists=1;
                        if(current_student->group_id==current_group->group_id)
                        {
                            current_group->student2_id=current_student->student_id;
                            current_group->marks_given_student2=(current_student->offline_marks)+(current_student->viva_marks);
                            grp_exists=1;
                        }
                        else
                        {
                            prev_group=current_group;
                            current_group=current_group->next;
                        }
                    }
                    
                    if(grp_exists==0)
                    {
                        printf("Sruthi");
                        current_group=(student_group_record*)malloc(sizeof(student_group_record));
                        current_group->next=NULL;
                        current_group->student1_id=current_student->student_id;
                        current_group->student2_id=current_student->group_partner_id;
                        current_group->group_id=current_student->group_id;
                        printf("%d", current_group->group_id);
                        current_group->marks_given_student1=(current_student->offline_marks)+(current_student->viva_marks);
                        strcpy(current_group->status,current_student->status);
                        grp_exists=1;
                        prev_group->next=current_group;
                    }
                }
                else
                {
                    prev_assignment=current_assignment;
                    current_assignment=current_assignment->next;
                }
            //}
        }
        if(assignment_exists==0)
        {
            current_assignment=(assignment_record*)malloc(sizeof(assignment_record));
            current_assignment->next=NULL;
            current_assignment->assignment_id=current_student->assignment_id;
            strcpy(current_assignment->topic_name,current_student->assignment_name);
            strcpy(current_assignment->status,current_student->status);
            current_group=current_assignment->grp_head=(student_group_record*)malloc(sizeof(student_group_record));
            current_group->next=NULL;
            current_group->student1_id=current_student->student_id;
            current_group->student2_id=current_student->group_partner_id;
            current_group->marks_given_student1=(current_student->offline_marks)+(current_student->viva_marks);
            current_group->marks_given_student2=0;
            current_group->group_id=current_student->group_id;
            strcpy(current_group->status,current_student->status);
            grp_exists=1;
            assignment_exists=1;
            prev_assignment->next=current_assignment;
        }
       
    
    return ar_head;
}









assignment_record* insert_assignment_record(assignment_record* head)                                                   //2nd
{
    assignment_record *tail,*new_assignment=NULL;
    if(head==NULL)
    {
        head = new_assignment = (assignment_record*)malloc(sizeof(assignment_record));
    }
    
    else
    {
        tail = head;
        while(tail->next!=NULL)
        {
            tail=tail->next;
        }
        tail->next=new_assignment=(assignment_record*)malloc(sizeof(assignment_record));
    }
    printf("Enter assignment id: ");
    scanf("%d", &new_assignment->assignment_id);
    printf("Enter topic name: ");
    scanf("%s", new_assignment->topic_name);
    printf("Enter status of assignment(submitted/not-submitted/evaluated): ");
    scanf("%s", new_assignment->status);
    new_assignment->grp_head=new_assignment->grp_tail=NULL;
    int groups;
    printf("Enter the number of groups we are allocating the assignment : ");
    scanf("%d", &groups);
    int i;
    for( i=0; i<groups; i++)
    {
        student_group_record *new_group=NULL;
        new_group = (student_group_record*)malloc(sizeof(student_group_record));
        printf("Enter group id: ");
        scanf("%d", &new_group->group_id);
        printf("Enter first student id: ");
        scanf("%d", &new_group->student1_id);
        printf("Enter second student id: ");
        scanf("%d", &new_group->student2_id);
        printf("Enter status of group(submitted/not-submitted/evaluated): ");
        scanf("%s", new_group->status);
        printf("Enter marks given to student 1: ");
        scanf("%d", &new_group->marks_given_student1);
        printf("Enter marks given to student 2: ");
        scanf("%d", &new_group->marks_given_student2);
        new_group->next=NULL;
        if(new_assignment->grp_head==NULL)
        {
            new_assignment->grp_head=new_assignment->grp_tail=new_group;
        }
        else
        {
            new_assignment->grp_tail->next=new_group;
            new_assignment->grp_tail=new_group;
        }
    }
    new_assignment->next=NULL;
    return head;
}

student_record* update_student_record(student_record* sr_head,assignment_record* ar_head)
{
    student_record* current_student = sr_head;
    assignment_record* current_assignment = ar_head;
    student_group_record* current_group = NULL;
    student_record* new_student = NULL;
    
    while(current_student->next != NULL)
    {
        current_student = current_student->next;
    }
    while(current_assignment->next != NULL)
    {
        current_assignment = current_assignment->next;
    }
    current_group = current_assignment->grp_head;
    
    while(current_group != NULL)
    {
        // Create a new node for the next student
        new_student = (student_record*)malloc(sizeof(student_record));
        if (new_student == NULL) {
            // Handle memory allocation error
            return sr_head;
        }
        
        // Update the student record with the group details
        new_student->student_id = current_group->student1_id;
        new_student->group_partner_id = current_group->student2_id;
        new_student->assignment_id = current_assignment->assignment_id;
        strcpy(new_student->assignment_name, current_assignment->topic_name);
        strcpy(new_student->status, current_group->status);
        new_student->offline_marks = current_group->marks_given_student1 / 2;
        new_student->viva_marks = current_group->marks_given_student1 / 2;
        new_student->next = NULL;
        
        // Add the new student to the end of the list
        current_student->next = new_student;
        current_student = new_student;
        
        // Create a new node for the next student
        new_student = (student_record*)malloc(sizeof(student_record));
        if (new_student == NULL) {
            // Handle memory allocation error
            return sr_head;
        }
        
        // Update the student record with the group details
        new_student->student_id = current_group->student2_id;
        new_student->group_partner_id = current_group->student1_id;
        new_student->assignment_id = current_assignment->assignment_id;
        strcpy(new_student->assignment_name, current_assignment->topic_name);
        strcpy(new_student->status, current_group->status);
        new_student->offline_marks = current_group->marks_given_student2 / 2;
        new_student->viva_marks = current_group->marks_given_student2 / 2;
        new_student->next = NULL;
        
        // Add the new student to the end of the list
        current_student->next = new_student;
        current_student = new_student;
        
        current_group = current_group->next;
    }
  
    return sr_head;
}

void print_updated_student_record(student_record* head)
{
    struct student_record *current = head;

    while (current != NULL)
    {
        printf("Student ID: %d\n", current->student_id);
        printf("Group Partner ID: %d\n", current->group_partner_id);
        printf("Group ID: %d\n", current->group_id);
        printf("Assignment ID: %d\n", current->assignment_id);
        printf("Assignment Name: %s\n", current->assignment_name);
        printf("Status: %s\n", current->status);
        printf("Offline Marks: %d\n", current->offline_marks);
        printf("Viva Marks: %d\n", current->viva_marks);
        printf("--------------------------------------\n");
        current = current->next;
    }
}






void change_status_of_assignment(assignment_record* ar_head)                                                         //??3rd
{
    assignment_record* current_assignment = ar_head;
    
    int i;
    for ( i = 1; i <= num_assignments; i++)
    {
        student_group_record* current_group=current_assignment->grp_head;
        printf("%s%s", current_group->status, current_group->next->status);
        if(strcmp((current_group->status),((current_group->next)->status))==0)
        {
            printf("Status of the assignment%d is changed to %s", i, current_group->status);
        }
        else if((strcmp(current_group->status,"submitted\n")==0&&strcmp(current_group->next->status,"evaluated\n")==0)||(strcmp(current_group->status,"evaluated\n")==0&&strcmp(current_group->next->status,"submitted\n")==0))
        {
            printf("Status of the assignment%d is changed to %s\n", i, "submitted");
        }
        else if((strcmp(current_group->status,"submitted\n")==0&&strcmp(current_group->next->status,"not-submitted\n")==0)||(strcmp(current_group->status,"not-submitted\n")==0&&strcmp(current_group->next->status,"submitted\n")==0))
        {
            printf("Status of the assignment%d is changed to %s\n", i, "not-submitted");
        }
        else if((strcmp(current_group->status,"not-submitted\n")==0&&strcmp(current_group->next->status,"evaluated\n")==0)||(strcmp(current_group->status,"evaluated\n")==0&&strcmp(current_group->next->status,"not-submitted\n")==0))
        {
            printf("Status of the assignment%d is changed to %s\n", i, "not-submitted");
        }
        else
        {
            printf("Nothing\n");
        }
        current_assignment=current_assignment->next;
    }
}







void assignment_declared_or_evaluated(assignment_record* ar_head)                                                     //??4th
{
    assignment_record* current_assignment = ar_head;

    int i;
    for (i = 1; i <= num_assignments; i++)
    {
        student_group_record* current_group=current_assignment->grp_head;
        printf("%s%s", current_group->status, current_group->next->status);
        if((strcmp(current_group->status,"evaluated\n")==0&&strcmp(current_group->next->status,"evaluated\n")==0))
        {
            printf("Assignment%d is evaluated\n", i);
        }
        else
        {
            printf("Assignment%d is declared\n", i);
        }
        current_assignment=current_assignment->next;
    }
}






void print_yet_to_be_evaluated(student_record* sr_head)                                                         //6th
{
    student_record* current_student=sr_head;
    while(current_student!=NULL)
    {
        if(strcmp(current_student->status, "evaluated\n")!=0)
        {
            
            if(strcmp(current_student->status, "submitted\n")!=0)
            {
                printf("Student with student_id%d from student_group%d is yet to be evaluated\n", current_student->student_id, current_student->group_id);
                if(current_student->viva_marks==0)
                {
                    printf("Viva is to be taken for student with student_id%d from student_group%d\n\n", current_student->student_id, current_student->group_id);
                }
            }
        }
        current_student=current_student->next;
    }
}





typedef struct marks_record                                                                                     //7th
{
    int group_id;
    int student1_id;
    int student2_id;
    int marks;
    struct marks_record* next;
} marks_record;

void print_marks_in_sorted_order(assignment_record* ar_head)
{
    assignment_record* current_assignment = ar_head;
    
    while (current_assignment != NULL)
    {
        student_group_record* current_group = current_assignment->grp_head;
        marks_record* marks_head = NULL;
        marks_record* temp = NULL;
        
        while (current_group != NULL)
        {
            int total_marks = current_group->marks_given_student1 + current_group->marks_given_student2;
            
            // create new marks record
            marks_record* new_marks = (marks_record*) malloc(sizeof(marks_record));
            new_marks->group_id = current_group->group_id;
            new_marks->student1_id = current_group->student1_id;
            new_marks->student2_id = current_group->student2_id;
            new_marks->marks = total_marks;
            new_marks->next = NULL;
            
            // insert marks record into linked list
            if (marks_head == NULL) {
                marks_head = new_marks;
            } else {
                if (new_marks->marks >= marks_head->marks) {
                    new_marks->next = marks_head;
                    marks_head = new_marks;
                } else {
                    temp = marks_head;
                    while (temp->next != NULL && new_marks->marks < temp->next->marks) {
                        temp = temp->next;
                    }
                    new_marks->next = temp->next;
                    temp->next = new_marks;
                }
            }
            
            current_group = current_group->next;
        }
        
        printf("Details of student-groups for Assignment %d:\n", current_assignment->assignment_id);
        temp = marks_head;
        while (temp != NULL) {
            printf("Group %d, Total marks: %d, Students: %d and %d\n", temp->group_id, temp->marks, temp->student1_id, temp->student2_id);
            temp = temp->next;
        }
        
        // free memory allocated for marks records
        while (marks_head != NULL) {
            temp = marks_head;
            marks_head = marks_head->next;
            free(temp);
        }
        
        current_assignment = current_assignment->next;
    }
}






void print_top_marks(assignment_record* ar_head)                                                                                           //7th
{
    assignment_record* current_assignment = ar_head;
    
    while (current_assignment != NULL)
    {
        student_group_record* current_group = current_assignment->grp_head;
        marks_record* marks_head = NULL;
        marks_record* temp = NULL;
        
        while (current_group != NULL)
        {
            int total_marks = current_group->marks_given_student1 + current_group->marks_given_student2;
            
            // create new marks record
            marks_record* new_marks = (marks_record*) malloc(sizeof(marks_record));
            new_marks->group_id = current_group->group_id;
            new_marks->student1_id = current_group->student1_id;
            new_marks->student2_id = current_group->student2_id;
            new_marks->marks = total_marks;
            new_marks->next = NULL;
            
            // insert marks record into linked list
            if (marks_head == NULL) {
                marks_head = new_marks;
            } else {
                if (new_marks->marks >= marks_head->marks) {
                    new_marks->next = marks_head;
                    marks_head = new_marks;
                } else {
                    temp = marks_head;
                    while (temp->next != NULL && new_marks->marks < temp->next->marks) {
                        temp = temp->next;
                    }
                    new_marks->next = temp->next;
                    temp->next = new_marks;
                }
            }
            
            current_group = current_group->next;
        }
        
        printf("Details of student-groups for Assignment %d:\n", current_assignment->assignment_id);
        temp = marks_head;
        printf("Group %d, Total marks: %d, Students: %d and %d\n", temp->group_id, temp->marks, temp->student1_id, temp->student2_id);
    
        // free memory allocated for marks records
        while (marks_head != NULL) {
            temp = marks_head;
            marks_head = marks_head->next;
            free(temp);
        }
        
        current_assignment = current_assignment->next;
    }
}






struct Date {                                                                                                                                 //8th
    int d, m, y;
};
const int monthDays[12]
    = { 31, 28, 31, 30, 31, 30,
       31, 31, 30, 31, 30, 31 };
int countLeapYears(struct Date d)
{
    int years = d.y;
    if (d.m <= 2)
        years--;
    return ((years+1) / 4) - ((years+1) / 100) + ((years+1) / 400);
}
int getDifference(struct Date dt1,struct Date dt2)
{
    int i;
    long int n1 = dt1.y * 365 + dt1.d;
    for ( i = 0; i < dt1.m - 1; i++){
        n1 = n1 + monthDays[i];
    n1 = n1 + countLeapYears(dt1);
}
    long int n2 = dt2.y * 365 + dt2.d;
    for (i = 0; i < dt2.m - 1; i++){
        n2 = n2 + monthDays[i];
    n2 = n2 + countLeapYears(dt2);
}
    return (n2 - n1);
}

void duedate_is_over(assignment_record* ar_head)
{
    assignment_record* current_assignment=ar_head;
    
    int i;
    for( i=0;i<num_assignments;i++)
    {
        int n;
        struct Date dt1 = { 16+i, 3, 2023 };
        struct Date dt2 = { 17, 3, 2023 };
        n=getDifference(dt1, dt2);
        student_group_record* current_group=current_assignment->grp_head;
        while(current_group!=NULL)
        {
            if(strcmp(current_group->status,"not_submitted\n")==0)
              //  printf("Srihitha");
            {
                if(n>=0) // check if the due date is over
                {
                    printf("Due date is over for student group %d\n", current_group->group_id);
                }
                else // due date is not over
                {
                    printf("Due date is not over for student group %d\n", current_group->group_id);
                }
                
                // print the group details
                printf("Assignment ID: %d, Group ID: %d, Student 1 ID: %d, Student 2 ID: %d\n",
                       current_assignment->assignment_id, current_group->group_id, current_group->student1_id, current_group->student2_id);
            }
            current_group=current_group->next;
        }
        current_assignment=current_assignment->next;
    }
}



int main()
{
    int choice;
    student_record *sr_head = NULL;
    assignment_record *ar_head = NULL;
    sr_head=createsr(sr_head);
    //print_student_record(sr_head);
    ar_head=createar(ar_head);
    //print_assignment_record(ar_head);
    
    
    while (1) {
        printf("\n");
        printf("1. Insert a student record\n");
        printf("2. Insert an assignment record\n");
        printf("3. Change aassignment status\n");
        printf("4. Print if assignment is declared or evaluated\n");
        printf("5. Print the list of student groups that have not submitted the assignments even if th eduedate is over\n");
        printf("6. Print the list of groups yet to be evaluated\n");
        printf("7. Print the details of student-groups for a given assignment in decreasing order of their marks\n");
        printf("8. Print the student-groups receiving top marks in each of the assignments\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sr_head=insert_student_record(sr_head);
                ar_head=update_assignment_record(sr_head, ar_head);
                print_student_record(sr_head);
                print_assignment_record(ar_head);
                printf("--------------------------------------\n");
                break;
            case 2:
                ar_head=insert_assignment_record(ar_head);
                sr_head=update_student_record(sr_head, ar_head);
                print_assignment_record(ar_head);
                print_student_record(sr_head);
                printf("--------------------------------------\n");
                break;
            case 3:
                change_status_of_assignment(ar_head);
                printf("--------------------------------------\n");
                break;
            case 4:
                assignment_declared_or_evaluated(ar_head);
                printf("--------------------------------------\n");
                break;
            case 5:
                duedate_is_over(ar_head);
                printf("--------------------------------------\n");
                break;
            case 6:
                print_yet_to_be_evaluated(sr_head);
                printf("--------------------------------------\n");
                break;
            case 7:
                print_marks_in_sorted_order(ar_head);
                printf("--------------------------------------\n");
                break;
            case 8:
                print_top_marks(ar_head);
                printf("--------------------------------------\n");
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice\n");
                printf("--------------------------------------\n");
        }
    }

    return 0;
}
