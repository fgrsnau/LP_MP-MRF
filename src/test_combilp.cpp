#include <iostream>
#include <vector>
#include <unordered_set>

#include "LP_MP.h"
#include "graphical_model.h"
#include "visitors/standard_visitor.hxx"
#include "hdf5_routines.hxx"
#include "partial_external_solver.hxx"
#include "gurobi_interface.hxx"
#include "combiLP.hxx"

using namespace LP_MP;
using namespace DD_ILP;

int main(int argc, char **argv)
{
  const std::vector<std::string> parameters {
    {""},
    {"-i"}, {"/home/stefan/models/private/worm/cnd1threeL1_1213061.h5"},
    {"--maxIter"}, {"20"}
    //{"--standardReparametrization"}, {"damped_uniform"},
    //{"--roundingReparametrization"}, {"damped_uniform"}
  };

  using SolverType = MpRoundingSolver<Solver<FMC_SRMP, combiLP<gurobi_interface, LP>, StandardVisitor>>;
  SolverType solver(parameters);
  solver.ReadProblem(ParseOpenGM<SolverType::SolverType>);
  solver.Solve();

#if 0
  LP &lp = solver.GetLP();
  INDEX count = 0;
  for (INDEX i = 0; i < lp.GetNumberOfMessages(); ++i) {
    auto *m = lp.GetMessage(i);
    if (!m->CheckPrimalConsistency())
      ++count;
  }
  std::cout << "Inconsistent messages: " << count << " / " << lp.GetNumberOfMessages() << " (" << (100.0f * count / lp.GetNumberOfMessages()) << "%)" << std::endl;

  std::unordered_set<INDEX> mask {85, 87, 114, 191, 220, 225, 231, 232, 251, 332, 335, 360, 374, 375, 382, 383, 386, 389, 523, 529, 551, 552};
  auto is_in_mask = [&mask](int v) {
    return std::find(mask.begin(), mask.end(), v) != mask.end();
  };

  auto &mrf = solver.template GetProblemConstructor<0>();
  partial_external_solver<gurobi_interface> external_solver;

  for (auto x : mask) {
    auto *factor_container = mrf.GetUnaryFactor(x);
    auto *factor = factor_container->GetFactor();
    external_solver.AddFactor(factor_container);
  }

  for (INDEX i = 0; i < mrf.GetNumberOfPairwiseFactors(); ++i) {
    auto variables = mrf.GetPairwiseVariables(i);
    if (is_in_mask(variables[0]) && is_in_mask(variables[1])) {
      auto *factor_container = mrf.GetPairwiseFactor(i);
      auto *factor = factor_container->GetFactor();
      external_solver.AddFactor(factor_container);
    }
  }

  external_solver.AddMessages(solver.GetLP());
  external_solver.solve();
#endif
}
