set(CTEST_CUSTOM_POST_MEMCHECK
    "geninfo -o covall.info src; lcov -e covall.info '/home/aschedel/workspace/codebase/soc-configuration/src/*' -o covsrc.info; genhtml -o Testing/coverage --no-function-coverage covsrc.info"
)
