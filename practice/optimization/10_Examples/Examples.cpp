#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "Examples.h"

bool Examples::runOnModule(Module &M) {

  /* IRBuilder Check Basic Block End Example */
  /*
     LLVMContext& Context = M.getContext();
     FunctionCallee MarkBBEnd = M.getOrInsertFunction("BBEnd", Type::getVoidTy(Context));
     std::vector<Value *> args;
     for(Function &F : M){
     for(BasicBlock &BB : F){
     IRBuilder<> Builder(BB.getTerminator());
     CallInst *newCallInst = Builder.CreateCall(MarkBBEnd, args);
     }
     }
     */

  /* How to insert arguments */
  /*  LLVMContext& Context = M.getContext();
      std::vector<Value *> args;
      Constant *One = ConstantInt::get(Type::getInt32Ty(Context), 1);
      args.push_back(One);
      for(Function &F : M){
      for(BasicBlock &BB : F){
      IRBuilder<> Builder(BB.getTerminator());
      CallInst *newCallInst = Builder.CreateCall(MarkBBEnd, args);
      }
      }
      */

  /* How to make basic block including function */
  LLVMContext& Context = M.getContext();
  FunctionType *MarkBBEndType = FunctionType::get(Type::getInt32Ty(Context), Type::getInt32Ty(Context), false);
  Function *MarkBBEnd = Function::Create(MarkBBEndType, GlobalValue::ExternalLinkage, "MarkBBEnd", &M);

  Argument *arg = MarkBBEnd->getArg(0);
  BasicBlock *entry = BasicBlock::Create(Context, "entry", MarkBBEnd);
  IRBuilder<> Builder(entry);
  Builder.CreateRet(arg);
  for(Function &F : M){
    for(BasicBlock &BB : F){
      IRBuilder<> Builder(BB.getTerminator());
      if(F.getName() != "MarkBBEnd"){
        Constant *One = ConstantInt::get(Type::getInt32Ty(Context), 1);
        CallInst *newCallInst = Builder.CreateCall(MarkBBEnd, One);
      }
    }
  }


  return true;
}

void Examples::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char Examples::ID = 0;
static RegisterPass<Examples> Y("examples", "Examples Pass ");
