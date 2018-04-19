
#include "graphical_model.h"
#include "visitors/standard_visitor.hxx"
#include "LP_FWMAP.hxx"
#include "hdf5_routines.hxx"

using namespace LP_MP;
int main(int argc, char** argv) {
  using BaseSolver = Solver<LP_tree_FWMAP, StandardVisitor>;
  MpRoundingSolver<BaseSolver> solver(argc, argv);
  solver.ReadProblem(ParseOpenGM_DD<BaseSolver>);
  return solver.Solve();
}