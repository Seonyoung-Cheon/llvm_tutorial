#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"

#include "InsertIncFunction.h"

bool InsertIncFunction::runOnModule(Module &M) {
  LLVMContext& Context = M.getContext();

  FunctionType *addFuncType = FunctionType::get(Type::getInt32Ty(Context), Type::getInt32Ty(Context), false);
  Function *addFun = Function::Create(addFuncType, GlobalValue::ExternalLinkage, "addTen", &M);
  Constant *Ten = ConstantInt::get(Type::getInt32Ty(Context), 10);


  auto args = addFun->arg_begin();
  Value *arg1 = &(*args);
  BasicBlock *entry = BasicBlock::Create(Context, "entry", addFun);
  IRBuilder<> Builder(entry);
  AllocaInst* alloc = Builder.CreateAlloca(Type::getInt32Ty(Context), nullptr);
  StoreInst* str = Builder.CreateStore(args, alloc);
  LoadInst* ld = Builder.CreateLoad(Type::getInt32Ty(Context), alloc);
  auto *result = Builder.CreateAdd(ld, Ten);
  Builder.CreateRet(result);

  for(Function &F : M) {
    for(BasicBlock &BB : F) {
      for(Instruction &I : BB) {
        if(ReturnInst* RI = dyn_cast<ReturnInst>(&I)){
          if( F.getName() != "addTen"){
            Builder.SetInsertPoint(RI);
            CallInst* add10 = Builder.CreateCall(addFun, RI->getOperand(0));
            RI->setOperand(0, add10);
          }
        }
      }
    }
  }

  return true;
}

void InsertIncFunction::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.setPreservesAll();
}

char InsertIncFunction::ID = 0;
static RegisterPass<InsertIncFunction> X("insert-inc-fun", "Increasing func Pass ");
