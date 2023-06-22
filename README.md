# Dudolin
Dudolin PL interpreter written in C++
bruh

# DUDOLIN instructions:
`DCLR variable int/float value` - declare a variable
`OPR [result_variable] variable/value action variable/value` - expression
`INP [result_variable]` - input value to a variable
`RND [result_variable] min max` - write random value to variable (variables can also be used as min or max)
`COPY variable1 variable2` - write variable2 value to a variable1
`PRINT variable/value/"string"` - print function
`ORD [result_variable] 'char'` - write char code to a variable
`POW [result_variable] variable1/value1 variable2/value2` - write variable1/value1 to the degree of variable2/value2 in the result_variable
`IF condition {commands}` - IF expression
`END` - finish program

# SAMPLE PROGRAM

`
DCLR x int 0;
INP [x];
IF x == 5 { PRINT "yep"; };
END;
`

# How to write IF constructions

`IF condition {commands;};`

For example:
`
IF 1 == 2 { PRINT "yes"; };
IF x == y { PRINT "yes"; };
IF x == 2 { PRINT "yes"; };
`

Condition Marks:
`
== - equal
!= - not equal
> - greater
< - lower
>= - greater or equal
<= - lower or equal
`
