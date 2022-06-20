# Python miscellaneous

## OOP 

### Class Variable
**Class variables** are definede outside the initializer and has no self prefix to it. Every instance has the same copy of it

**Instance variable** are defined with self prefix, and each instance has its own copy

```python
class Player:
    classVar = 1  # class variables

    def __init__(self):
        self.instanceVar = 0  # creating instance variables
```

### Class method and Static method
**Class Methods** and **Static Method** can both be accessed using either the class name or a instance

To define a class method, we need to use cls as the first input and use the `@classmethod` decorator,

To define a static method, we dont need to use any additional input and add the `@staticmethod` decorator

```python
class Player:
    teamName = 'Liverpool'  # class variables

    def __init__(self, name):
        self.name = name  # creating instance variables

    @classmethod
    def getTeamName(cls): # a class method
        return cls.teamName

    @staticmethod
    def demo(): # a static method
        print("I am a static method.")
```



TO BE CONTINUED

### Abstract Base Class
To define an abstract base class, we need to import from module `abc`. The abstract class has to inherit from class `ABC`
```python
from abc import ABC, abstractmethod

class ParentClass(ABC):

    @abstractmethod
    def method(self)
```


## Garbage Collection
https://towardsdatascience.com/memory-management-and-garbage-collection-in-python-c1cb51d1612c

1. Reference Counting
Each 

2. Generational Garbage Collection