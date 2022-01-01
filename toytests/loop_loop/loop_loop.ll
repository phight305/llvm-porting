; ModuleID = 'loop_loop.c'
target triple = "toy"

define i32 @main() nounwind uwtable {
entry:
  %retval = alloca i32, align 4
  %a = alloca i32*, align 8
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  %d = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  store i32 0, i32* %retval
  store i32* inttoptr (i64 4660 to i32*), i32** %a, align 8
  store i32 20, i32* %b, align 4
  store i32 30, i32* %c, align 4
  store i32 50, i32* %d, align 4
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc4, %entry
  %0 = load i32* %i, align 4
  %1 = load i32* %b, align 4
  %cmp = icmp slt i32 %0, %1
  br i1 %cmp, label %for.body, label %for.end6

for.body:                                         ; preds = %for.cond
  store i32 0, i32* %j, align 4
  br label %for.cond1

for.cond1:                                        ; preds = %for.inc, %for.body
  %2 = load i32* %j, align 4
  %3 = load i32* %c, align 4
  %cmp2 = icmp slt i32 %2, %3
  br i1 %cmp2, label %for.body3, label %for.end

for.body3:                                        ; preds = %for.cond1
  %4 = load i32* %d, align 4
  %add = add nsw i32 %4, 1
  store i32 %add, i32* %d, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body3
  %5 = load i32* %j, align 4
  %inc = add nsw i32 %5, 1
  store i32 %inc, i32* %j, align 4
  br label %for.cond1

for.end:                                          ; preds = %for.cond1
  br label %for.inc4

for.inc4:                                         ; preds = %for.end
  %6 = load i32* %i, align 4
  %inc5 = add nsw i32 %6, 1
  store i32 %inc5, i32* %i, align 4
  br label %for.cond

for.end6:                                         ; preds = %for.cond
  %7 = load i32* %d, align 4
  %8 = load i32** %a, align 8
  store i32 %7, i32* %8, align 4
  %9 = load i32* %retval
  ret i32 %9
}
