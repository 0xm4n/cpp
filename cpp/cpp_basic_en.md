### “declaration” and “definition”

definition refers to the place where the variable is created or assigned storage; definition is a superset of the declaration

declaration refers to places where the nature of the variable is stated but no storage is allocated. The declaration of a variable or function tells the program what its type is going to be.

A variable or function can be *declared* any number of times, but it can be *defined* only once.



### extern 

The **`extern`** keyword tells the compiler that a variable is defined in another source module (outside of the current scope). The linker then finds this actual declaration and sets up the **`extern`** variable to point to the correct location. Variables described by **`extern`** statements will not have any space allocated for them, as they should be properly defined elsewhere.



### external variable

A C program consists of a set of external objects, which are either variables or functions. The adjective external is used in contrast to internal, which describes the arguments and variables defined inside functions. External variables are defined outside of any function, and are thus potentially available to many functions. Functions themselves are always external, because C does not allow functions to be defined inside other functions. By default, external variables and functions have the property that all references to them by the same name, even from functions compiled separately, are references to the same thing.  The scope of an external variable or a function lasts from the point at which it is declared to the end of the file being compiled. It is important to distinguish between the declaration of an external variable and its definition. A declaration  announces the properties of a variable (primarily its type); a definition also causes storage to be set aside. There must be only one definition of an external variable among all the files that make up the source program; other files may contain extern declarations to access it. (There may also be extern declarations in the file containing the definition.)



### Static Variable

The static declaration, applied to an external variable or function, limits the scope of that object to the rest of the source file being compiled. External static thus provides a way to hide names. Normally, function names are global, visible to any part of the entire program. If a function is declared static, however, its name is invisible outside of the file in which it is declared. 
The static declaration can also be applied to internal variables. Internal static  variables are local to a particular function just as automatic variables are, but unlike automatics, they remain in existence rather than coming and going each time the function is activated. This means that internal static variables provide private, permanent storage within a single function.



### Passing array to functions

In C, when passing an array to a function say fun(), it is always treated as a pointer by fun(). Therefore in C, we must pass size of array as a parameter. Size may not be needed only in case of ‘\0’ terminated character arrays, size can be determined by checking end of string character.



### enum

An enumeration is a list of constant integer values. The first name in an enum has value 0, the next 1, and so on, unless explicit value are specified. If not all values are specified, unspecified values continue the progression from the last specified value. Name in different enumerations must be distinct. Enumerations provide a convenient way to associate constant values with names, an alternative to #define with the advantage that the values can be generated for you.



### comma operator

comma operator which most often finds use in the for statement. A pair of expressions separated by a comma is evaluated left to right, and the type and value of the result are the type and value of the right operand. The commas that separate function arguments, variables in declarations, etc., are not comma operators, and do not guarantee left to right evaluation. Comma operators should be used sparingly. The most suitable uses are for constructs strongly related to each other. A comma expression might also be appropriate for the exchange of elements in reverse where the exchange can be thought of as a single operation.

### conditional inclusion

The #if evaluates a constant integer expression. If the expression is non-zero, subsequent lines until an #endif or #elif or #else are included. The expression defined(name) in a #if is 1 if the name has been defined, and 0 otherwise. This can be used to avoid including files multiple times. If this style is used consistently, then each header can itself include any other headers on which it depends, without the user of the header having to deal with the interdependence. The #ifdef and #ifndef are specialized forms that test whether a name is defined.



### object variable definition

An object is a region of memory with a type that specifics what kind of information can be placed in it. The "places"  in which we store data are called objects. To access an object we need a name. A named object is called a variable and has a specified type that determines what can be put into the object and which operations can be applied. The data items we put into variable are called values. A statement that defines a variable is called a definition, and a definition can provide an initial value

A named object is called a variable.

A statement that introduces a new name into a program and sets aside memory for a variable is called a definition.

### Input

reading of string is terminated by what is called whitespace, that is , space, newline, and tab characters. Otherwise, whitespace by default is ignored by >>. For example, you can add as many spaces as you like before a number to be read; >> will just skip past them and read the number.

### Initialization Assignment

Initialization (giving a variable its initial value)

Assignment (giving a variable a new value)

logically assignment and initialization are different. You can tell the two apart by the type specification that always starts an initialization; an assignment does not have that. In principle, an initialization always finds the variable empty. On the other hand, an assignment must clear out the old value from the variable before putting in the new value.