/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * cxx98IO.h
 *
 *  Created on: Apr 5, 2018
 *      Author: William F Godoy godoywf@ornl.gov
 */

#ifndef ADIOS2_BINDINGS_CXX98_CXX98_CXX98IO_H_
#define ADIOS2_BINDINGS_CXX98_CXX98_CXX98IO_H_

#include <cstddef>
#include <string>
#include <vector>

#include "cxx98Attribute.h"
#include "cxx98Engine.h"
#include "cxx98Variable.h"
#include "cxx98types.h"

#include "adios2/ADIOSConfig.h"

#ifdef ADIOS2_HAVE_MPI
#include <mpi.h>
#endif

struct adios2_io;

namespace adios2
{
namespace cxx98
{

class ADIOS;

class IO
{
    friend class ADIOS;

public:
    ~IO();

    template <class T>
    Variable<T>
    DefineVariable(const std::string &name, const Dims &shape = Dims(),
                   const Dims &start = Dims(), const Dims &count = Dims(),
                   const bool constantDims = false);

    template <class T>
    Variable<T> InquireVariable(const std::string &name);

    /**
     * @brief Define array attribute
     * @param name must be unique for the IO object
     * @param array pointer to user data
     * @param elements number of data elements
     * @return reference to internal Attribute
     * @exception std::invalid_argument if Attribute with unique name is
     * already defined, in debug mode only
     */
    template <class T>
    Attribute<T> DefineAttribute(const std::string &name, const T *array,
                                 const size_t size);

    /**
     * @brief Define single value attribute
     * @param name must be unique for the IO object
     * @param value single data value
     * @return reference to internal Attribute
     * @exception std::invalid_argument if Attribute with unique name is already
     * defined, in debug mode only
     */
    template <class T>
    Attribute<T> DefineAttribute(const std::string &name, const T &value);

/**
 * TODO Gets an existing attribute of primitive type by name
 * @param name of attribute to be retrieved
 * @return pointer to an existing attribute in current IO, NULL if not
 * found
 */
//    template <class T>
//    Attribute<T> InquireAttribute(const std::string &name);

#ifdef ADIOS2_HAVE_MPI
    /**
     * Open an Engine to start heavy-weight input/output operations.
     * New MPI communicator version, valid with MPI compiled library only
     * @param name unique engine identifier
     * @param mode
     * @param comm
     * @return engine object
     */
    Engine Open(const std::string &name, const Mode mode, MPI_Comm comm);
#endif

    /**
     * Open an Engine to start heavy-weight input/output operations.
     * Reuses ADIOS object communicator ADIOS>IO>Engine in MPI library
     * version
     * @param name unique engine identifier
     * @param mode adios2::Mode::Write,adios2::Mode::Read or
     * adios2::Mode::Append
     * @return engine object
     */
    Engine Open(const std::string &name, const Mode mode);

    /**
     * Inspect current engine type
     * @return current engine type
     */
    std::string EngineType() const;

private:
    IO(adios2_io &io);
    adios2_io &m_IO;
};

// Explicit declaration of the public template methods
#define declare_template_instantiation(T)                                      \
    extern template Variable<T> IO::InquireVariable<T>(const std::string &);

ADIOS2_FOREACH_CXX98_TYPE_1ARG(declare_template_instantiation)
#undef declare_template_instantiation

} // end namespace cxx98
} // end namespace adios2

#endif /* ADIOS2_BINDINGS_CXX98_CXX98_CXX98IO_H_ */
