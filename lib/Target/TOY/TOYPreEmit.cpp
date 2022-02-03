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
    bool optimizeLoopBranch(MachineFunction &MF);
    bool removeFallThroughBranch(MachineFunction &MF);
    bool localValueNumbering(MachineFunction &MF);

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
  case TOY::CMPLE: return std::pair<bool, unsigned>(true, TOY::CMPGT);
  default:         return std::pair<bool, unsigned>(false, 0);
  }
}

bool TOYPreEmit::optimizeLoopBranch(MachineFunction &MF) {
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

    if ((BB2OrderMap[MBB] > BB2OrderMap[TBB] &&
         BB2OrderMap[MBB] > BB2OrderMap[FBB] &&
         BB2OrderMap[FBB] > BB2OrderMap[TBB]) ||
        (BB2OrderMap[MBB] < BB2OrderMap[TBB] &&
         BB2OrderMap[MBB] > BB2OrderMap[FBB])) {
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

bool TOYPreEmit::removeFallThroughBranch(MachineFunction &MF) {
  bool Changed = false;

  std::map<MachineBasicBlock *, unsigned> BB2OrderMap;
  unsigned Order = 0;
  for (MachineFunction::iterator MFI = MF.begin(), MFE = MF.end(); MFI != MFE; MFI++) {
    MachineBasicBlock *BB = MFI;
    BB2OrderMap[BB] = Order;
    Order++;
  }

  for (MachineFunction::iterator MBI = MF.begin(); MBI != MF.end(); MBI++) {
    MachineBasicBlock *MBB = MBI;

    // If MBB has only one successor and MBB falls through to its sucessor,
    // then the BR branching to its successor can be removed.
    MachineBasicBlock::iterator I = MBI->end();
    if (I == MBB->begin())
        continue;

    I--;
    MachineInstr *LastInst = I;
    if (LastInst->getOpcode() == TOY::BR) {
        MachineBasicBlock *Target = LastInst->getOperand(0).getMBB();
        if (BB2OrderMap[Target] == BB2OrderMap[MBB] + 1) {
            LastInst->eraseFromParent();
            Changed = true;
        }
    }
  }

  return Changed;
}

namespace {

struct Val {
  unsigned int Op;
  std::vector<unsigned int> Nums;
  Val(unsigned int Op, std::vector<unsigned int> Nums) : Op(Op), Nums(Nums) {}
};

}

static bool isLvnCandidate(MachineInstr *MI) {
  switch (MI->getOpcode()) {
  case TOY::ADDri:
  case TOY::ADDrr:
  case TOY::SUBri:
  case TOY::MOVi: return true;
  default: return false;
  }
}

bool TOYPreEmit::localValueNumbering(MachineFunction &MF) {

  bool Changed = false;

  for (MachineFunction::iterator MFI = MF.begin(); MFI != MF.end(); MFI++) {
    unsigned int Num = 0;
    std::map<unsigned int, unsigned int> Reg2NumMap;
    std::map<int64_t, unsigned int> Imm2NumMap;
    std::map<unsigned int, Val *> Num2ValMap;
    for (MachineBasicBlock::iterator MBBI = MFI->begin(), MBBE = MFI->end(); MBBI != MBBE;) {
      MachineInstr *MI = &*MBBI;
      MBBI++;

      if (MI->getOpcode() == TOY::BR || MI->getOpcode() == TOY::BRCC)
        continue;

      std::vector<unsigned int> Nums;
      unsigned int DefReg = 0;
      for (unsigned int i = 0; i < MI->getNumOperands(); i++) {
        MachineOperand &Operand = MI->getOperand(i);
        if (Operand.isReg()) {
          unsigned int Reg = Operand.getReg();
          if (Operand.isDef()) {
            if (DefReg != 0)
              llvm_unreachable("There should be only one defined reg!");
            DefReg = Reg;
            continue;
          }

          if (Reg2NumMap.find(Reg) != Reg2NumMap.end()) {
            Nums.push_back(Reg2NumMap[Reg]);
          } else {
            Reg2NumMap[Reg] = Num;
            Num2ValMap[Num] = NULL;
            Nums.push_back(Num);
            Num++;
          }
        } else if (Operand.isImm()) {
          int64_t Imm = Operand.getImm();
          if (Imm2NumMap.find(Imm) != Imm2NumMap.end()) {
            Nums.push_back(Imm2NumMap[Imm]);
          } else {
            Imm2NumMap[Imm] = Num;
            Num2ValMap[Num] = NULL;
            Nums.push_back(Num);
            Num++;
          }
        } else {
          llvm_unreachable("The MO should be reg or imm!");
        }
      }

      if (DefReg != 0) {
        if (Reg2NumMap.find(DefReg) != Reg2NumMap.end()) {
          unsigned int Num = Reg2NumMap[DefReg];
          Val *Val = Num2ValMap[Num];
          if (Val != NULL &&
              Val->Nums.size() == Nums.size() &&
              std::equal(Val->Nums.begin(), Val->Nums.end(), Nums.begin())) {
            if (isLvnCandidate(MI)) {
              MI->eraseFromParent();
              Changed = true;
              continue;
            }
          }
        }

        Reg2NumMap[DefReg] = Num;
        Num2ValMap[Num] = new Val(MI->getOpcode(), Nums);
        Num++;
      }
    }

    std::map<unsigned int, Val *>::iterator Num2ValIter;
    for (Num2ValIter = Num2ValMap.begin(); Num2ValIter != Num2ValMap.end(); Num2ValIter++) {
      delete Num2ValIter->second;
    }
  }

  return Changed;
}

bool TOYPreEmit::runOnMachineFunction(MachineFunction &MF) {
  DEBUG(dbgs() << "********* TOY PreRmit *********\n");

  TII = MF.getTarget().getInstrInfo();

  bool Changed = false;
  Changed |= optimizeLoopBranch(MF);
  /*
     After optmizing branch instructions in loop, a BB may has a BR instrution
     branching to its fall through BB.
  */
  Changed |= removeFallThroughBranch(MF);
  Changed |= localValueNumbering(MF);

  return Changed;
}
