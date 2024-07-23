// guide i followed : https://medium.com/@elifedman/understanding-nsexpression-in-swift-a-beginners-guide-50b7baa36271

//to use NSExpression you need to import foundation 

import Foundation

let num1 = 5.3
let num2 = 4

let expression = NSExpression(format: "\(num1)*\(num2)")

if let result = expression.expressionValue(with: nil, context: nil) as? Double 
{
    print("result: \(result)")
}

/*

Functions

NSExpression supports various mathematical and logical functions.

Basic Arithmetic Functions

add:to:: Adds two numbers.
from:subtract:: Subtracts one value from another.
multiply:by:: Multiplies two numbers.
divide:by:: Divides one number by another.
modulus:by:: Computes the remainder of one number divided by another.
Mathematical Arithmetic Functions

sqrt:: Calculates the square root of a number.
log:: Calculates the logarithm of a number.
ln:: Calculates the natural logarithm of a number.
raise:toPower: Calculates a number raised to a given power.
exp:: Raises the mathematical constant e to the power of a number.
abs:: Returns the absolute value of a numeric expression.
ceil:: Rounds up a numeric expression to the nearest integer.
floor:: Rounds down a numeric expression to the nearest integer.
floor:: Calculates the integral number nearest to but no greater than the given number

*/

//more examples

//calculate 2 to the power of 5

let baseNum = 3
let exponentNum = 4.0

let baseExpression = NSExpression(forConstantValue: baseNum)
let exponentExpression = NSExpression(forConstantValue: exponentNum)

let expressionPow = NSExpression(forFunction: "raise:toPower:", arguments: [baseExpression, exponentExpression])

if let result = expressionPow.expressionValue(with: nil, context: nil) as? Double {
    print(result)
} else {
    print("error")
}

//find min value in values array

let numbers = [543, 34, 543, 67, 102]
let numbersExpressions = NSExpression(forConstantValue: numbers)

let avgExpression = NSExpression(forFunction: "min:", arguments: [numbersExpressions])

if let answ = avgExpression.expressionValue(with: nil, context: nil) as? Double {
    print("result: \(answ)")
}

// non related to math but still really cool!

let word = "meDiUm"
let wordExpression = NSExpression(forConstantValue: word)

let exprss = NSExpression(forFunction: "uppercase:", arguments: [wordExpression])

if let ans = exprss.expressionValue(with: nil, context: nil) as? String {
    print(ans)
} else {
    print("Error")
}