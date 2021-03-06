#------------------------------------------------------------------------------#
# Distributed under the OSI-approved Apache License, Version 2.0.  See
# accompanying file Copyright.txt for details.
#------------------------------------------------------------------------------#

# BPLS2
add_executable(bpls2 ./bpls2/bpls2.cpp)
target_link_libraries(bpls2 adios2 adios2sys_interface)
install(TARGETS bpls2 EXPORT adios2
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/bpls2/bpls2.cmake.gen.in
  ${PROJECT_BINARY_DIR}/bpls2.cmake.gen
  @ONLY
)
file(GENERATE
  OUTPUT ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/bpls2.cmake
  INPUT ${PROJECT_BINARY_DIR}/bpls2.cmake.gen
)

# ADIOS2_REORGANIZE
add_executable(adios2_reorganize 
               ./adios2_reorganize/main.cpp 
               ./adios2_reorganize/Reorganize.cpp 
               Utils.cpp)
target_link_libraries(adios2_reorganize adios2)
install(TARGETS adios2_reorganize EXPORT adios2
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Add MPI dependency to parallel tools
if(ADIOS2_HAVE_MPI)
  target_link_libraries(adios2_reorganize MPI::MPI_C)
endif()



