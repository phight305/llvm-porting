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

#include "llvm/Support/DataTypes.h" // uint8_t

namespace llvm {
class Target;
class MCAsmBackend;
class MCInstrInfo;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCContext;
class MCCodeEmitter;
class MCObjectWriter;
class raw_ostream;
class StringRef;

extern Target TheTOYTarget;

MCCodeEmitter *createTOYMCCodeEmitter(const MCInstrInfo &MCII,
                                      const MCRegisterInfo &MRI,
                                      const MCSubtargetInfo &STI,
                                      MCContext &Ctx);
MCAsmBackend *createTOYAsmBackend(const Target &T, StringRef TT, StringRef CPU);

MCObjectWriter *createTOYELFObjectWriter(raw_ostream &OS,
                                         uint8_t OSABI,
                                         bool IsLittleEndian,
                                         bool Is64Bit);
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
