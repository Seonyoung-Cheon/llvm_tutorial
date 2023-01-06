#ifndef LLVM_TUTORIAL_OPTIMIZATION_INST_COUNT_H
#define LLVM_TUTORIAL_OPTIMIZATION_INST_COUNT_H

#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"

using namespace llvm;

namespace {
  struct InstCount : public ModulePass {
    static char ID; // Pass identification, replacement for typeid
    InstCount() : ModulePass(ID) {}

    bool runOnModule(Module &M) override;

    void getAnalysisUsage(AnalysisUsage &AU) const override;
  };
}

#endif
