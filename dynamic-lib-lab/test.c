/* ==========================================
   学号：20262826   姓名：张智泓
   （截图要求包含学号，保持这行注释始终可见）

   本文件通过 LoadLibrary / GetProcAddress 显式加载 mymath.dll：
   - 不 include add.h / subtract.h / multiply.h / divide.h
   - 不链接任何 .lib / .a 导入库
   - 运行时才按名字把 4 个函数取出来调用
   所以别人拿到 test.c 也看不到 4 个模块的实现源码
   ========================================== */
#include <stdio.h>
#include <math.h>
#include <windows.h>

#include "test.h"

/* 用函数指针还原 DLL 里 4 个函数的真实签名：double f(double, double) */
typedef double (*BINOP)(double, double);

static BINOP pAdd;
static BINOP pSubtract;
static BINOP pMultiply;
static BINOP pDivide;

static int check_result(const char *name, double actual, double expected)
{
    if (fabs(actual - expected) <= 1e-12) {   /* ← 条件断点打这行，条件 name[0] == 'd' */
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
    passed += check_result("add", pAdd(2.5, 1.25), 3.75);
    ++total;
    passed += check_result("add with negative", pAdd(-2.5, 1.25), -1.25);
    ++total;
    passed += check_result("subtract", pSubtract(5.5, 2.25), 3.25);
    ++total;
    passed += check_result("multiply", pMultiply(2.5, -4.0), -10.0);
    ++total;
    passed += check_result("divide", pDivide(7.5, 2.5), 3.0);

    ++total;
    if (isnan(pDivide(1.0, 0.0))) {
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
    /* 1. 运行时加载 DLL（只需 mymath.dll 在 test.exe 同目录或 PATH 里） */
    HMODULE hDll = LoadLibrary("mymath.dll");
    if (hDll == NULL) {
        printf("LoadLibrary(\"mymath.dll\") failed!\n");
        return 1;
    }

    /* 2. 按符号名取出 4 个函数的地址 */
    pAdd      = (BINOP)GetProcAddress(hDll, "add");
    pSubtract = (BINOP)GetProcAddress(hDll, "subtract");
    pMultiply = (BINOP)GetProcAddress(hDll, "multiply");
    pDivide   = (BINOP)GetProcAddress(hDll, "divide");

    if (pAdd == NULL || pSubtract == NULL || pMultiply == NULL || pDivide == NULL) {
        printf("GetProcAddress failed!\n");
        return 1;
    }

    /* 3. 通过函数指针调用，跑单元测试 */
    int ret = run_tests();

    /* 4. 用完了释放 DLL */
    FreeLibrary(hDll);
    return ret;
}
