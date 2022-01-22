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
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Target/TargetRegisterInfo.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  struct TOYPreRegAlloc : public MachineFunctionPass {

  public:
    static char ID;   // Pass identification, replacement for typeid

    TOYPreRegAlloc() : MachineFunctionPass(ID) {}

    bool peepholeOpt(MachineFunction &MF);
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

bool TOYPreRegAlloc::peepholeOpt(MachineFunction &MF) {
  bool Changed = false;

  MachineRegisterInfo *MRI = &MF.getRegInfo();

  for (MachineFunction::iterator MFI = MF.begin(), MFE = MF.end(); MFI != MFE; MFI++) {
    for (MachineBasicBlock::iterator MBBI = MFI->begin(), MBBE = MFI->end(); MBBI != MBBE;) {
      MachineInstr *MI = &*MBBI;
      MBBI++;
      unsigned int Opcode = MI->getOpcode();

      switch (Opcode) {
      case TOY::MOVi: {
          int64_t Val = MI->getOperand(1).getImm();
          if (Val == 0) {
            unsigned int Reg = MI->getOperand(0).getReg();
            if (TargetRegisterInfo::isVirtualRegister(Reg)) {
              for (MachineRegisterInfo::use_nodbg_iterator UI = MRI->use_nodbg_begin(Reg), UE = MRI->use_nodbg_end(); UI != UE;) {
                MachineOperand &MO = UI.getOperand();
                ++UI;
                MO.setReg(TOY::ZERO);
                Changed = true;
              }

              if (MRI->use_nodbg_empty(Reg))
                  MI->eraseFromParent();
            }
          }
        }
        break;
      default: break;
      }
    }
  }
  return Changed;
}

bool TOYPreRegAlloc::runOnMachineFunction(MachineFunction &MF) {
  DEBUG(dbgs() << "********* TOY PreRegAlloc *********\n");

  bool Changed = false;

  Changed |= peepholeOpt(MF);

  return Changed;
}
