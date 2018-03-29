#include "graphical_model.h"
#include "visitors/standard_visitor.hxx"
#include "LP_external_interface.hxx"
#include "solver.hxx"
#include "combiLP.hxx"
#include "hdf5_routines.hxx"
#include "gurobi_interface.hxx"

using namespace LP_MP;

int main(int argc, char** argv)
{
  try {
    using solver_type = Solver<FMC_SRMP,LP_external_solver<DD_ILP::gurobi_interface,LP>,StandardVisitor>;
    std::vector<std::string> options = { 
      {""},
      {"-i"}, {"combiLP.h5"}
    };
    solver_type solver(options);
    solver.ReadProblem(LP_MP::ParseOpenGM<solver_type>);
    solver.GetLP().solve();
  } catch (GRBException ex) {
    std::cout << "Exception caught: " << ex.getErrorCode() << std::endl << ex.getMessage() << std::endl;
  }
}
