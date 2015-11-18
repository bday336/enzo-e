// See LICENSE_CELLO file for license and copyright information

/// @file      disk_FileIfrit.cpp
/// @author    James Bordner (jobordner@ucsd.edu)
/// @date      Thu Feb 21 16:11:36 PST 2008
/// @brief     Implementation of the FileIfrit class

#include "cello.hpp"

#include "disk.hpp"

//----------------------------------------------------------------------
 
FileIfrit::FileIfrit (std::string path, std::string name) throw()
  : File(path,name)
{
}

//----------------------------------------------------------------------

FileIfrit::~FileIfrit () throw()
{
}

//----------------------------------------------------------------------
 
void FileIfrit::file_open () throw()
{
}

//----------------------------------------------------------------------

void FileIfrit::file_create () throw()
{
}

//----------------------------------------------------------------------

void FileIfrit::file_close () throw()
{
}

//----------------------------------------------------------------------
  
void FileIfrit::file_read_meta
( void * buffer, std::string name,  int * s_type,
  int * nx, int * ny, int * nz) throw()
{
}

//----------------------------------------------------------------------
  
void FileIfrit::file_write_meta
( const void * buffer, std::string name, int type,
  int nx, int ny, int nz) throw()
{
}

//----------------------------------------------------------------------
  

// Datasets

void FileIfrit::data_open
( std::string name,  int * type,
  int * nx, int * ny, int * nz) throw()
{
}

//----------------------------------------------------------------------

void FileIfrit::data_create
( std::string name,  int type,
  int nxd, int nyd, int nzd,
  int nx,  int ny,  int nz) throw()
{
}

//----------------------------------------------------------------------

void FileIfrit::data_read (void * buffer) throw()
{
}

//----------------------------------------------------------------------

void FileIfrit::data_write 
(const void * buffer) throw()
{
}

//----------------------------------------------------------------------

void FileIfrit::data_close () throw()
{
}

//----------------------------------------------------------------------

void FileIfrit::data_read_meta
( void * buffer, std::string name,  int * s_type,
  int * nx, int * ny, int * nz) throw()
{
}

//----------------------------------------------------------------------
  
void FileIfrit::data_write_meta
( const void * buffer, std::string name, int type,
  int nx, int ny, int nz) throw()
{
}

//----------------------------------------------------------------------


// Groups

int FileIfrit::group_count () const throw()
{
  return 0;
}

//----------------------------------------------------------------------

std::string FileIfrit::group_name (size_t i) const throw()
{
  return "";
}

//----------------------------------------------------------------------

void FileIfrit::group_chdir (std::string name) throw()
{
}

//----------------------------------------------------------------------

void FileIfrit::group_open () throw()
{
}

//----------------------------------------------------------------------

void FileIfrit::group_create () throw()
{
}

//----------------------------------------------------------------------

void FileIfrit::group_close () throw()
{
}

//----------------------------------------------------------------------

void FileIfrit::group_read_meta
( void * buffer, std::string name,  int * s_type,
  int * nx, int * ny, int * nz) throw()
{
}

//----------------------------------------------------------------------
  
void FileIfrit::group_write_meta
( const void * buffer, std::string name, int type,
  int nx, int ny, int nz) throw()
{
}

//======================================================================

// void FileIfrit::read_bin
// (std::string name, 
//  float *     buffer, 
//  int *       pnx, 
//  int *       pny, 
//  int *       pnz) throw()
// ///
// {
//   FILE * fp = fopen (name.c_str(), "r");
//   ASSERT ("FileIfrit::read_bin","int or float size in unexpected",
// 	  sizeof(int)==4 && sizeof(float)==4);
//   int bound;

//   // Read header

//   ASSERT("FileIfrit::read_bin","fread error",
// 	 fread (&bound,4,1,fp));

//   if (bound != 12) WARNING("FileIfrit::read_bin","incorrect format");

//   ASSERT("FileIfrit::read_bin","fread error",
// 	 fread (pnx,4,1,fp));

//   ASSERT("FileIfrit::read_bin","fread error",
// 	 fread (pny,4,1,fp));

//   ASSERT("FileIfrit::read_bin","fread error",
// 	 fread (pnz,4,1,fp));

//   ASSERT("FileIfrit::read_bin","fread error",
// 	 fread (&bound,4,1,fp))
// ;
//   if (bound != 12) WARNING("FileIfrit::read_bin","incorrect format");

//   // Read floating-point field
//   int n = (*pnx)*(*pny)*(*pnz);

//   ASSERT("FileIfrit::read_bin","fread error",
// 	 fread (&bound,4,1,fp));

//   if (bound != 4*n) WARNING("FileIfrit::read_bin","incorrect format");

//   ASSERT("FileIfrit::read_bin","fread error",
// 	 fread (buffer,4,(*pnx)*(*pny)*(*pnz),fp));

//   ASSERT("FileIfrit::read_bin","fread error",
// 	 fread (&bound,4,1,fp));

//   if (bound != 4*n) WARNING("FileIfrit::read_bin","incorrect format");

//   fclose (fp);
// }

// //----------------------------------------------------------------------

// void FileIfrit::write_bin 
// (std::string name, 
//  float  *    buffer, 
//  int         nx, 
//  int         ny, 
//  int         nz) throw()
// ///
// {
//   FILE * fp = fopen (name.c_str(), "w");
//   ASSERT ("FileIfrit::read_bin","int or float size in unexpected",
// 	  sizeof(int)==4 && sizeof(float)==4);
//   // Write header
//   int bound = 12;
//   fwrite (&bound,4,1,fp);
//   fwrite (&nx,4,1,fp);
//   fwrite (&ny,4,1,fp);
//   fwrite (&nz,4,1,fp);
//   fwrite (&bound,4,1,fp);

//   // Write floating-point field
//   bound = 4*nx*ny*nz;
//   fwrite (&bound,4,1,fp);
//   fwrite (buffer,4,nx*ny*nz,fp);
//   fwrite (&bound,4,1,fp);

//   fclose (fp);
// }
