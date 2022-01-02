//===-------------------- TOYPreEmit.cpp ----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------===//

#define DEBUG_TYPE "pre-emit"
#include <map>
#include <utility>
#include "TOY.h"
#include "TOYTargetMachine.h"
#include "TOYInstrInfo.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  struct TOYPreEmit : public MachineFunctionPass {

    const TargetInstrInfo *TII;

  public:
    static char ID;   // Pass identification, replacement for typeid

    TOYPreEmit() : MachineFunctionPass(ID) {}

    virtual bool runOnMachineFunction(MachineFunction &MF);
    bool optimizeNestedLoop(MachineFunction &MF);

    const char *getPassName() const { return "TOY PreRmit"; }

    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      MachineFunctionPass::getAnalysisUsage(AU);
    }

  };

  char TOYPreEmit::ID = 0;

} // end anonymous namespace

/// createTOYPreEmit - Factory for creating
/// the hardware loop phase.
FunctionPass *llvm::createTOYPreEmit() {
  return new TOYPreEmit();
}

static std::pair<bool, unsigned> getReversedCmp(unsigned Op) {
  switch (Op) {
  case TOY::CMPGE: return std::pair<bool, unsigned>(true, TOY::CMPLT);
  default:         return std::pair<bool, unsigned>(false, 0);
  }
}

bool TOYPreEmit::optimizeNestedLoop(MachineFunction &MF) {
  bool Changed = false;

  std::map<MachineBasicBlock *, unsigned> BB2OrderMap;
  unsigned Order = 0;
  for (MachineFunction::iterator MFI = MF.begin(), MFE = MF.end(); MFI != MFE; MFI++) {
    MachineBasicBlock *BB = MFI;
    BB2OrderMap[BB] = Order;
    Order++;
  }

  for (MachineFunction::iterator MBI = MF.begin(); MBI != MF.end(); MBI++) {
    MachineBasicBlock::iterator I = MBI->end();
    MachineBasicBlock *MBB = MBI;
    I--;
    if (I == MBB->begin())
      continue;

    MachineInstr *LastInst = I;
    if (LastInst->getOpcode() != TOY::BR)
      continue;

    I--;
    if (I == MBB->begin())
      continue;

    MachineInstr *SecondLastInst = I;
    if (SecondLastInst->getOpcode() != TOY::BRCC)
      continue;

    I--;
    if (I == MBB->begin())
      continue;

    MachineBasicBlock *TBB = SecondLastInst->getOperand(0).getMBB();
    MachineBasicBlock *FBB = LastInst->getOperand(0).getMBB();

    if (BB2OrderMap[MBB] > BB2OrderMap[TBB] &&
        BB2OrderMap[MBB] > BB2OrderMap[FBB] &&
        BB2OrderMap[FBB] > BB2OrderMap[TBB]) {
      MachineInstr *ThirdLastInst = I;
      std::pair<bool, unsigned> Reverse = getReversedCmp(ThirdLastInst->getOpcode());
      if (Reverse.first) {
        ThirdLastInst->setDesc(TII->get(Reverse.second));
        SecondLastInst->getOperand(0).setMBB(FBB);
        LastInst->getOperand(0).setMBB(TBB);
        Changed = true;
      }
    }
  }

  return Changed;
}

bool TOYPreEmit::runOnMachineFunction(MachineFunction &MF) {
  DEBUG(dbgs() << "********* TOY PreRmit *********\n");

  TII = MF.getTarget().getInstrInfo();

  bool Changed = false;
  Changed |= optimizeNestedLoop(MF);

  return Changed;
}
