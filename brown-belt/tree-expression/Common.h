//
// Created by smarty on 22.10.2020.
//

#ifndef TREE_EXPRESSION_COMMON_H
#define TREE_EXPRESSION_COMMON_H

#include <memory>
#include <string>

// Базовый класс арифметического выражения
class Expression {
public:
    virtual ~Expression() = default;

    // Вычисляет значение выражения
    virtual int Evaluate() const = 0;

    // Форматирует выражение как строку
    // Каждый узел берётся в скобки, независимо от приоритета
    virtual std::string ToString() const = 0;
};

using ExpressionPtr = std::unique_ptr<Expression>;

// Функции для формирования выражения
ExpressionPtr Value(int value);
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right);
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right);

#endif //TREE_EXPRESSION_COMMON_H
