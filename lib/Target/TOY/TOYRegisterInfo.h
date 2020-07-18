//===-- TOYRegisterInfo.h - TOY Register Information Impl ---*- C++ -*-===//
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

#ifndef TOYREGISTERINFO_H
#define TOYREGISTERINFO_H

#include "llvm/Target/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "TOYGenRegisterInfo.inc"

namespace llvm {

class TOYSubtarget;
class TargetInstrInfo;
class Type;

struct TOYRegisterInfo : public TOYGenRegisterInfo {
  TOYSubtarget &Subtarget;
  const TargetInstrInfo &TII;

  TOYRegisterInfo(TOYSubtarget &st, const TargetInstrInfo &tii);

  /// Code Generation virtual methods...
  const uint16_t *getCalleeSavedRegs(const MachineFunction *MF = 0) const;

  BitVector getReservedRegs(const MachineFunction &MF) const;

  void eliminateCallFramePseudoInstr(MachineFunction &MF,
                                     MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator I) const;

  void eliminateFrameIndex(MachineBasicBlock::iterator II,
                           int SPAdj, RegScavenger *RS = NULL) const;

  void processFunctionBeforeFrameFinalized(MachineFunction &MF) const;

  // Debug information queries.
  unsigned getFrameRegister(const MachineFunction &MF) const;

  // Exception handling queries.
  unsigned getEHExceptionRegister() const;
  unsigned getEHHandlerRegister() const;

};

} // end namespace llvm

#endif
