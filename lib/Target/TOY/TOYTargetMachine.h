//===-- TOYTargetMachine.h - Define TargetMachine for TOY ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Sparc specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef TOYTARGETMACHINE_H
#define TOYTARGETMACHINE_H

// #include "TOYInstrInfo.h"
// #include "TOYISelLowering.h"
// #include "TOYFrameLowering.h"
#include "TOYSubtarget.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/DataLayout.h"
// #include "llvm/Target/TargetFrameLowering.h"
// #include "llvm/Target/TargetTransformImpl.h"

namespace llvm {

class TOYTargetMachine : public LLVMTargetMachine {
  TOYSubtarget Subtarget;
  const DataLayout DL;       // Calculates type size & alignment
  // TOYInstrInfo InstrInfo;
  // TOYTargetLowering TLInfo;
  // TOYFrameLowering FrameLowering;
public:
  TOYTargetMachine(const Target &T, StringRef TT,
                   StringRef CPU, StringRef FS, const TargetOptions &Options,
                   Reloc::Model RM, CodeModel::Model CM,
                   CodeGenOpt::Level OL);
  // virtual const TOYInstrInfo *getInstrInfo() const {
    // llvm_unreachable("getInstrInfo not implemented yet\n");
    // return InstrInfo;
  // }
  // virtual const TargetFrameLowering  *getFrameLowering() const {
    // llvm_unreachable("getFrameLowering not implemented yet\n");
    // return &FrameLowering;
  // }
  virtual const TOYSubtarget *getSubtargetImpl() const {
    return &Subtarget;
  }
  // virtual const TOYRegisterInfo *getRegisterInfo() const {
    // llvm_unreachable("getRegisterInfo not implemented yet\n");
    // return &InstrInfo.getRegisterInfo();
  // }
  // virtual const TOYTargetLowering* getTargetLowering() const {
    // llvm_unreachable("getTargetLowering not implemented yet\n");
    // return &TLInfo;
  // }
  virtual const DataLayout *getDataLayout() const {
      return &DL;
  }

  // Pass Pipeline Configuration
  virtual TargetPassConfig *createPassConfig(PassManagerBase &PM);
};


} // end namespace llvm

#endif
