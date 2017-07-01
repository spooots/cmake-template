set(CTEST_CUSTOM_POST_MEMCHECK
    "\
     lcov --capture --directory src --output-file coverage.info; \
     lcov \
        --remove coverage.info \
            '/usr/include/*' \
            '*/foobla-build/src/*' \
            '/usr/lib/*' \
        --output coverage_filtered.info; \
     genhtml -o Testing/coverage --no-function-coverage coverage_filtered.info \
     "
)
