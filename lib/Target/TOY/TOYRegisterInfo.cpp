//===-- TOYRegisterInfo.cpp - TOY Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the TOY implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "TOYRegisterInfo.h"
#include "TOY.h"
#include "TOYSubtarget.h"
#include "llvm/Type.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetInstrInfo.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"

#define GET_REGINFO_TARGET_DESC
#include "TOYGenRegisterInfo.inc"

using namespace llvm;

TOYRegisterInfo::TOYRegisterInfo(TOYSubtarget &st,
                                 const TargetInstrInfo &tii)
  : TOYGenRegisterInfo(TOY::LR/*Return address register*/), Subtarget(st), TII(tii) {
}

const uint16_t* TOYRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  // llvm_unreachable("getCalleeSavedRegs not implemented yet");
  static const uint16_t CalleeSavedRegs[] = { TOY::LR, TOY::R2, TOY::R3 };
  return CalleeSavedRegs;
}

BitVector TOYRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  Reserved.set(TOY::ZERO);
  Reserved.set(TOY::SP);
  Reserved.set(TOY::LR);
  Reserved.set(TOY::TMP);

  return Reserved;
}

void TOYRegisterInfo::
eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB,
                              MachineBasicBlock::iterator I) const {
  llvm_unreachable("eliminateCallFramePseudoInstr not implemented yet");
}

void
TOYRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                     int SPAdj, RegScavenger *RS) const {
  unsigned i = 0;
  MachineInstr &MI = *II;
  DebugLoc dl = MI.getDebugLoc();
  while (!MI.getOperand(i).isFI()) {
    ++i;
    assert(i < MI.getNumOperands() &&
           "Instr doesn't have FrameIndex operand!");
  }

  MachineFunction &MF = *MI.getParent()->getParent();
  MachineFrameInfo *MFI = MF.getFrameInfo();
  int StackSize = (int)(MFI->getStackSize());
  int FrameIndex = MI.getOperand(i).getIndex();
  int Offset = MF.getFrameInfo()->getObjectOffset(FrameIndex) - StackSize;

  BuildMI(*MI.getParent(), II, dl, TII.get(TOY::ADDri), TOY::TMP)
    .addReg(MI.getOperand(i + 1).getReg())
    .addImm(Offset);

  MI.getOperand(i).ChangeToRegister(TOY::SP, false/*IsDef*/);
  MI.getOperand(i+1).ChangeToRegister(TOY::TMP, false/*IsDef*/);
}

unsigned TOYRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  llvm_unreachable("getFrameRegister not implemented yet");
}

unsigned TOYRegisterInfo::getEHExceptionRegister() const {
  llvm_unreachable("getEHExceptionRegister What is the exception register");
}

unsigned TOYRegisterInfo::getEHHandlerRegister() const {
  llvm_unreachable(" getEHHandlerRegister What is the exception handler register");
}
