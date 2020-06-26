set(LLVM_TARGET_DEFINITIONS TOY.td)

tablegen(LLVM TOYGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM TOYGenInstrInfo.inc -gen-instr-info)
#tablegen(LLVM SparcGenAsmWriter.inc -gen-asm-writer)
#tablegen(LLVM SparcGenDAGISel.inc -gen-dag-isel)
#tablegen(LLVM SparcGenSubtargetInfo.inc -gen-subtarget)
#tablegen(LLVM SparcGenCallingConv.inc -gen-callingconv)
add_public_tablegen_target(TOYCommonTableGen)

add_llvm_target(TOYCodeGen
#  DelaySlotFiller.cpp
#  FPMover.cpp
#  SparcAsmPrinter.cpp
#  SparcInstrInfo.cpp
#  SparcISelDAGToDAG.cpp
#  SparcISelLowering.cpp
#  SparcFrameLowering.cpp
#  SparcMachineFunctionInfo.cpp
# SparcRegisterInfo.cpp
#  SparcSubtarget.cpp
   TOYTargetMachine.cpp
#  SparcSelectionDAGInfo.cpp
)

#add_dependencies(LLVMSparcCodeGen intrinsics_gen)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
