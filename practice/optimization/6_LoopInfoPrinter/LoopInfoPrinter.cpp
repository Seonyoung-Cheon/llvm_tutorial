#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/Instructions.h"

#include "LoopInfoPrinter.h"

bool LoopInfoPrinter::runOnFunction(Function &F) {
  LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
  dbgs() << "Function Name : " << F.getName() << '\n';
  int count = 0;
  for(BasicBlock &BB : F){
    bool isLoop = LI.getLoopFor(&BB);
    if(LI.isLoopHeader(&BB)) {
      dbgs() << "Loop Depth in BB : " << LI.getLoopDepth(&BB) <<'\n';
      count++;
    }
  }
  dbgs() << " Number of Loop : " << count <<'\n';
  return false;
}

void LoopInfoPrinter::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.addRequired<LoopInfoWrapperPass>();
  AU.setPreservesAll();
}

char LoopInfoPrinter::ID = 0;
static RegisterPass<LoopInfoPrinter> Y("loop-info-printer", "LoopInfoPrinter Pass ");
