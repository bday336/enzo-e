// See LICENSE_CELLO file for license and copyright information

/// @file     io_Output.hpp 
/// @author   James Bordner (jobordner@ucsd.edu) 
/// @date     Mon Mar 14 17:35:56 PDT 2011
/// @todo     Extract Schedule object for scheduling output
/// @brief    [\ref Io] Declaration for the Output component

#ifndef IO_OUTPUT_HPP
#define IO_OUTPUT_HPP

class Hierarchy;
class Patch;
class Schedule;

class Output {

  /// @class    Output
  /// @ingroup  Io
  /// @brief    [\ref Io] define interface for various types of IO for Simulations

public: // functions

  /// Create an uninitialized Output object with the given file_name format
  Output() throw();

   /// Set file name
  void set_filename (std::string filename,
		      std::vector<std::string> fileargs) throw()
   {
     file_name_ = filename; 
     file_args_ = fileargs;
   };

  // /// Set file name variable to use
  // void set_file_var (std::string file_var, size_t index) throw()
  // { 
  //   if ((index >= file_args_.size())) {
  //     file_args_.resize(index+1);
  //   }
  //   file_args_[index] = file_var;
  // }

  /// Set field list
  void set_field_list (std::vector<int> field_list) throw();

  /// Return the Schedule object pointer
  Schedule * schedule() throw() 
  { return schedule_; };
  
  /// Write hierarchy-related data to disk if scheduled
  void scheduled_write
  (  const FieldDescr * field_descr,
     Hierarchy * hierarchy, int cycle, double time, bool root_call=true) throw();

  /// Write a patch-related data to disk if scheduled
  void scheduled_write
  (  const FieldDescr * field_descr,
     Patch * patch, Hierarchy * hierarchy,
     int cycle, double time, bool root_call=true) throw();

  /// Write a block-related to disk if scheduled
  void scheduled_write
  (  const FieldDescr * field_descr,
     Block * block, Patch * patch, Hierarchy * hierarchy,
     int cycle, double time, bool root_call=true) throw();

  std::string expand_file_name (int cycle, double time) const throw();

  int process_write () const throw () 
  { return process_write_; };

  bool is_writer (int ip) const throw () 
  { return (ip % process_write_ == 0); };

#ifdef CONFIG_USE_CHARM
  int counter() 
  { 
    if (count_reduce_ >= process_write_) {count_reduce_ = 0;}
    count_reduce_++; 
    PARALLEL_PRINTF ("Output:counter(%d)\n",count_reduce_);
    return (count_reduce_);
  }

#endif

public: // virtual functions

#ifdef CONFIG_USE_CHARM

  /// Open file before writing
  virtual void open (const Hierarchy * hierarchy, int cycle, double time) throw() = 0;

  /// Accumulate block-local data
  virtual void block (const Block * block) throw() = 0;

  /// Close file after writing
  virtual void close () throw() = 0;

#endif


  /// Write hierarchy data to disk
  virtual void write 
  ( const FieldDescr * field_descr,
    int index, Hierarchy * hierarchy, 
    int cycle, double time,
    bool root_call=true, int ix0=0, int iy0=0, int iz0=0) throw() = 0;

  /// Write patch data to disk; may be called by write (Hierarchy)
  virtual void write 
  ( const FieldDescr * field_descr,
    int index, Patch * patch, Hierarchy * hierarchy,
    int cycle, double time, 
    bool root_call=true, int ix0=0, int iy0=0, int iz0=0) throw() = 0;

  /// Write block data to disk; may be called by write (Patch)
  virtual void write 
  ( const FieldDescr * field_descr,
    int index, Block * block, Patch * patch, Hierarchy * hierarchy, 
    int cycle, double time, 
    bool root_call=true, int ix0=0, int iy0=0, int iz0=0) throw() = 0;

protected: // attributes

  IoSimulation * io_simulation_;

  Schedule * schedule_;

  /// Only processes with id's divisible by process_write_ writes
  /// (1: all processes write; 2: 0,2,4,... write; np: root process writes)
  int process_write_;

#ifdef CONFIG_USE_CHARM
  /// counter for reduction of data from non-writers to writers
  int count_reduce_;
#endif

  /// Name of the file to write, including format arguments
  std::string file_name_;

  /// Format strings for file name, if any ("cycle", "time", etc.)
  std::vector<std::string> file_args_;

  /// Whether Output is scheduled for next call to scheduled write
  bool scheduled_;
  
  /// List of fields to output
  std::vector<int> field_list_;

};

#endif /* IO_OUTPUT_HPP */