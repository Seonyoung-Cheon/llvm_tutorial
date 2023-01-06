#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "DynamicCallCount.h"

bool DynamicCallCount::runOnModule(Module &M) {
  LLVMContext& Context = M.getContext();
  /* FunctionType *printResType = FunctionType::get(Type::getVoidTy(Context), Type::getVoidTy(Context)); */
  FunctionCallee cntCall = M.getOrInsertFunction("countCall", Type::getVoidTy(Context));
  FunctionCallee printRes = M.getOrInsertFunction("printResult", Type::getVoidTy(Context));

  std::vector<Value *> Args;
  for(Function &F : M){
    for(BasicBlock &BB : F){
      for(Instruction &I : BB){
        if(CallInst* CI = dyn_cast<CallInst>(&I)){
          IRBuilder<> builder(CI);
          builder.CreateCall(cntCall, Args);
          /* CallInst::Create(cntCall, Args, "", CI); */

          if(ReturnInst* RI = dyn_cast<ReturnInst>(&I)){
            IRBuilder<> builder(RI);
            builder.CreateCall(printRes, Args);
            /* CallInst::Create(printRes, Args, "", RI); */
          }
        }
      }
    }
  }
  return false;
}

void DynamicCallCount::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char DynamicCallCount::ID = 0;
static RegisterPass<DynamicCallCount> Y("dyn-call-count", "DynamicCallCount Pass ");
