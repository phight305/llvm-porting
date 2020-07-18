//===-- TOYTargetMachine.cpp - Define TargetMachine for Sparc -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "TOYTargetMachine.h"
#include "TOY.h"
#include "llvm/PassManager.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

extern "C" void LLVMInitializeTOYTarget() {
  // Register the target.
  RegisterTargetMachine<TOYTargetMachine> X(TheTOYTarget);
}

TOYTargetMachine::TOYTargetMachine(const Target &T, StringRef TT, StringRef
                                   CPU, StringRef FS, const TargetOptions &Options,
                                   Reloc::Model RM, CodeModel::Model CM,
                                   CodeGenOpt::Level OL)
    : LLVMTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL),
      Subtarget(TT, CPU, FS),
      DL(Subtarget.getDataLayout()),
      TLInfo(*this) {}
      // InstrInfo(Subtarget),
      // TLInfo(*this), FrameLowering(Subtarget)

namespace {
/// TOY Code Generator Pass Configuration Options.
class TOYPassConfig : public TargetPassConfig {
public:
  TOYPassConfig(TOYTargetMachine *TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  TOYTargetMachine &getTOYTargetMachine() const {
      return getTM<TOYTargetMachine>();
  }

  virtual bool addInstSelector();
  virtual bool addPreEmitPass();
};
} // namespace

TargetPassConfig *TOYTargetMachine::createPassConfig(PassManagerBase &PM) {
    return new TOYPassConfig(this, PM);
}


bool TOYPassConfig::addInstSelector() {
    addPass(createTOYISelDag(getTOYTargetMachine()));
    return false;
}

/// addPreEmitPass - This pass may be implemented by targets that want to run
/// passes immediately before machine code is emitted.  This should return
/// true if -print-machineinstrs should print out the code after the passes.
bool TOYPassConfig::addPreEmitPass(){
    return true;
}
