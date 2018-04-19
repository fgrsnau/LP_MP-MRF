
#include "graphical_model.h"
#include "visitors/standard_visitor.hxx"
#include "LP_FWMAP.hxx"

using namespace LP_MP;
int main(int argc, char** argv) {
  using BaseSolver = Solver<LP_tree_FWMAP, StandardVisitor>;
  MpRoundingSolver<BaseSolver> solver(argc, argv);
  solver.ReadProblem(UaiMrfInput::ParseProblemDD<BaseSolver>);
  return solver.Solve();
}