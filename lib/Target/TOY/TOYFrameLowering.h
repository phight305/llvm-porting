//===-- TOYFrameLowering.h - Define frame lowering for TOY --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//
//===----------------------------------------------------------------------===//

#ifndef TOY_FRAMEINFO_H
#define TOY_FRAMEINFO_H

#include "TOY.h"
#include "TOYSubtarget.h"
#include "llvm/Target/TargetFrameLowering.h"

namespace llvm {
  class TOYSubtarget;

class TOYFrameLowering : public TargetFrameLowering {
public:
  explicit TOYFrameLowering(const TOYSubtarget &/*sti*/)
    : TargetFrameLowering(TargetFrameLowering::StackGrowsUp, 4/*Align*/, 0/*FIXME: LocalAreaOffset*/) {
  }

  /// emitProlog/emitEpilog - These methods insert prolog and epilog code into
  /// the function.
  void emitPrologue(MachineFunction &MF) const;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const;

  bool hasFP(const MachineFunction &MF) const { return false; }
};

} // End llvm namespace

#endif

