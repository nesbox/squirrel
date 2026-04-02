.. _expressions:


=================
Expressions
=================

.. index::
    single: Expressions

----------------
Assignment
----------------

.. index::
    single: assignment(=)
    single: new slot(<-)

::

    exp := derefexp '=' exp
    exp:= derefexp '<-' exp

squirrel implements 2 kind of assignment: the normal assignment(=)::

    a = 10;

and the "new slot" assignment.::

    a <- 10;

The new slot expression allows to add a new slot into a table(see :ref:`Tables <tables>`). If the slot
already exists in the table it behaves like a normal assignment.

----------------
Operators
----------------

.. index::
    single: Operators

^^^^^^^^^^^^^
?: Operator
^^^^^^^^^^^^^

.. index::
    pair: ?: Operator; Operators

::

    exp := exp_cond '?' exp1 ':' exp2

conditionally evaluate an expression depending on the result of an expression.

^^^^^^^^^^^^^
Arithmetic
^^^^^^^^^^^^^

.. index::
    pair: Arithmetic Operators; Operators

::

    exp:= 'exp' op 'exp'

Squirrel supports the standard arithmetic operators ``+, -, *, / and %``.
Other than that is also supports compact operators (``+=,-=,*=,/=,%=``) and
increment and decrement operators(++ and --);::

    a += 2;
    //is the same as writing
    a = a + 2;
    x++
    //is the same as writing
    x = x + 1

All operators work normally with integers and floats; if one operand is an integer and one
is a float the result of the expression will be float.
The + operator has a special behavior with strings; if one of the operands is a string the
operator + will try to convert the other operand to string as well and concatenate both
together. For instances and tables, ``_tostring`` is invoked.

^^^^^^^^^^^^^
Relational
^^^^^^^^^^^^^

.. index::
    pair: Relational Operators; Operators

::

    exp:= 'exp' op 'exp'

Relational operators in Squirrel are : ``==, <, <=, <, <=, !=``

These operators return true if the expression is false and a value different than true if the
expression is true. Internally the VM uses the integer 1 as true but this could change in
the future.

^^^^^^^^^^^^^^
3 ways compare
^^^^^^^^^^^^^^

.. index::
    pair: 3 ways compare operator; Operators

::

    exp:= 'exp' <=> 'exp'

the 3 ways compare operator <=> compares 2 values A and B and returns an integer less than 0
if A < B, 0 if A == B and an integer greater than 0 if A > B.

^^^^^^^^^^^^^^
Logical
^^^^^^^^^^^^^^

.. index::
    pair: Logical operators; Operators

::

    exp := exp op exp
    exp := '!' exp

Logical operators in Squirrel are : ``&&, ||, !, ??``

The operator ``&&`` (logical and) returns its first argument if it is "false" (null, 0, 0.0, or false), otherwise returns its second argument.

The operator ``||`` (logical or) returns its first argument if it is "true" (not null, 0, 0.0, or false), otherwise returns the second argument.

The operator ``??`` (null coalescing) returns its first argument if it is **not** null, otherwise returns the second argument. Unlike ``||``, it only treats **null** as falsey.

The '!' operator will return true if the given value to negate was "false", or false if the given value was "true".

^^^^^^^^^^^^^^^^^^^
Optional Chaining
^^^^^^^^^^^^^^^^^^^

.. index::
    pair: Optional Chaining; Operators

::

    exp := obj_exp '?.' field_id
    exp := obj_exp '?[' key_exp ']'

The optional chaining operators allow safe access to table slots or class members. 
If the *obj_exp* evaluates to **null**, the entire expression evaluates to **null** without throwing an error.
Additionally, if the *obj_exp* is a table or class but the requested field does not exist, it also evaluates to **null** safely.

Optional chaining can be nested::

    local val = obj?.sub?.field;

If any element in the chain is null or missing, the result is null.
Note: Optional chaining cannot be used with mutating operators like ``++`` or ``--``, and currently does not support optional function calls.

^^^^^^^^^^^^^^^
in operator
^^^^^^^^^^^^^^^

.. index::
    pair: in operator; Operators

::

    exp:= keyexp 'in' tableexp

Tests the existence of a slot in a table.
Returns true if *keyexp* is a valid key in *tableexp* ::

    local t=
    {
        foo="I'm foo",
        [123]="I'm not foo"
    }

    if("foo" in t) dostuff("yep");
    if(123 in t) dostuff();

^^^^^^^^^^^^^^^^^^^
classof operator
^^^^^^^^^^^^^^^^^^^

.. index::
    pair: classof operator; Operators

::

    exp := classexp1 'classof' classexp2

Tests whether *classexp1* is the same class as *classexp2* or derives from it.
Returns true if *classexp1* is *classexp2* or extends *classexp2* anywhere in its inheritance chain.

^^^^^^^^^^^^^^^^^^^
instanceof operator
^^^^^^^^^^^^^^^^^^^

.. index::
    pair: instanceof operator; Operators

::

    exp:= instanceexp 'instanceof' classexp

Tests if a class instance is an instance of a certain class.
Returns true if *instanceexp* is an instance of *classexp*.

^^^^^^^^^^^^^^^^^^^
typeof operator
^^^^^^^^^^^^^^^^^^^

.. index::
    pair: typeof operator; Operators

::

    exp:= 'typeof' exp

returns the type name of a value as string.::

    local a={},b="squirrel"
    print(typeof a); //will print "table"
    print(typeof b); //will print "string"

^^^^^^^^^^^^^^^^^^^
Comma operator
^^^^^^^^^^^^^^^^^^^

.. index::
    pair: Comma operator; Operators

::

    exp:= exp ',' exp

The comma operator evaluates two expression left to right, the result of the operator is
the result of the expression on the right; the result of the left expression is discarded.::

    local j=0,k=0;
    for(local i=0; i<10; i++ , j++)
    {
        k = i + j;
    }
    local a,k;
    a = (k=1,k+2); //a becomes 3

^^^^^^^^^^^^^^^^^^^
Bitwise Operators
^^^^^^^^^^^^^^^^^^^

.. index::
    pair: Bitwise Operators; Operators

::

    exp:= 'exp' op 'exp'
    exp := '~' exp

Squirrel supports the standard C-like bitwise operators ``&, |, ^, ~, <<, >>`` plus the unsigned
right shift operator ``>>>``. The unsigned right shift works exactly like the normal right shift operator(``>>``)
except for treating the left operand as an unsigned integer, so is not affected by the sign. Those operators
only work on integer values; passing of any other operand type to these operators will
cause an exception.

^^^^^^^^^^^^^^^^^^^^^
Operators precedence
^^^^^^^^^^^^^^^^^^^^^

.. index::
    pair: Operators precedence; Operators

+----------------------------------------------------+-----------+
| ``., ?., [ ], ?[ ], ( ), -, ~, !, typeof, ++, --,  | highest   |
| clone``                                            |           |
+----------------------------------------------------+-----------+
| ``/, *, %``                                        | ...       |
+----------------------------------------------------+-----------+
| ``+, -``                                           |           |
+----------------------------------------------------+-----------+
| ``<<, >>, >>>``                                    |           |
+----------------------------------------------------+-----------+
| ``<, <=, >, >=, in, classof, instanceof``          |           |
+----------------------------------------------------+-----------+
| ``==, !=, <=>``                                    |           |
+----------------------------------------------------+-----------+
| ``&``                                              |           |
+----------------------------------------------------+-----------+
| ``^``                                              |           |
+----------------------------------------------------+-----------+
| ``|``                                              |           |
+----------------------------------------------------+-----------+
| ``&&``                                             |           |
+----------------------------------------------------+-----------+
| ``||``                                             |           |
+----------------------------------------------------+-----------+
| ``??``                                             |           |
+----------------------------------------------------+-----------+
| ``?:``                                             |           |
+----------------------------------------------------+-----------+
| ``+=, =, -=, /=, *=, %=, <-``                      | ...       |
+----------------------------------------------------+-----------+
| ``, (comma operator)``                             | lowest    |
+----------------------------------------------------+-----------+

.. _table_constructor:

-----------------
Table Constructor
-----------------

.. index::
    single: Table Contructor

::

    tslots := ( 'id' '=' exp | '[' exp ']' '=' exp ) [',']
    exp := '{' [tslots] '}'

Creates a new table.::

    local a = {} //create an empty table

A table constructor can also contain slots declaration; With the syntax: ::

    local a = {
        slot1 = "I'm the slot value"
    }

An alternative syntax can be::

    '[' exp1 ']' = exp2 [',']

A new slot with exp1 as key and exp2 as value is created::

    local a=
    {
        [1]="I'm the value"
    }

Both syntaxes can be mixed::

    local table=
    {
        a=10,
        b="string",
        [10]={},
        function bau(a,b)
        {
            return a+b;
        }
    }

The comma between slots is optional.

^^^^^^^^^^^^^^^^^^^^^^
Table with JSON syntax
^^^^^^^^^^^^^^^^^^^^^^

.. index::
    single: Table with JSON syntax

Since Squirrel 3.0 is possible to declare a table using JSON syntax(see http://www.wikipedia.org/wiki/JSON).

the following JSON snippet: ::

    local x = {
      "id": 1,
      "name": "Foo",
      "price": 123,
      "tags": ["Bar","Eek"]
    }

is equivalent to the following squirrel code: ::

    local x = {
      id = 1,
      name = "Foo",
      price = 123,
      tags = ["Bar","Eek"]
    }

-----------------
clone
-----------------

.. index::
    single: clone

::

    exp:= 'clone' exp

Clone performs shallow copy of a table, array or class instance (copies all slots in the new object without
recursion). If the source table has a delegate, the same delegate will be assigned as
delegate (not copied) to the new table (see :ref:`Delegation <delegation>`).

After the new object is ready the "_cloned" meta method is called (see :ref:`Metamethods <metamethods>`).

When a class instance is cloned the constructor is not invoked(initializations must rely on ```_cloned``` instead

-----------------
Array contructor
-----------------

.. index::
    single: Array constructor

::

    exp := '[' [explist] ']'

Creates a new array.::

    a <- [] //creates an empty array

Arrays can be initialized with values during the construction::

    a <- [1,"string!",[],{}] //creates an array with 4 elements
