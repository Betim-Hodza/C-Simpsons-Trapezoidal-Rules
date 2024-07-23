import Foundation

func evaluateExpression(_ expression: String, withVariable x: Double) -> Double {
    let expr = NSExpression(format: expression)
    let variables = ["x": x]
}