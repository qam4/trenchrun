# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(trenchrunTests LANGUAGES CXX)

# ---- Tests ----

add_executable(trenchrun_test
    source/Tests.cpp
    source/TestsRunner.cpp
    )
target_link_libraries(trenchrun_test PRIVATE trenchrun_lib)
target_compile_features(trenchrun_test PRIVATE cxx_std_17)

add_test(NAME trenchrun_test COMMAND trenchrun_test)

# ---- End-of-file commands ----

add_folders(Test)
