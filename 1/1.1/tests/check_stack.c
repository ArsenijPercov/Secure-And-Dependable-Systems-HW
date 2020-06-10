#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <rpn-stack.h>

typedef struct _rpn_stack
{
    void * data;
    struct _rpn_stack* next;
}rpn_stack_t;

START_TEST (test_stack_constructor)
{
    fprintf(stderr, "Running test_stack_constructor\n");
    rpn_stack_t *stack;
    stack = rpn_stack_new();
    ck_assert_ptr_ne(stack, NULL);
    fprintf(stderr, "Done\n\n");
    
}END_TEST


START_TEST (test_stack_push_delete_int)
{
    fprintf(stderr, "Running test_stack_push_delete_int\n");
    rpn_stack_t *stack;
    stack = rpn_stack_new();
    int data[] = {14, 18, 3};
    size_t len = sizeof(data)/sizeof(data[0]);
    size_t i;
    for(i = 0; i < len; i++){
        rpn_stack_push(stack, &data[i]);
        int* tmp = rpn_stack_peek(stack);
        ck_assert_int_eq(data[i], *tmp);
    }
    rpn_stack_del(stack);
    ck_assert_ptr_eq(stack,NULL);
    fprintf(stderr, "Done\n\n");
}END_TEST

START_TEST (test_stack_push_array)
{
    fprintf(stderr, "Running test_stack_push_array\n");
    rpn_stack_t *stack;
    stack = rpn_stack_new();
    int data[2][3] = {{13,12,11},{14, 18, 3}};
    size_t len = sizeof(data)/sizeof(data[0][0]);
    size_t i;
    for(i = 0; i < len; i++){
        rpn_stack_push(stack, &data[i]);
        int* tmp = rpn_stack_peek(stack);
        ck_assert_int_eq(data[i], *tmp);
    }
    rpn_stack_del(stack);
    ck_assert_ptr_eq(stack,NULL);
    fprintf(stderr, "Done\n\n");

}END_TEST

START_TEST (test_stack_pop)
{
    fprintf(stderr, "Running test_stack_pop\n");
    rpn_stack_t *stack;
    stack = rpn_stack_new();
    int data[] = {14, 18, 3};
    size_t len = sizeof(data)/sizeof(data[0]);
    size_t i;
    for(i = 0; i < len; i++){
        rpn_stack_push(stack, &data[i]);
    }
    for(i = 0; i < len; i++){
        int* tmp = rpn_stack_pop(stack);
        ck_assert_int_eq(data[len-1-i], *tmp);
    }
    rpn_stack_del(stack);
    ck_assert_ptr_eq(stack,NULL);
    fprintf(stderr, "Done\n\n");
    
}END_TEST

START_TEST (test_stack_pop_empty)
{
    fprintf(stderr, "Running test_stack_pop_empty\n");
    rpn_stack_t *stack;
    stack = rpn_stack_new();
    int* tmp = rpn_stack_pop(stack);
    ck_assert_ptr_eq(NULL, *tmp);
    fprintf(stderr, "Done\n\n");
}END_TEST



START_TEST (test_stack_peek_empty)
{
    fprintf(stderr, "Running test_stack_peek_empty\n");
    rpn_stack_t *stack;
    stack = rpn_stack_new();
    int* tmp = rpn_stack_peek(stack);
    ck_assert_ptr_eq(NULL, *tmp);
    fprintf(stderr, "Done\n\n");
}END_TEST

START_TEST (test_stack_empty_empty)
{
   fprintf(stderr, "Running test_stack_empty_empty\n");
    rpn_stack_t *stack;
    stack = rpn_stack_new();
    int tmp = rpn_stack_empty(stack);
    ck_assert_int_eq(1, tmp);
    fprintf(stderr, "Done\n\n");
    
}END_TEST

START_TEST (test_stack_empty_nonempty)
{
    fprintf(stderr, "Running test_stack_empty_nonempty\n");
    rpn_stack_t *stack;
    stack = rpn_stack_new();
    int data[] = {14, 18, 3};
    size_t len = sizeof(data)/sizeof(data[0]);
    size_t i;
    for(i = 0; i < len; i++){
        rpn_stack_push(stack, &data[i]);
    }
    int res = rpn_stack_empty(stack);
    ck_assert_int_eq(0,res);
    rpn_stack_del(stack);
    ck_assert_ptr_eq(stack,NULL);
    fprintf(stderr, "Done\n\n");
}END_TEST


static Suite* gdb_suite(void){
    Suite* s;
    TCase *tc_stack_constructor,*tc_stack_push_delete_int, *tc_stack_push_array,
     *tc_stack_pop, *tc_stack_pop_empty, *tc_stack_peek_empty, *tc_stack_empty_empty, *tc_stack_empty_nonempty;
    s = suite_create("all");
    tc_stack_constructor = tcase_create("stack_constructor");
    tc_stack_push_delete_int = tcase_create("stack_push_delete_int");
    tc_stack_push_array = tcase_create("stack_push_array");
    tc_stack_pop = tcase_create("stack_pop");
    tc_stack_pop_empty = tcase_create("stack_pop_empty");
    tc_stack_peek_empty = tcase_create("stack_peek_empty");
    tc_stack_empty_empty = tcase_create("stack_empty_empty");
    tc_stack_empty_nonempty = tcase_create("stack_empty_nonempty");

    tcase_add_test(tc_stack_constructor, test_stack_constructor);
    tcase_add_test(tc_stack_push_delete_int, test_stack_push_delete_int);
    tcase_add_test(tc_stack_push_array, test_stack_push_array);
    tcase_add_test(tc_stack_pop, test_stack_pop);
    tcase_add_test(tc_stack_pop_empty, test_stack_pop_empty);
    tcase_add_test(tc_stack_peek_empty, test_stack_peek_empty);
    tcase_add_test(tc_stack_empty_empty, test_stack_empty_empty);
    tcase_add_test(tc_stack_empty_nonempty, test_stack_empty_nonempty);

    suite_add_tcase(s,tc_stack_constructor);
    suite_add_tcase(s,tc_stack_push_delete_int);
    suite_add_tcase(s,tc_stack_push_array);
    suite_add_tcase(s,tc_stack_pop);
    suite_add_tcase(s,tc_stack_pop_empty);
    suite_add_tcase(s,tc_stack_peek_empty);
    suite_add_tcase(s,tc_stack_empty_empty);
    suite_add_tcase(s,tc_stack_empty_nonempty);

    return s;
}


int main(void){

   int num_failed;
   Suite* s;
   SRunner *sr;

   s = gdb_suite();
   sr = srunner_create(s);

   srunner_run_all(sr, CK_NORMAL);
   num_failed = srunner_ntests_failed(sr);
   srunner_free(sr);

   return (num_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

}