# Pattern Ideas

* Increments followed by a decrement, or vice-versa
* Addition/Subtraction by 0
* Multiplication/Division/Modulo by 1
* Bit shifting for multiplication and division by a power of 2
* Adding a negative number
* An iload followed by an istore (Same for aload/astore and field)
* Collapse consecutive labels
* Consectuive ineg's
* Strip nop's
* Swap appearing before an addition or multiplcation
* dup'ing and then branching
* dup and then a load and then a pop
* Loading a constant and then branching
* Strip instructions following a return up to the next label
* Generalize Lauries's "GOTO" pattern for conditional branching
* Explicit 'intanceof'
