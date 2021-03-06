/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * TestDataManCallback1D.cpp
 *
 *  Created on: Aug 15, 2018
 *      Author: Jason Wang
 */

#include "TestDataMan.h"

class DataManEngineTest : public ::testing::Test
{
public:
    DataManEngineTest() = default;
};

#ifdef ADIOS2_HAVE_ZEROMQ
TEST_F(DataManEngineTest, WriteRead_1D_Callback)
{
    // set parameters
    size_t timeout = 3;
    Dims shape = {10};
    Dims start = {0};
    Dims count = {10};
    size_t steps = 10000;
    std::string workflowMode = "subscribe";
    std::vector<adios2::Params> transportParams = {
        {{"Library", "ZMQ"}, {"IPAddress", "127.0.0.1"}, {"Port", "12311"}}};

    // run workflow
    auto r = std::thread(DataManReaderCallback, shape, start, count, steps,
                         workflowMode, transportParams, timeout);
    std::cout << "Reader thread started" << std::endl;
    auto w = std::thread(DataManWriter, shape, start, count, steps,
                         workflowMode, transportParams);
    std::cout << "Writer thread started" << std::endl;
    w.join();
    std::cout << "Writer thread ended" << std::endl;
    r.join();
    std::cout << "Reader thread ended" << std::endl;
}

#endif // ZEROMQ

int main(int argc, char **argv)
{
#ifdef ADIOS2_HAVE_MPI
    int mpi_provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &mpi_provided);
    std::cout << "MPI_Init_thread required Mode " << MPI_THREAD_MULTIPLE
              << " and provided Mode " << mpi_provided << std::endl;
    if (mpi_provided != MPI_THREAD_MULTIPLE)
    {
        MPI_Finalize();
        return 0;
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
#endif

    int result;
    ::testing::InitGoogleTest(&argc, argv);
    result = RUN_ALL_TESTS();

#ifdef ADIOS2_HAVE_MPI
    MPI_Finalize();
#endif

    return result;
}
