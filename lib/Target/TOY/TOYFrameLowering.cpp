//===-- TOYFrameLowering.cpp - TOY Frame Information ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the TOY implementation of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "TOYFrameLowering.h"
#include "TOYInstrInfo.h"
// #include "TOYMachineFunctionInfo.h"
#include "llvm/Function.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/DataLayout.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

void TOYFrameLowering::emitPrologue(MachineFunction &MF) const {
  const TOYInstrInfo &TII = *static_cast<const TOYInstrInfo*>(MF.getTarget().getInstrInfo());
  MachineBasicBlock &MBB = MF.front();
  MachineFrameInfo *MFI = MF.getFrameInfo();
  MachineBasicBlock::iterator MBBI = MBB.begin();
  DebugLoc dl = MBBI != MBB.end() ? MBBI->getDebugLoc() : DebugLoc();

  int StackSize = (int)MFI->getStackSize();
  BuildMI(MBB, MBBI, dl, TII.get(TOY::ADDri), TOY::SP).addReg(TOY::SP).addImm(StackSize);
}

void TOYFrameLowering::emitEpilogue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {
  const TOYInstrInfo &TII = *static_cast<const TOYInstrInfo*>(MF.getTarget().getInstrInfo());
  MachineFrameInfo *MFI = MF.getFrameInfo();
  MachineBasicBlock::iterator MBBI = MBB.getLastNonDebugInstr();
  DebugLoc dl = MBBI->getDebugLoc();

  int StackSize = (int)MFI->getStackSize();
  BuildMI(MBB, MBBI, dl, TII.get(TOY::SUBri), TOY::SP).addReg(TOY::SP).addImm(StackSize);
}
