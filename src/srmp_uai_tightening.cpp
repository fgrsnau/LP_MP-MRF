
#include "graphical_model.h"
#include "visitors/standard_visitor.hxx"

using namespace LP_MP;
int main(int argc, char** argv) {
  using BaseSolver = Solver<LP<FMC_SRMP_T>, StandardTighteningVisitor>;
  MpRoundingSolver<BaseSolver> solver(argc, argv);
  solver.ReadProblem(UaiMrfInput::ParseProblem<BaseSolver>);
  return solver.Solve();
}