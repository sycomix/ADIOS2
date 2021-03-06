/*
 * Distributed under the OSI-approved Apache License, Version 2.0.  See
 * accompanying file Copyright.txt for details.
 *
 * adios2_c_adios.h
 *
 *  Created on: Nov 8, 2017
 *      Author: William F Godoy godoywf@ornl.gov
 */

#ifndef ADIOS2_BINDINGS_C_C_ADIOS2_C_ADIOS_H_
#define ADIOS2_BINDINGS_C_C_ADIOS2_C_ADIOS_H_

#include "adios2_c_types.h"

#include "adios2/ADIOSMPICommOnly.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create an ADIOS struct pointer handler using a runtime config file in a MPI
 * application.
 * @param config_file runtime configuration file, XML format, future: JSON
 * @param mpi_comm MPI communicator from application for ADIOS scope
 * @param debug_mode adios2_debug_mode_on or adios2_debug_mode_off
 * @return valid ADIOS* handler
 */
adios2_adios *adios2_init_config(const char *config_file, MPI_Comm mpi_comm,
                                 const adios2_debug_mode debug_mode);

/**
 * Create an ADIOS struct pointer in a MPI application, without a runtime config
 * file.
 * @param mpi_comm MPI communicator from application for ADIOS scope
 * @param debug_mode adios2_debug_mode_on or adios2_debug_mode_off
 * @return valid ADIOS* handler
 */
adios2_adios *adios2_init(MPI_Comm mpi_comm,
                          const adios2_debug_mode debug_mode);
/**
 * Create an ADIOS struct pointer handler using a runtime config file in serial
 * nonMPI
 * application.
 * @param config_file runtime configuration file, XML format, future: JSON
 * @param debug_mode adios2_debug_mode_on or adios2_debug_mode_off
 * @return valid ADIOS* handler
 */
adios2_adios *adios2_init_config_nompi(const char *config_file,
                                       const adios2_debug_mode debug_mode);

/**
 * Create an ADIOS struct pointer handler in serial nonMPI application.
 * @param debug_mode adios2_debug_mode_on or adios2_debug_mode_off
 * @return valid ADIOS* handler
 */
adios2_adios *adios2_init_nompi(const adios2_debug_mode debug_mode);

/**
 * Create an IO struct pointer handler from ADIOS* handler
 * @param adios ADIOS* handler that owns the IO* handler
 * @param io_name unique name for the newly declared io handler
 * @return valid IO* handler
 */
adios2_io *adios2_declare_io(adios2_adios *adios, const char *io_name);

/**
 * Retrieves a previously declared IO handler
 * @param adios ADIOS* handler that owns the IO* handler
 * @param io_name unique name for the previously declared io handler
 * @return valid IO* handler or NULL is not found
 */
adios2_io *adios2_at_io(adios2_adios *adios, const char *io_name);

/**
 * Define an operator supported by ADIOS2: e.g.
 * @param adios ADIOS* handler that owns the Operator* component
 * @param name unique operator name within adios component
 * @param type supported type: e.g. : "zfp", "sz"
 * @return operator handler
 */
adios2_operator *adios2_define_operator(adios2_adios *adios, const char *name,
                                        const char *type);

/**
 * Retrieve an existing operator by name
 * @param adios ADIOS* handler that owns the Operator* component
 * @param name unique operator name within adios component
 * @return if found returns an operator handler, if not found returns NULL
 */
adios2_operator *adios2_inquire_operator(adios2_adios *adios, const char *name);

/**
 * Flushes all adios2_engine in all adios2_io handlers created with the current
 * adios2_adios handler using adios2_declare_io and adios2_open
 * If no adios2_io or adios2_engine is created it does nothing.
 * @param adios input handler
 */
void adios2_flush_all(adios2_adios *adios);

/**
 * Final point for adios2_ADIOS handler.
 * Deallocate adios pointer. Required to avoid memory leaks.
 * @param adios handler to be deallocated, must be initialized with any of the
 * adios2_init signatures
 */
void adios2_finalize(adios2_adios *adios);

#ifdef __cplusplus
} // end extern C
#endif

#endif /* ADIOS2_BINDINGS_C_C_ADIOS2_C_ADIOS_H_ */
