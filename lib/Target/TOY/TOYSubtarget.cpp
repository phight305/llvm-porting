//===-- TOYSubtarget.cpp - TOY Subtarget Information ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the TOY specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "TOYSubtarget.h"
#include "TOY.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "TOYGenSubtargetInfo.inc"

using namespace llvm;

void TOYSubtarget::anchor() { }

TOYSubtarget::TOYSubtarget(const std::string &TT, const std::string &CPU,
                           const std::string &FS) :
  TOYGenSubtargetInfo(TT, CPU, FS), IsV1(false) {
    // Parse features string.
    ParseSubtargetFeatures(CPU, FS);  
}
