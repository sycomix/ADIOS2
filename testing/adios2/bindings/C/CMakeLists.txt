#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

add_executable(TestBPWriteTypes_c TestBPWriteTypes.cpp)
target_link_libraries(TestBPWriteTypes_c adios2 gtest)

add_executable(TestBPWriteTypesHighLevel_c TestBPWriteTypesHighLevel.cpp)
target_link_libraries(TestBPWriteTypesHighLevel_c adios2 gtest)

if(ADIOS2_HAVE_MPI)
  target_link_libraries(TestBPWriteTypes_c MPI::MPI_C)
  target_link_libraries(TestBPWriteTypesHighLevel_c MPI::MPI_C)
  
  set(extra_test_args
    EXEC_WRAPPER
    ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS}
  )
endif()

gtest_add_tests(TARGET TestBPWriteTypes_c ${extra_test_args})
gtest_add_tests(TARGET TestBPWriteTypesHighLevel_c ${extra_test_args})
