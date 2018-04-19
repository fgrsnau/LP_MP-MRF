
#include "graphical_model.h"
#include "visitors/standard_visitor.hxx"
#include "hdf5_routines.hxx"

using namespace LP_MP;
int main(int argc, char** argv) {
  using BaseSolver = Solver<LP<FMC_SRMP_T>, StandardTighteningVisitor>;
  MpRoundingSolver<BaseSolver> solver(argc, argv);
  solver.ReadProblem(ParseOpenGM<BaseSolver>);
  return solver.Solve();
}