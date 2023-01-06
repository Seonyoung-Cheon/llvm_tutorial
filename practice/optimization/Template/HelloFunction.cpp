#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"

#include "HelloFunction.h"

#define DEBUG_TYPE "hello"

bool HelloFunction::runOnFunction(Function &F) {
  dbgs() << F.getName();
  return false;
}

void HelloFunction::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char HelloFunction::ID = 0;
static RegisterPass<HelloFunction> Y("helloFunction", "Hello World Pass ");
