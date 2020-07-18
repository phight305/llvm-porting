set(LLVM_TARGET_DEFINITIONS TOY.td)

tablegen(LLVM TOYGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM TOYGenInstrInfo.inc -gen-instr-info)
#tablegen(LLVM TOYGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM TOYGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM TOYGenSubtargetInfo.inc -gen-subtarget)
#tablegen(LLVM TOYGenCallingConv.inc -gen-callingconv)
add_public_tablegen_target(TOYCommonTableGen)

add_llvm_target(TOYCodeGen
#  DelaySlotFiller.cpp
#  FPMover.cpp
   TOYAsmPrinter.cpp
#  TOYInstrInfo.cpp
   TOYISelDAGToDAG.cpp
   TOYISelLowering.cpp
#  TOYFrameLowering.cpp
#  TOYMachineFunctionInfo.cpp
   TOYRegisterInfo.cpp
   TOYSubtarget.cpp
   TOYTargetMachine.cpp
#  TOYSelectionDAGInfo.cpp
   TOYMCInstLower.cpp
)

#add_dependencies(LLVMTOYCodeGen intrinsics_gen)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
