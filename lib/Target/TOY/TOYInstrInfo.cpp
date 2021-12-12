//===-- TOYInstrInfo.cpp - TOY Instruction Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the TOY implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "TOYInstrInfo.h"
#include "TOY.h"
// #include "TOYMachineFunctionInfo.h"
#include "TOYSubtarget.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallVector.h"

#define GET_INSTRINFO_CTOR
#include "TOYGenInstrInfo.inc"

using namespace llvm;

TOYInstrInfo::TOYInstrInfo(TOYSubtarget &ST)
  : TOYGenInstrInfo(0, 0), // FIXME: what do they mean ?
    RI(ST, *this), Subtarget(ST) {
}

/// isLoadFromStackSlot - If the specified machine instruction is a direct
/// load from a stack slot, return the virtual or physical register number of
/// the destination along with the FrameIndex of the loaded stack slot.  If
/// not, return 0.  This predicate must return 0 if the instruction has
/// any side effects other than loading from the stack slot.
unsigned TOYInstrInfo::isLoadFromStackSlot(const MachineInstr *MI,
                                           int &FrameIndex) const {
  switch (MI->getOpcode()) {
  default: break;
  case TOY::LOADrr:
    if (MI->getOperand(1).isFI()) {
      FrameIndex = MI->getOperand(1).getIndex();
      return MI->getOperand(0).getReg();
    }
    break;
  }
  return 0;
}

/// isStoreToStackSlot - If the specified machine instruction is a direct
/// store to a stack slot, return the virtual or physical register number of
/// the source reg along with the FrameIndex of the loaded stack slot.  If
/// not, return 0.  This predicate must return 0 if the instruction has
/// any side effects other than storing to the stack slot.
unsigned TOYInstrInfo::isStoreToStackSlot(const MachineInstr *MI,
                                          int &FrameIndex) const {
  switch (MI->getOpcode()) {
  default: break;
  case TOY::STORErr:
    if (MI->getOperand(1).isFI()) {
      FrameIndex = MI->getOperand(1).getIndex();
      return MI->getOperand(0).getReg();
    }
    break;
  }
  return 0;
}

MachineInstr *
TOYInstrInfo::emitFrameIndexDebugValue(MachineFunction &MF,
                                       int FrameIx,
                                       uint64_t Offset,
                                       const MDNode *MDPtr,
                                       DebugLoc dl) const {
  llvm_unreachable("emitFrameIndexDebugValue not implemented\n");
}


bool TOYInstrInfo::AnalyzeBranch(MachineBasicBlock &MBB,
                                 MachineBasicBlock *&TBB,
                                 MachineBasicBlock *&FBB,
                                 SmallVectorImpl<MachineOperand> &Cond,
                                 bool AllowModify) const {
  return true;
}

unsigned
TOYInstrInfo::InsertBranch(MachineBasicBlock &MBB,MachineBasicBlock *TBB,
                           MachineBasicBlock *FBB,
                           const SmallVectorImpl<MachineOperand> &Cond,
                           DebugLoc DL) const {
  llvm_unreachable("InsertBranch not implemented\n");
}

unsigned TOYInstrInfo::RemoveBranch(MachineBasicBlock &MBB) const {
  llvm_unreachable("RemoveBranch not implemented\n");
}

void TOYInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                               MachineBasicBlock::iterator I, DebugLoc DL,
                               unsigned DestReg, unsigned SrcReg,
                               bool KillSrc) const {
  if (TOY::GRRegsRegClass.contains(DestReg) && TOY::GRRegsRegClass.contains(SrcReg)) {
    BuildMI(MBB, I, DL, get(TOY::ADDri), DestReg).addReg(SrcReg).addImm(0);
    return;
  }
  else {
    llvm_unreachable("COPY with other register classes is not supported");
  }
}

void TOYInstrInfo::
storeRegToStackSlot(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                    unsigned SrcReg, bool isKill, int FI,
                    const TargetRegisterClass *RC,
                    const TargetRegisterInfo *TRI) const {
  DebugLoc DL;
  if (I != MBB.end())
    DL = I->getDebugLoc();
  BuildMI(MBB, I, DL, get(TOY::STORErr)).addReg(SrcReg).addFrameIndex(FI).addReg(TOY::ZERO);
}

void TOYInstrInfo::
loadRegFromStackSlot(MachineBasicBlock &MBB, MachineBasicBlock::iterator I,
                     unsigned DestReg, int FI,
                     const TargetRegisterClass *RC,
                     const TargetRegisterInfo *TRI) const {
  DebugLoc DL;
  if (I != MBB.end())
    DL = I->getDebugLoc();
  BuildMI(MBB, I, DL, get(TOY::LOADrr), DestReg).addFrameIndex(FI).addReg(TOY::ZERO);
}

unsigned TOYInstrInfo::getGlobalBaseReg(MachineFunction *MF) const {
  llvm_unreachable("getGlobalBaseReg not implemented\n");
}
