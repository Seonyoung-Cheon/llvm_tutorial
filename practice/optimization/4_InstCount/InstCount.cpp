#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/Instructions.h"
#include "InstCount.h"

bool InstCount::runOnModule(Module &M) {
  for(Function &F : M){
    dbgs() << F.getName() << " Inst Count : ";
    int cnt = 0;
    for(BasicBlock &BB : F){
      for(Instruction &I : BB){
        cnt++;
      }
    }
    dbgs() << cnt << '\n';
  }
  return false;
}

void InstCount::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char InstCount::ID = 0;
static RegisterPass<InstCount> Y("inst-count", "InstCount Pass ");
