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
//#include "llvm/MC/MCCodeGenInfo.h"
//#include "llvm/MC/MCInstrInfo.h"
//#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
//#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h" // For RegisterMCAsmInfo

//#define GET_INSTRINFO_MC_DESC
//#include "TOYGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "TOYGenSubtargetInfo.inc"

//#define GET_REGINFO_MC_DESC
//#include "TOYGenRegisterInfo.inc"

using namespace llvm;
/*
static MCInstrInfo *createSparcMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitSparcMCInstrInfo(X);
  return X;
}
static MCRegisterInfo *createSparcMCRegisterInfo(StringRef TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitSparcMCRegisterInfo(X, SP::I7);
  return X;
}
*/
/*
static MCSubtargetInfo *createTOYMCSubtargetInfo(StringRef TT, StringRef CPU,
                                                   StringRef FS) {
  MCSubtargetInfo *X = new MCSubtargetInfo();
  InitTOYMCSubtargetInfo(X, TT, CPU, FS);
  return X;
}
*/
/*
static MCCodeGenInfo *createSparcMCCodeGenInfo(StringRef TT, Reloc::Model RM,
                                               CodeModel::Model CM,
                                               CodeGenOpt::Level OL) {
  MCCodeGenInfo *X = new MCCodeGenInfo();
  X->InitMCCodeGenInfo(RM, CM, OL);
  return X;
}
*/
extern "C" void LLVMInitializeTOYTargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfo<TOYELFMCAsmInfo> X(TheTOYTarget);
  //RegisterMCAsmInfo<SparcELFMCAsmInfo> Y(TheSparcV9Target);

  // Register the MC codegen info.
  //TargetRegistry::RegisterMCCodeGenInfo(TheSparcTarget,
  //                                     createSparcMCCodeGenInfo);
  //TargetRegistry::RegisterMCCodeGenInfo(TheSparcV9Target,
  //                                     createSparcMCCodeGenInfo);

  // Register the MC instruction info.
  //TargetRegistry::RegisterMCInstrInfo(TheSparcTarget, createSparcMCInstrInfo);

  // Register the MC register info.
  //TargetRegistry::RegisterMCRegInfo(TheSparcTarget, createSparcMCRegisterInfo);

  // Register the MC subtarget info.
  //TargetRegistry::RegisterMCSubtargetInfo(TheTOYTarget,
  //                                        createTOYMCSubtargetInfo);
}
