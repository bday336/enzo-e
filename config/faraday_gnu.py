import os

is_arch_valid = 1

flags_arch = '-Wall -O3 -g'
flags_link_charm = ' -rdynamic' # required for backtraces

cc  = 'gcc'
f90 = 'gfortran'

flags_prec_single = '-fdefault-real-4 -fdefault-double-8'
flags_prec_double = '-fdefault-real-8 -fdefault-double-8'

libpath_fortran = '.'
libs_fortran    = ['gfortran']

home = os.environ['HOME']

charm_path   = '/usr/local/charm-6.5.1/gnu'
#papi_path    = '/usr/local'
hdf5_inc    = '/usr/include'
hdf5_lib    = '/usr/lib'
png_path     = '/lib/x86_64-linux-gnu'
#grackle_path = home + '/Software/Grackle/src/clib'

