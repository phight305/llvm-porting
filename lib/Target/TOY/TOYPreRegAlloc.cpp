//===-------------------- TOYPreRegAlloc.cpp ----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------===//

#define DEBUG_TYPE "pre-reg-alloc"
#include "TOY.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  struct TOYPreRegAlloc : public MachineFunctionPass {

  public:
    static char ID;   // Pass identification, replacement for typeid

    TOYPreRegAlloc() : MachineFunctionPass(ID) {}

    virtual bool runOnMachineFunction(MachineFunction &MF);

    const char *getPassName() const { return "TOY PreRegAlloc"; }

    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      MachineFunctionPass::getAnalysisUsage(AU);
    }

  };

  char TOYPreRegAlloc::ID = 0;

} // end anonymous namespace

/// createTOYPreRegAlloc - Factory for creating
/// the hardware loop phase.
FunctionPass *llvm::createTOYPreRegAlloc() {
  return new TOYPreRegAlloc();
}

bool TOYPreRegAlloc::runOnMachineFunction(MachineFunction &MF) {
  DEBUG(dbgs() << "********* TOY PreRegAlloc *********\n");

  return false;
}
