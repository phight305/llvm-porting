//===-- TOYFixupKinds.h - TOY Specific Fixup Entries ----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TOY_TOYFIXUPKINDS_H
#define LLVM_TOY_TOYFIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm {
namespace TOY {
  // Although most of the current fixup types reflect a unique relocation
  // one can have multiple fixup types for a given relocation and thus need
  // to be uniquely named.
  //
  // This table *must* be in the save order of
  // MCFixupKindInfo Infos[TOY::NumTargetFixupKinds]
  // in TOYAsmBackend.cpp.
  //
  enum Fixups {
    fixup_TOY_CALL = FirstTargetFixupKind,

    // Marker
    LastTargetFixupKind,
    NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind
  };
} // namespace TOY
} // namespace llvm


#endif // LLVM_TOY_TOYFIXUPKINDS_H

