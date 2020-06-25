//===-- TOYMCAsmInfo.cpp - TOY asm properties -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the TOYMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "TOYMCAsmInfo.h"
#include "llvm/ADT/Triple.h"

using namespace llvm;

void TOYELFMCAsmInfo::anchor() { }

TOYELFMCAsmInfo::TOYELFMCAsmInfo(const Target &T, StringRef TT) {

#if 0
  IsLittleEndian = false;
  Triple TheTriple(TT);
  if (TheTriple.getArch() == Triple::sparcv9)
    PointerSize = 8;

  Data16bitsDirective = "\t.half\t";
  Data32bitsDirective = "\t.word\t";
  Data64bitsDirective = 0;  // .xword is only supported by V9.
  ZeroDirective = "\t.skip\t";
  CommentString = "!";
  HasLEB128 = true;
  SupportsDebugInformation = true;
  
  SunStyleELFSectionSwitchSyntax = true;
  UsesELFSectionDirectiveForBSS = true;

  WeakRefDirective = "\t.weak\t";

  PrivateGlobalPrefix = ".L";

#endif
}
