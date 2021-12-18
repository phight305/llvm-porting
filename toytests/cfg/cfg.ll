; ModuleID = 'cfg.c'
target triple = "toy"

define i32 @main() nounwind uwtable {
entry:
  %retval = alloca i32, align 4
  %a = alloca i32*, align 8
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  store i32 0, i32* %retval
  store i32* inttoptr (i64 4660 to i32*), i32** %a, align 8
  store i32 20, i32* %b, align 4
  store i32 30, i32* %c, align 4
  %0 = load i32* %b, align 4
  %1 = load i32* %c, align 4
  %cmp = icmp slt i32 %0, %1
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %2 = load i32** %a, align 8
  store i32 5, i32* %2, align 4
  br label %if.end

if.else:                                          ; preds = %entry
  %3 = load i32** %a, align 8
  store i32 6, i32* %3, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %4 = load i32* %retval
  ret i32 %4
}
