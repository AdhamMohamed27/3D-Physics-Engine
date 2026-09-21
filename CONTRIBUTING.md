# Contributing

Contributions to 3DEngineCpp are welcome.

## Workflow

1. Fork the repository and create a focused feature branch.
2. Preserve existing copyright, license, and attribution notices.
3. Add or update tests for behavior changes.
4. Build the engine and run the physics test suite.
5. Open a pull request that describes the change and validation performed.

## Validation

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --target 3DEngineCpp physics_unit_tests
ctest --test-dir build --output-on-failure
```

## Attribution requirement

This project is based on original work by Benny Bobaganoosh, also known as
TheBennyBox. Do not remove, replace, or obscure that attribution. When
redistributing modified files, retain the original notices and clearly mark
the files that were changed, as required by Apache License 2.0 section 4.

Contributors may add their own copyright or attribution notices for original
modifications alongside the existing notices.