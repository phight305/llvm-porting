//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the TOYMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef TOYTARGETASMINFO_H
#define TOYTARGETASMINFO_H

#include "llvm/MC/MCAsmInfo.h"

namespace llvm {
  class StringRef;
  class Target;

  class TOYELFMCAsmInfo : public MCAsmInfo {
    virtual void anchor();
  public:
    explicit TOYELFMCAsmInfo(const Target &T, StringRef TT);
  };

} // namespace llvm

#endif
