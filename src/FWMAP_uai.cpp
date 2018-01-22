
#include "graphical_model.h"
#include "visitors/standard_visitor.hxx"
#include "LP_FWMAP.hxx"

using namespace LP_MP;
int main(int argc, char** argv) {
MpRoundingSolver<Solver<FMC_SRMP,LP_tree_FWMAP,StandardVisitor>> solver(argc,argv);
solver.ReadProblem(UaiMrfInput::ParseProblemDD<Solver<FMC_SRMP,LP_tree_FWMAP,StandardVisitor>>);
return solver.Solve();
}