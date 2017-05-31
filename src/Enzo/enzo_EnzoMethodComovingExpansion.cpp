// See LICENSE_CELLO file for license and copyright information

/// @file     enzo_EnzoMethodComovingExpansion.cpp
/// @author   Britton Smith (bds006@ucsd.edu)
/// @date     Wed May 24 12:25:56 PDT 2017
/// @brief    Implements comoving expansion class

#include "cello.hpp"
#include "enzo.hpp"

//----------------------------------------------------------------------

EnzoMethodComovingExpansion::EnzoMethodComovingExpansion
(
 const FieldDescr * field_descr,
 EnzoConfig * enzo_config
) 
  : Method(),
    comoving_coordinates_(enzo_config->physics_cosmology)
{
  // do nothing!
}

//----------------------------------------------------------------------

void EnzoMethodComovingExpansion::compute ( Block * block) throw()
{

  EnzoBlock * enzo_block = static_cast<EnzoBlock*> (block);
  Field field = enzo_block->data()->field();

  /* Only do this if
     1. this is a leaf block
     2. we are using comoving coordinates
     3. baryon fields are present.
  */
  if (!(block->is_leaf() &&
        comoving_coordinates_ &&
        field.field_count() > 0))
    {
      block->compute_done();
    }

  EnzoPhysicsCosmology * cosmology = (EnzoPhysicsCosmology * )
    block->simulation()->problem()->physics("cosmology");

  ASSERT ("EnzoMethodComovingExpansion::compute()",
	  "comoving_coordinates enabled but missing EnzoPhysicsCosmology",
	  ! (comoving_coordinates_ && (cosmology != NULL)) );

  /* Compute adot/a at time = t-1/2dt (time-centered). */

  enzo_float a, dadt, compute_time;
  int has_history = field.history_time(1) > 0.;

  if (has_history) {
    compute_time = 0.5 * (field.history_time(0) +
                          field.history_time(1));
  }
  else {
    compute_time = field.history_time(0);
  }

  cosmology->compute_expansion_factor(&a, &dadt, compute_time);
  enzo_float Coefficient = block->dt()*dadt/a;

  /* Determine the size of the grids. */

  int i, dim, size = 1;
  int rank = enzo_block->rank();
  for (dim = 0; dim < rank; dim++)
    size *= enzo_block->GridDimension[dim];

  /* If we can, compute the pressure at the mid-point.
     We can, because we will always have an old baryon field now. */
  const int in = cello::index_static();
  enzo_float * pressure = new enzo_float[size];
  int rval;

  if (EnzoBlock::DualEnergyFormalism[in]) {
    rval = enzo_block->ComputePressureDualEnergyFormalism(
        compute_time, pressure, comoving_coordinates_);
  }
  else{
    rval = enzo_block->ComputePressure(
        compute_time, pressure, comoving_coordinates_);
  }
  if (rval == ENZO_FAIL) {
    fprintf(stderr,
            "Error in ComputePressureDualEnergyFormalism or ComputePressure.\n");
    exit(ENZO_FAIL);
  }

  // hard-code hydromethod for PPM for now
  int HydroMethod = 0;

  // hard-code CR method to off
  int CRModel = 0;
  enzo_float * cr_field_0 = NULL;
  enzo_float * cr_field_1 = NULL;

  /* Get the necessary fields.
     field.values(<field_name>, 0) is the field at the current time.
     field.values(<field_name>, 1) is the field at the previous time.
  */

  enzo_float * density_0         = (enzo_float *) field.values("density", 0);
  enzo_float * total_energy_0    = (enzo_float *) field.values("total_energy", 0);
  enzo_float * internal_energy_0 = (enzo_float *) field.values("internal_energy", 0);
  enzo_float * density_1, * total_energy_1, * internal_energy_1;

  density_1 = has_history ?
    (enzo_float *) field.values("density", 1) : density_0;
  total_energy_1    = has_history ?
    (enzo_float *) field.values("total_energy", 1) : total_energy_0;
  internal_energy_1 = has_history ?
    (enzo_float *) field.values("internal_energy", 1): internal_energy_0;

  enzo_float * velocity_x_0, * velocity_y_0, * velocity_z_0,
    * velocity_x_1, * velocity_y_1, * velocity_z_1 = NULL;

  velocity_x_0 = (enzo_float *) field.values("velocity_x", 0);
  velocity_x_1 = has_history ?
    (enzo_float *) field.values("velocity_x", 1) : velocity_x_0;
  if (rank >= 2) {
    velocity_y_0 = (enzo_float *) field.values("velocity_y", 0);
    velocity_y_1 = has_history ?
      (enzo_float *) field.values("velocity_y", 1) : velocity_y_0;
  }
  if (rank >= 3) {
    velocity_z_0 = (enzo_float *) field.values("velocity_z", 0);
    velocity_z_1 = has_history ?
      (enzo_float *) field.values("velocity_z", 1) : velocity_z_0;
  }

  /* Call fortran routine to do the real work. */

  FORTRAN_NAME(expand_terms)(
      &rank, &size, &EnzoBlock::DualEnergyFormalism[in], &Coefficient,
      (int*) &HydroMethod, &EnzoBlock::Gamma[in],
      pressure,
      density_0, total_energy_0, internal_energy_0,
      velocity_x_0, velocity_y_0, velocity_z_0,
      density_1, total_energy_1, internal_energy_1,
      velocity_x_1, velocity_y_1, velocity_z_1,
      &CRModel, cr_field_0, cr_field_1);

  block->compute_done();

}

//----------------------------------------------------------------------

double EnzoMethodComovingExpansion::timestep( Block * block ) const throw()
{

  enzo_float dtExpansion = ENZO_HUGE_VAL;

  if (!comoving_coordinates_)
    return (double) dtExpansion;

  EnzoPhysicsCosmology * cosmology = (EnzoPhysicsCosmology * )
    block->simulation()->problem()->physics("cosmology");

  ASSERT ("EnzoMethodComovingExpansion::timestep()",
	  "comoving_coordinates enabled but missing EnzoPhysicsCosmology",
	  ! (comoving_coordinates_ && (cosmology != NULL)) );

  EnzoBlock * enzo_block = static_cast<EnzoBlock*> (block);

  cosmology->compute_expansion_timestep(&dtExpansion,
                                        (enzo_float) enzo_block->time());

  return (double) dtExpansion;

}

//----------------------------------------------------------------------

void EnzoMethodComovingExpansion::pup (PUP::er &p)
{
  TRACEPUP;
  // NOTE: change this function whenever attributes change
}

//======================================================================
