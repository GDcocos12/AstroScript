# Dudolin
Dudolin PL interpreter written in C++

# DUDOLIN instructions:
`DCLR variable int/float value` - declare a variable<br />
`OPR [result_variable] variable/value action variable/value` - expression<br />
`INP [result_variable]` - input value to a variable<br />
`RND [result_variable] min max` - write random value to variable (variables can also be used as min or max)<br />
`COPY variable1 variable2` - write variable2 value to a variable1<br />
`PRINT variable/value/"string"` - print function<br />
`ORD [result_variable] 'char'` - write char code to a variable<br />
`POW [result_variable] variable1/value1 variable2/value2` - write variable1/value1 to the degree of variable2/value2 in the result_variable<br />
`IF condition {commands}` - IF expression<br />
`EXEC {filename}` - execute program<br />
`END` - finish program<br />

# SAMPLE PROGRAM

`DCLR x int 0;`<br />
`INP [x];`<br />
`IF x == 5 { PRINT "yep"; };`<br />
`END;`<br />

# How to write IF constructions

`IF condition {commands;};`<br />

For example:<br />
`IF 1 == 2 { PRINT "yes"; };`<br />
`IF x == y { PRINT "yes"; };`<br />
`IF x == 2 { PRINT "yes"; };`<br />

Condition Marks:<br />
`==` - equal<br />
`!=` - not equal<br />
`>` - greater<br />
`<` - lower<br />
`>=` - greater or equal<br />
`<=` - lower or equal<br />
