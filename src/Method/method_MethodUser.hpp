// $Id: method_MethodUser.hpp 1258 2010-03-02 01:07:36Z bordner $
// See LICENSE_CELLO file for license and copyright information

/// @file     method_MethodUser.hpp 
/// @author   James Bordner (jobordner@ucsd.edu) 
/// @date     Mon Jul 13 11:11:47 PDT 2009 
/// @brief    Declaration for the MethodUser component

#ifndef METHOD_METHOD_HPP
#define METHOD_METHOD_HPP

#include <vector>
#include <string>

#include "error.hpp"
#include "data.hpp"

enum argument_type {
  argument_unknown,
  argument_field,
  argument_particle
};

enum access_type {
  access_unknown,
  access_read,
  access_write,
  access_read_write
};


class MethodUser {

  /// @class    MethodUser
  /// @ingroup  Method
  /// @brief    Encapsulate external method / analysis / visualization function.

public: // interface

  /// Create a new MethodUser
  MethodUser() throw()
  {};

  /// Return the corresponding MethodControl pointer

public: // virtual functions

  /// Perform any method-specific initialization

  virtual void initialize (DataDescr * data_descr) throw() = 0;

  /// Perform any method-specific finalizations steps, e.g. to
  /// deallocate any dynamically-allocated memory

  virtual void finalize (DataDescr * data_descr) throw() = 0;

  /// Initialize PPM variable that may change.  Called once per
  /// block per timestep.

  virtual void initialize_block (DataBlock * data_block) throw() = 0;

  /// Finalize PPM after advancing a block a timestep, e.g. to deallocate
  /// any dynamically-allocated variables

  virtual void finalize_block (DataBlock * data_block) throw() = 0;

  /// Apply the method to advance a block one timestep 

  virtual void advance_block( DataBlock * data_block,
			      double t, double dt ) throw() = 0; 

  /// Return the name of the method

  virtual std::string method_name() const throw() = 0;

protected: // functions

  /// Specify a field or particle type and its access type

  void add_argument_(argument_type type,
		     std::string   name,
		     access_type   access_type,
		     DataDescr   * data_descr = 0) throw();

protected: // attributes

  /// List of argument types, e.g. argument_type_field
  std::vector<argument_type> argument_types_;

  /// List of argument names, e.g. "Density", "Velocity-X", etc.
  std::vector<std::string>   argument_names_;

  /// List of argument access types, e.g. access_read_write
  std::vector<access_type>   access_types_;

};

#endif /* METHOD_METHOD_HPP */