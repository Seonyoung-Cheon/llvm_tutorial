#ifndef LLVM_TUTORIAL_OPTIMIZATION_EXAMPLES_H
#define LLVM_TUTORIAL_OPTIMIZATION_EXAMPLES_H

#include "llvm/IR/Module.h"
#include "llvm/Pass.h"

using namespace llvm;

namespace {
  struct Examples : public ModulePass {
    static char ID; // Pass identification, replacement for typeid
    Examples() : ModulePass(ID) {}

    bool runOnModule(Module &M) override;

    void getAnalysisUsage(AnalysisUsage &AU) const override;
  };
}

#endif
