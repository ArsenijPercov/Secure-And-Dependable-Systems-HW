#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 32
typedef struct Node
{
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

int is_number(char* str);
int get_min(List* my_list);
int get_max(List* my_list);
double get_mean(List* my_list);

int main(int argc, char** argv)
{
    
    int c;
    int count_row =0;
    int count_column = 0;
    
    List **matrix = (List**) malloc(sizeof(Node*)*SIZE);
    
    if(matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    for(int i=0; i<SIZE; i++) {
        matrix[i] = (List*) malloc(sizeof(List));
        
        if(matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }
    

    Node* cursor[SIZE] ;
    for (int i =0 ;i<SIZE;i++){
        Node *head;
        head = (Node*) malloc(sizeof(Node));
        matrix[i]->head = head;
        cursor[i] = matrix[i]->head;
    }
    int col_size = __INT16_MAX__;
    while ( (scanf("%d", &c)) != EOF )
    {
        
        Node* new;
        if (count_column + 1 > col_size)
        {
            fprintf(stderr,"Column number exceeded the defined one\n");
            exit(1);
        }
        if (count_row==0)
        {
            cursor[count_column]->data = c;
            
        }
        else
        {
            new = (struct  Node*) malloc(sizeof(struct Node));
            new->data = c;
            cursor[count_column]->next = new;
            cursor[count_column] = new; 
        }
        char x;
        count_column++;
        if (x = getchar() == '\n')
        {    
            if (count_row != 0 && count_column<col_size)
            {
                fprintf(stderr,"Column number is lower the defined one\n");
                exit(1);
            }
            count_row++;
            col_size = count_column;
            count_column = 0;
            
        }      
    }
    if (count_row == 0)
    {
        fprintf(stderr,"NO input\n");
        exit(1);
        
    }
    for (int i =0 ;i<col_size;i++){
        cursor[i] = matrix[i]->head;
    }
    
    for (int i = 0; i < col_size;i++){
    
        for (int j=0; j< count_row; j++){
            
            printf("%d",cursor[i]->data);
            cursor[i] = cursor[i]->next;
    
           
        }
        printf("\n");
    }
    
    int n = (argc-1)/2;
    printf("%d %d\n",argc,n);
    if((argc-1)%2 != 0) 
    {
        fprintf(stderr, "Invalid command options\n");
        exit(1);
    }

    double result[n];
    int res_idx = 0;

    for(int i=1; i<argc; i += 2) {

        if(!is_number(argv[i+1])) {
                fprintf(stderr, "Argument is not a number\n");
                exit(1);
        }
        int list_no = atoi(argv[i+1]);
        if(matrix[list_no] == NULL) {
                fprintf(stderr, "Column number doesn't exist\n");
                exit(1);
        }

        if(strcmp(argv[i], "max") == 0) {
            result[res_idx++] = get_max(matrix[list_no]);
        } else if(strcmp(argv[i], "min") == 0) {
            result[res_idx++] = get_min(matrix[list_no]);
        } else if(strcmp(argv[i], "mean") == 0) {
            result[res_idx++] = get_mean(matrix[list_no]);
        } else {
            printf("Invalid option\n");
            exit(1);
        }
    }
    for (int i=0; i<n; i++) {
        printf("%.4lf ", result[i]);
    };
    
    printf("\n");
    return 0;
    
}
int is_number(char* str) {
    for(int i=0; i<strlen(str); i++) {
        if( !(str[i] >= '0' && str[i] <= '9')) {
            return 0;
        }
    }
    return 1;
}

int get_min(List* my_list) {
    if(my_list == NULL || my_list->head == NULL) {
        fprintf(stderr, "Invalid column number\n");
        exit(1);
    }
    int min = my_list->head->data;
    for(Node* cursor = my_list->head; cursor; cursor = cursor->next) {
        if(cursor->data < min) {
            min = cursor->data;
        }
    }
    return min;
}

int get_max(List* my_list) {
    if(my_list == NULL || my_list->head == NULL) {
        fprintf(stderr, "Invalid column number\n");
        exit(1);
    }
    int max = my_list->head->data;
    for(Node* cursor = my_list->head; cursor; cursor = cursor->next) {
        if(cursor->data > max) {
            max = cursor->data;
        }
    }
    return max;
}

double get_mean(List* my_list) {
    if(my_list == NULL || my_list->head == NULL) {
        fprintf(stderr, "Invalid column number\n");
        exit(1);
    }
    int n=0;
    double sum=0;
    for(Node* cursor = my_list->head; cursor; cursor = cursor->next) {
        sum += cursor->data;
        printf("%d ", cursor->data);
        n++;
    }
    printf("\n");
    return sum/n;
}
