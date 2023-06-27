#include "runner.h"
#include <flags/flags.h>
#include <flags/strings.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Args {
  bool Help;
  bool Verbose;
  bool ShowRun;
  bool ShowSkip;
  char Filter[32];
} Args;

void ArgsInit(Args *args) {
  args->Help = false;
  args->Verbose = false;
  args->ShowRun = false;
  args->ShowSkip = false;
  memset(args->Filter, 0, 32); // NOLINT
}

int TestsRunWithArgs(Test *tests, size_t len, int argc, char *argv[]) {
  Args args;
  int index = 0;

  ArgsInit(&args);
  FlagOptionsDeclare(
      options, FlagsNewBool(&args.Help, "help", "display help menu"),
      FlagsNewBool(&args.Verbose, "verbose", "enable verbose output"),
      FlagsNewBool(&args.ShowRun, "show-run", "display which tests run"),
      FlagsNewBool(&args.ShowSkip, "show-skip", "display which tests skip"),
      FlagsNewString(args.Filter, 32, "filter",
                     "only tests that match the filter will run"), );
  Flags flags = FlagsDefineOnlyOptions(options);

  FlagError err = FlagsParse(argc, argv, &flags, &index);
  if (err) {
    FlagsPrintError(argc, argv, err, index);
    return EXIT_FAILURE;
  }

  if (args.Help) {
    FlagsPrintHelp(argv[0], &flags);
    return EXIT_SUCCESS;
  }

  bool isFilterSet = StringIsNotBlankWithLen(args.Filter, strlen(args.Filter));
  int totalCount = len, failedCount = 0, skippedCount = 0, okCount = 0;
  for (size_t i = 0; i < len; i++) {
    const char *name = (tests[i]).Name;
    bool skip = !StringIsSubstringOf(args.Filter, strlen(args.Filter), name,
                                     strlen(name));
    if (skip) {
      skippedCount++;
      if (args.ShowSkip || args.Verbose) {
        fprintf(stderr, "tests: skipping test %s\n", (tests)[i].Name);
      }
      continue;
    }

    if (args.Verbose) {
      fprintf(stderr, "tests: running test %s\n", (tests)[i].Name);
    }

    const int code = (tests)[i].Func();
    if (code) {
      failedCount++;
      fprintf(stderr, "tests: test %s failed\n", name);
      continue;

    } else if (isFilterSet || args.ShowRun || args.Verbose) {
      fprintf(stderr, "tests: test %s ok\n", name);
    }

    okCount++;
  }

  if (failedCount) {
    fprintf(stderr, "tests: %d out of %d tests failed\n", failedCount,
            totalCount);
    return EXIT_FAILURE;
  }

  if (args.Verbose) {
    fprintf(stderr, "tests: run %d tests, skipped %d tests, %d ok\n",
            totalCount, skippedCount, okCount);

  } else {
    fprintf(stderr, "tests: all ok\n");
  }

  return EXIT_SUCCESS;
}
