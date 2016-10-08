#include "minunit.h"
mu_suite(darray_suite);
mu_suite(llist_suite);

int main(int argc, char *argv[])
{
    mu_run_suite(list_suite);
    mu_run_suite(darray_suite);
    mu_report();
    return 0;
}
