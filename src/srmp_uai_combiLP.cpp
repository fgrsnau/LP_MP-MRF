
#include "graphical_model.h"
#include "combiLP.hxx"
#include "gurobi_interface.hxx"
#include "visitors/standard_visitor.hxx"

using namespace LP_MP;
int main(int argc, char** argv) {
  using BaseSolver = Solver<combiLP<DD_ILP::gurobi_interface, LP<FMC_SRMP>>, StandardVisitor>;
  MpRoundingSolver<BaseSolver> solver(argc, argv);
  solver.ReadProblem(UaiMrfInput::ParseProblem<BaseSolver>);
  return solver.Solve();
}