//===-- TOY.td - Describe the TOY Target Machine -------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//def FeatureIsV1
//  : SubtargetFeature<"v1", "IsV1", "true",
//                     "Enable TOY-V1 instructions">;

//===----------------------------------------------------------------------===//
// Declare the target which we are implementing
//===----------------------------------------------------------------------===//
include "TOYRegisterInfo.td"
//include "TOYInstrInfo.td"
//include "TOYCallingConv.td"

//class Proc<string Name, list<SubtargetFeature> Features>
// : Processor<Name, NoItineraries, Features>;

//def : Proc<"generic",         [FeatureIsV1]>;

//def TOYInstrInfo : InstrInfo;

def TOY : Target {
  // Pull in Instruction Info:
  //let InstructionSet = TOYInstrInfo;
}
