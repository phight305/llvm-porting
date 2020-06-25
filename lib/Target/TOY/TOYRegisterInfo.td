class TOYReg<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "TOY";
}
foreach i = 0-3 in {
  def R#i : TOYReg<i, "r"#i >;
}
def SP : TOYReg<13, "sp">;
def LR : TOYReg<14, "lr">;
def GRRegs : RegisterClass<"TOY", [i32], 32, (add R0, R1, R2, R3, SP)>;
