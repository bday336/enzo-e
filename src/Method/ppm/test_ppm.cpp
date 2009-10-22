/** 
 *********************************************************************
 *
 * @file      test_hydro.cpp
 * @brief     Program implementing unit tests for hydrodynamics
 * @author    James Bordner
 * @date      Fri Mar  7 17:11:14 PST 2008
 *
 *********************************************************************
 */

#include "string.h"
#include "cello_hydro.h"
#include "test_ppm.h"

void initialize_hydro ();
void initialize_ppm (enum type_problem);

const char * file_root = "image";

int main(int argc, char ** argv)
{
  enum type_problem problem_type;
  int n      = 394;
  int cycles = 20000;
  int cycle_dump_frequency = 10;

  if (argc < 2) {
    printf ("Usage: %s [color|image|implosion|implosion3\n",argv[0]);
    exit(1);
  } else {
    if (strcmp(argv[1],"color")) {
      problem_type = problem_color;
    } else if (strcmp(argv[1],"image")) {
      problem_type = problem_image;
    } else if (strcmp(argv[1],"implosion")) {
      problem_type = problem_implosion;
    } else if (strcmp(argv[1],"implosion3")) {
      problem_type = problem_implosion3;
    } else {
      printf ("Usage: %s [color|image|implosion|implosion3\n",argv[0]);
      exit(1);
    }
    if (argc>=3)  {
      n = atoi(argv[2]);
      if (n < 1 || 10000 < n) {
	printf ("Illegal size %d: resetting to 400\n",n);
	n = 400;
      }
    }
    if (argc>=4)  {
      cycles = atoi(argv[3]);
      if (cycles < 1 || 10000000 < cycles) {
	printf ("Illegal cycles %d: resetting to 20000\n",n);
	cycles = 20000;
      }
    }
    if (argc>=5)  {
      cycle_dump_frequency = atoi(argv[4]);
      if (cycle_dump_frequency < 0) {
	printf ("Illegal cycle_dump_frequency %d: resetting to 10\n",n);
	cycle_dump_frequency = 10;
      }
    }
  }


  initialize_hydro ();

  initialize_ppm(problem_type);

  float dt;

  int   cycle;
  float time;

  for (cycle = 0, time = 0.0;
       (cycle < cycle_stop) && (time < time_stop);
       ++cycle, time += dt) {

    dt =  min(ComputeTimeStep(), time_stop - time);

    printf ("cycle = %6d time = %6f dt = %6f\n",cycle,time,dt);

    SetExternalBoundaryValues();

    if ((cycle % cycle_dump_frequency) == 0) {
      data_dump(file_root,cycle);
    }

    SolveHydroEquations(cycle, dt);

  }
  if ((cycle % cycle_dump_frequency) == 0) {
    SetExternalBoundaryValues();
    data_dump(file_root,cycle);
  }
}
