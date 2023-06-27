#ifndef TESTING_RUNNER_H_
#define TESTING_RUNNER_H_

#include <stddef.h>

typedef int(TestFunc)(void);

typedef struct Test {
  TestFunc *Func;
  const char *Name;
} Test;

#define TestDefine(test)                                                       \
  { .Name = "" #test, .Func = &(test) }

int TestsRunWithArgs(Test *tests, size_t len, int argc, char *argv[]);

#define TestsRun(tests, argc, argv)                                            \
  TestsRunWithArgs(tests, sizeof(tests) / sizeof(Test), argc, argv)

#endif // TESTING_RUNNER_H_
