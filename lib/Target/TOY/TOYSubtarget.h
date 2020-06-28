//===-- TOYSubtarget.h - Define Subtarget for the TOY -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the SPARC specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#ifndef TOY_SUBTARGET_H
#define TOY_SUBTARGET_H

#include "llvm/Target/TargetSubtargetInfo.h"
#include <string>

#define GET_SUBTARGETINFO_HEADER
#include "TOYGenSubtargetInfo.inc"

namespace llvm {
class StringRef;

class TOYSubtarget : public TOYGenSubtargetInfo {
  virtual void anchor();
  bool IsV1;  
public:
  TOYSubtarget(const std::string &TT, const std::string &CPU,
               const std::string &FS);

  bool isV1() const { return IsV1; }
  std::string getDataLayout() const {
    return std::string("E-p:32:32:32-i64:64:64-f64:64:64-f128:64:64-n32");
  }

  void ParseSubtargetFeatures(StringRef CPU, StringRef FS);
};

} // end namespace llvm

#endif
