//===-- TOYMCTargetDesc.h - TOY Target Descriptions ---------*- C++ -*-===//
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

#ifndef TOYMCTARGETDESC_H
#define TOYMCTARGETDESC_H

namespace llvm {
class Target;
class MCAsmBackend;
class StringRef;

extern Target TheTOYTarget;

MCAsmBackend *createTOYAsmBackend(const Target &T, StringRef TT, StringRef CPU);

} // End llvm namespace

// Defines symbolic names for TOY registers.  This defines a mapping from
// register name to register number.
//
#define GET_REGINFO_ENUM
#include "TOYGenRegisterInfo.inc"

// Defines symbolic names for the TOY instructions.
//
#define GET_INSTRINFO_ENUM
#include "TOYGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "TOYGenSubtargetInfo.inc"

#endif
