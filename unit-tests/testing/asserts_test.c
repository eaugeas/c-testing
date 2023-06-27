#include <testing/testing.h>

static int Test_AssertTrue(void) {
  AssertTrue(true);
  AssertTrue(100);
  return EXIT_SUCCESS;
}

static int Test_AssertFalse(void) {
  AssertFalse(false);
  return EXIT_SUCCESS;
}

static int Test_AssertEq(void) {
  AssertEq(1, 1);
  return EXIT_SUCCESS;
}

static int Test_AssertNotEq(void) {
  AssertNotEq(1, 2);
  return EXIT_SUCCESS;
}

static int Test_AssertMemEq(void) {
  AssertMemEq("value", "value", 5);
  return EXIT_SUCCESS;
}

static int Test_AssertMemNotEq(void) {
  AssertMemNotEq("value1", "value2", 6);
  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  Test tests[] = {
      TestDefine(Test_AssertTrue),  TestDefine(Test_AssertFalse),
      TestDefine(Test_AssertEq),    TestDefine(Test_AssertNotEq),
      TestDefine(Test_AssertMemEq), TestDefine(Test_AssertMemNotEq),
  };

  return TestsRun(tests, argc, argv);
}
