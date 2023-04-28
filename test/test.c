#include "ctest.h"
#include <stdlib.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "libgeometry/counter.h"
#include "libgeometry/lexer.h"
#include "libgeometry/parser.h"

CTEST(check_figure_name_ok, t1)
{
    char* str = "circle(1.0 1.0, 2)";
    const int expected = 0;
    int len = 0;
    const int real = check_name(str, &len);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_figure_name_fail, t2)
{
    char* str = "cikcle(1.0 1.0, 2)";
    const int expected = 1;
    int len = 0;
    const int real = check_name(str, &len);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_args_ok, t3)
{
    char* str = "circle(1.0 1.0, 2)";
    const int expected = 0;
    int len = (int)strlen("circle");
    int a = check_brace_1(str, &len);
    int b = check_arg_x(str, &len);
    int c = check_arg_y(str, &len);
    int d = check_radius(str, &len);
    int e = check_brace_2(str, &len);
    if (a == 0 && b == 0 && c == 0 && d == 0 && e == 0) {
        const int real = 0;
        ASSERT_EQUAL(expected, real);
    }
}

CTEST(check_args_fail, t4)
{
    char* str = "circle(1d 1.0, 2)";
    const int expected = 3;
    int len = strlen("circle");
    check_brace_1(str, &len);
    const int real = check_arg_x(str, &len);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_args_fail_2, t5)
{
    char* str = "circle(1.0 2d, 2)";
    const int expected = 4;
    int len = strlen("circle");
    check_brace_1(str, &len);
    check_arg_x(str, &len);
    const int real = check_arg_y(str, &len);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_args_fail_3, t6)
{
    char* str = "circle(1.0 2.0, d2)";
    const int expected = 5;
    int len = strlen("circle");
    check_brace_1(str, &len);
    check_arg_x(str, &len);
    check_arg_y(str, &len);
    const int real = check_radius(str, &len);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_args_fail_4, t7)
{
    char* str = "circle(1.0 2.0, -2)";
    const int expected = 5;
    int len = strlen("circle");
    check_brace_1(str, &len);
    check_arg_x(str, &len);
    check_arg_y(str, &len);
    const int real = check_radius(str, &len);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_first_brace_ok, t8)
{
    char* str = "circle(1.0 2.0, 2)";
    const int expected = 0;
    int len = strlen("circle");
    const int real = check_brace_1(str, &len);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_first_brace_fail, t9)
{
    char* str = "circle)1.0 2.0, 2)";
    const int expected = 2;
    int len = strlen("circle");
    const int real = check_brace_1(str, &len);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_second_brace_ok, t10)
{
    char* str = "circle(1.0 1.0, 2)";
    const int expected = 0;
    int len = (int)strlen("circle");
    check_brace_1(str, &len);
    check_arg_x(str, &len);
    check_arg_y(str, &len);
    check_radius(str, &len);
    check_brace_2(str, &len);
    const int real = check_brace_2(str, &len);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_second_brace_fail, t11)
{
    char* str = "circle(1.0 1.0, 2(";
    const int expected = 6;
    int len = (int)strlen("circle");
    check_brace_1(str, &len);
    check_arg_x(str, &len);
    check_arg_y(str, &len);
    check_radius(str, &len);
    check_brace_2(str, &len);
    const int real = check_brace_2(str, &len);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_unexpected_fail, t11)
{
    char* str = "circle(1.0 1.0, 2) awd";
    const int expected = 7;
    int len = (int)strlen("circle");
    check_brace_1(str, &len);
    check_arg_x(str, &len);
    check_arg_y(str, &len);
    check_radius(str, &len);
    check_brace_2(str, &len);
    const int real = check_brace_2(str, &len);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_area, t12)
{
    char* str = "circle(1.0 1.0, 2)";
    const double expected = M_PI * 2 * 2;
    int len = (int)strlen("circle");
    check_brace_1(str, &len);
    check_arg_x(str, &len);
    check_arg_y(str, &len);
    if (check_radius(str, &len) == 0) {
        const double real = count_area(str);
        ASSERT_DBL_NEAR_TOL(expected, real, 0.00000000001);
    }
}

CTEST(check_perimeter, t12)
{
    char* str = "circle(1.0 1.0, 2)";
    const double expected = M_PI * 2 * 2;
    int len = (int)strlen("circle");
    check_brace_1(str, &len);
    check_arg_x(str, &len);
    check_arg_y(str, &len);
    if (check_radius(str, &len) == 0) {
        const double real = count_perimeter(str);
        ASSERT_DBL_NEAR_TOL(expected, real, 0.00000000001);
    }
}
