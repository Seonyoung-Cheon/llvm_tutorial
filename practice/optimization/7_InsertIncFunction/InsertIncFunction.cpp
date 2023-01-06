#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"

#include "InsertIncFunction.h"

bool InsertIncFunction::runOnModule(Module &M) {
  LLVMContext& Context = M.getContext();

  FunctionType *addFuncType = FunctionType::get(Type::getInt32Ty(Context), Type::getInt32Ty(Context), false);
  Function *addFun = Function::Create(addFuncType, GlobalValue::ExternalLinkage, "addTen", &M);
  Constant *Ten = ConstantInt::get(Type::getInt32Ty(Context), 10);
  Constant *One = ConstantInt::get(Type::getInt32Ty(Context), 1);


  auto args = addFun->arg_begin();
  Value *arg1 = &(*args);
  BasicBlock *entry = BasicBlock::Create(Context, "entry", addFun);
  IRBuilder<> Builder(entry);
  AllocaInst* alloc = Builder.CreateAlloca(Type::getInt32Ty(Context), nullptr, "a.addr");
  StoreInst* str = Builder.CreateStore(args, alloc);
  LoadInst* ld = Builder.CreateLoad(Type::getInt32Ty(Context), alloc);
  auto *result = Builder.CreateAdd(arg1, Ten, "add");
  Builder.CreateRet(result);

  for(Function &F : M) {
    for(BasicBlock &BB : F) {
      Builder.SetInsertPoint(BB.getTerminator());
      CallInst* add10 = Builder.CreateCall(addFun, One);
    }
  }

  return false;
}

void InsertIncFunction::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char InsertIncFunction::ID = 0;
static RegisterPass<InsertIncFunction> X("insert-inc-fun", "Increasing func Pass ");
