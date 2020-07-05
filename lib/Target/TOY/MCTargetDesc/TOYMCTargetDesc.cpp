//===-- TOYMCTargetDesc.cpp - TOY Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides TOY specific target descriptions.
//
//===----------------------------------------------------------------------===//
#include "TOYMCTargetDesc.h"
#include "TOYMCAsmInfo.h"
// #include "llvm/MC/MCCodeGenInfo.h"
// #include "llvm/MC/MCInstrInfo.h"
// #include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
// #include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h" // For RegisterMCAsmInfo

// #define GET_INSTRINFO_MC_DESC
// #include "TOYGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "TOYGenSubtargetInfo.inc"

// #define GET_REGINFO_MC_DESC
// #include "TOYGenRegisterInfo.inc"

using namespace llvm;
static MCInstrInfo *createTOYMCInstrInfo() {
  llvm_unreachable("createTOYMCInstrInfo is not implemented yet!");
  // MCInstrInfo *X = new MCInstrInfo();
  // InitTOYMCInstrInfo(X);
  // return X;
}
static MCRegisterInfo *createTOYMCRegisterInfo(StringRef TT) {
  llvm_unreachable("createTOYMCRegisterInfo is not implemented yet!");
  // MCRegisterInfo *X = new MCRegisterInfo();
  // InitTOYMCRegisterInfo(X, SP::I7);
  // return X;
}
static MCSubtargetInfo *createTOYMCSubtargetInfo(StringRef TT, StringRef CPU, StringRef FS) {
  llvm_unreachable("createTOYMCSubtargetInfo is not implemented yet!");
  // MCSubtargetInfo *X = new MCSubtargetInfo();
  // InitTOYMCSubtargetInfo(X, TT, CPU, FS);
  // return X;
}
static MCCodeGenInfo *createTOYMCCodeGenInfo(StringRef TT, Reloc::Model RM,
                                             CodeModel::Model CM,
                                             CodeGenOpt::Level OL) {
  llvm_unreachable("createTOYMCCodeGenInfo is not implemented yet!");
  // MCCodeGenInfo *X = new MCCodeGenInfo();
  // X->InitMCCodeGenInfo(RM, CM, OL);
  // return X;
}
extern "C" void LLVMInitializeTOYTargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfo<TOYELFMCAsmInfo> X(TheTOYTarget);
  // RegisterMCAsmInfo<TOYELFMCAsmInfo> Y(TheTOYV9Target);

  // Register the MC codegen info.
  // TargetRegistry::RegisterMCCodeGenInfo(TheTOYTarget,
  //                                       createTOYMCCodeGenInfo);
  // TargetRegistry::RegisterMCCodeGenInfo(TheTOYV9Target,
  //                                       createTOYMCCodeGenInfo);

  // Register the MC instruction info.
  // TargetRegistry::RegisterMCInstrInfo(TheTOYTarget, createTOYMCInstrInfo);

  // Register the MC register info.
  // TargetRegistry::RegisterMCRegInfo(TheTOYTarget, createTOYMCRegisterInfo);

  // Register the MC subtarget info.
  // TargetRegistry::RegisterMCSubtargetInfo(TheTOYTarget,
  //                                         createTOYMCSubtargetInfo);
}
