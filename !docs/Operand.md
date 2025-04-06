```mermaid
---
title: Operand
---
classDiagram
    class Operand

    class Boolean

    class Integer

    class Real

    class Variable

    class Pi

    class E

    Operand <|-- Boolean
    Operand <|-- Integer
    Operand <|-- Real
    Operand <|-- Variable
    Real <|-- Pi
    Real <|-- E
```