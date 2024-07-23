import Foundation

func evaluateExpression(_ expression: String, withVariable x: Double) -> Double {
    let expr = NSExpression(format: expression)
    let variables = ["x": x]
    return expr.expressionValue(with: variables, context: nil) as? Double ?? 0.0
}

func simpsonsApprox(N: Int, b: Int, a: Int, function: String, deltaX: Double) -> Double {
    // set variables
    var sum = 0.0
    var x = Double(a)

    //evaluate f at a and b
    let f_a = evaluateExpression(function, withVariable: x)
    x = Double(b)
    let f_b = evaluateExpression(function, withVariable: x)

    //add the first and last terms
    sum += f_a + f_b 

    for i in 1..<N {
        // calculates each x value per loop
        x = Double(a) + Double(i) * deltaX
        //evaluate f_x
        let f_x = evaluateExpression(function, withVariable: x)

        /* 
        second to last term is always times 4
        if even then times 2, odd is times 4
        */
        if i == N - 1 {
            sum += 4 * f_x
        } else if i % 2 == 0 {
            sum += 2 * f_x
        } else {
            sum += 4 * f_x
        }
    }

    return (deltaX / 3) * sum
}

func trapezoidalApprox(N: Int, b: Int, a: Int, function: String, deltaX: Double) -> Double {
    
    var sum = 0.0
    var x = Double(a)

    //eval f at a & b
    let f_a = evaluateExpression(function, withVariable: x)
    x = Double(b)
    let f_b = evaluateExpression(function, withVariable: x)

    // add first and last terms
    sum += f_a + f_b

    for i in 1..<N {
        //get current x val
        x = Double(a) + Double(i) * deltaX
        // eval f at x
        let f_x = evaluateExpression(function, withVariable: x)

        // if i is not the first or last term, multiply f_x by 2 and add to sum
        if i > 1 && i < (N-1) {
            sum += 2 * f_x
        }
    }

    return (deltaX / 2) * sum
}

func printMenu() {
    print("Simpsons & Trapezoidal Algorithm")
    print("choose a number out of the list:")
    print("1. Simpsons")
    print("2. Trapezoidal")
    print("Please input the algorithm you want to use:")
}

func printingNote() {
    print("\nNote, when inputting a function you can write it like this: e.g. x + x^2 or (x*5)^2 or (x * 5) / 2.")
    print("Parenthesis work as intended")
    print("The following constants work: pi, e")
    print("Note: This Swift version uses NSExpression which might not support all functions from the original C version.")
}

// Main 
printMenu()

guard let choice = readLine(), (choice == "1" || choice == "2") else {
    print("Invalid choice. Exiting.")
    exit(1)
}

printingNote()

print("\nPlease input the function you want to integrate")
guard let function = readLine() else {
    print("Invalid function. Exiting.")
    exit(1)
}

print("Please input the number of intervals (N):")
guard let NString = readLine(), let N = Int(NString) else {
    print("Invalid number of intervals. Exiting.")
    exit(1)
}

print("Please input the lower bound (a):")
guard let aString = readLine(), let a = Int(aString) else {
    print("Invalid lower bound. Exiting.")
    exit(1)
}

print("Please input the upper bound (b):")
guard let bString = readLine(), let b = Int(bString) else {
    print("Invalid upper bound. Exiting.")
    exit(1)
}

let deltaX = Double(b - a) / Double(N)

if choice == "1" {
    let sum = simpsonsApprox(N: N, b: b, a: a, function: function, deltaX: deltaX)
    print("Simpsons Approximation of the integral from \(a)-\(b) of \(function) = \(sum)")
} else {
    let sum = trapezoidalApprox(N: N, b: b, a: a, function: function, deltaX: deltaX)
    print("Trapezoidal Approximation of the integral from \(a)-\(b) of \(function) = \(sum)")
}