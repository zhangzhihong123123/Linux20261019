/* 学号：20262826  姓名：张智泓
 * 本文件是“调用方”：只 include 头文件并链接 mymath.lib，
 * 看不到 add / subtract / multiply / divide 的实现源码。 */
#include "test.h"

#include <math.h>
#include <stdio.h>

#include "add.h"
#include "divide.h"
#include "multiply.h"
#include "subtract.h"

static int check_result(const char *name, double actual, double expected)
{
    if (fabs(actual - expected) <= 1e-12) {
        printf("[PASS] %s\n", name);
        return 1;
    }

    printf("[FAIL] %s: expected %.12f, got %.12f\n", name, expected, actual);
    return 0;
}

int run_tests(void)
{
    int passed = 0;
    int total = 0;

    ++total;
    passed += check_result("add", add(2.5, 1.25), 3.75);
    ++total;
    passed += check_result("add with negative", add(-2.5, 1.25), -1.25);
    ++total;
    passed += check_result("subtract", subtract(5.5, 2.25), 3.25);
    ++total;
    passed += check_result("multiply", multiply(2.5, -4.0), -10.0);
    ++total;
    passed += check_result("divide", divide(7.5, 2.5), 3.0);

    ++total;
    if (isnan(divide(1.0, 0.0))) {
        printf("[PASS] divide by zero returns NAN\n");
        ++passed;
    } else {
        printf("[FAIL] divide by zero returns NAN\n");
    }

    printf("%d/%d tests passed\n", passed, total);
    return passed == total ? 0 : 1;
}

int main(void)
{
    return run_tests();
}
