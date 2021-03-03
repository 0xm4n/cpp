### SELECT

SELECT population FROM world
  WHERE name = 'France'



### IN

SELECT name, population FROM world
  WHERE name IN ('Brazil', 'Russia', 'India', 'China');



### BETWEEN

SELECT name, area FROM world
  WHERE area BETWEEN 250000 AND 300000



### LIKE

- The % is a *wild-card* it can match any characters
- The _underscore as a single character wildcard.



### ORDER  BY

The ORDER BY keyword is used to sort the result-set in ascending or descending order. The ORDER BY keyword sorts the records in ascending order by default. To sort the records in descending order, use the DESC keyword.

SELECT *column1*, *column2, ...*
FROM *table_name*
ORDER BY *column1, column2, ...* ASC|DES



### CONCAT()

CONCAT allows you to stick two or more strings together.

This operation is concatenation.

CONCAT(s1, s2 ...)   



### REPLACE()

REPLACE(f, s1, s2) returns the string f with all occurrences of s1 replaced with s2.

REPLACE('vessel','e','a') -> 'vassal'



### ROUND()

ROUND(f,p) returns f rounded to p decimal places.

The number of decimal places may be negative, this will round to the nearest 10 (when p is -1) or 100 (when p is -2) or 1000 (when p is -3) etc..

ROUND(7253.86, 1)    ->  7253.9



### LENGTH()

LENGTH(s) returns the number of characters in string s.

LENGTH('Hello') -> 5 



### MAX() / MIN()

The MAX() function returns the largest value of the selected column.

SELECT MIN(*column_name*) FROM *table_name* WHERE *condition*;



### ANY()

The ANY and ALL operators are used with a WHERE or HAVING clause.

The ANY operator returns true if any of the subquery values meet the condition.

SELECT *column_name(s)*
FROM *table_name*
WHERE *column_name operator* ANY
(SELECT *column_name* FROM *table_name* WHERE *condition*);

### ALL()

The ALL operator returns true if all of the subquery values meet the condition.

SELECT *column_name(s)*
FROM *table_name*
WHERE *column_name operator* ALL
(SELECT *column_name* FROM *table_name* WHERE *condition*);