
#include "graphical_model.h"
#include "visitors/standard_visitor.hxx"
#include "hdf5_routines.hxx"

using namespace LP_MP;
int main(int argc, char** argv) {
MpRoundingSolver<Solver<FMC_SRMP_T,LP,StandardTighteningVisitor>> solver(argc,argv);
solver.ReadProblem(ParseOpenGM<Solver<FMC_SRMP_T,LP,StandardTighteningVisitor>>);
bool result = solver.Solve();
WriteGM("reparametrized.h5", solver.template GetProblemConstructor<0>());
return result;
}
