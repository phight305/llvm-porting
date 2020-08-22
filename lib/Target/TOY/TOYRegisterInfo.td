class TOYReg<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "TOY";
}
foreach i = 0-3 in {
  def R#i : TOYReg<i, "r"#i >;
}
def ZERO : TOYReg<12, "zero">;
def SP : TOYReg<13, "sp">;
def LR : TOYReg<14, "lr">;
def TMP : TOYReg<15, "tmp">;
def GRRegs : RegisterClass<"TOY", [i32], 32, (add R0, R1, R2, R3, ZERO, SP, LR, TMP)>;
