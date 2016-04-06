# Pattern Ideas

## TODO
* Increments followed by a decrement, or vice-versa
* Addition/Subtraction by 0
* Multiplication/Division/Modulo by 1
* Bit shifting for multiplication and division by a power of 2
* Adding a negative number
* Collapse consecutive labels
* Swap appearing before an addition or multiplcation
* Loading a constant and then branching
* Strip instructions following a return up to the next label
* Generalize Lauries's "GOTO" pattern for conditional branching
* Explicit 'intanceof'
* Change astore, aload k to astore_, aload_k (same for istore, iload)

## DONE
* a load and then a pop
* Strip nop's
* An iload followed by an istore (Same for aload/astore and field)
* Remove dup and pop that come before and after astore, istore
* dup'ing and then compare equals branching

## NOT FOUND IN CODE
* Consectuive ineg's