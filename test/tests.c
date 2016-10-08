#include "minunit.h"
mu_suite(darr_suite);
mu_suite(dllist_suite);

int main(int argc, char *argv[])
{
    mu_run_suite(dllist_suite);
    mu_run_suite(darr_suite);
    mu_report();
    return 0;
}
