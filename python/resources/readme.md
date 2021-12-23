#Json-CPP 
A better json library.

## Installation
```
pip install json-cpp

```

## Create your first json object:
After installing the package, try the following python script:
```
from json_cpp JsonObject

class MyJsonClass(JsonObject):
    def __init__(self, name="", age=0, weight=0.0):
        self.name = name
        self.age = age
        self.weight = weight


myobject = MyJsonClass('German Espinosa', 41, 190.0)

print(myobject)

```
output
```
{"name":"German Espinosa","age":41,"weight":190.0}
```
###Object to json conversion:

All objects with type MyJsonClass will produce perfectly formed json when converted to string.
If you need to retrieve the json string representing the object:
```
from json_cpp JsonObject

class MyJsonClass(JsonObject):
    def __init__(self, name="", age=0, weight=0.0):
        self.name = name
        self.age = age
        self.weight = weight


myobject = MyJsonClass('German Espinosa', 41, 190.0)

json_string = str(myobject)

print (json_string)
```
output
```
{"name":"German Espinosa","age":41,"weight":190.0}
```
### Json to object conversion:
You can create instances of your json objects from strings containing a correct json representation:
```
from json_cpp JsonObject

class MyJsonClass(JsonObject):
    def __init__(self, name="", age=0, weight=0.0):
        self.name = name
        self.age = age
        self.weight = weight


json_string = "{\"name\":\"German Espinosa\",\"age\":41,\"weight\":190.0}"

myobject = MyJsonClas.parse(json_string)

print ("name:", myobject.name, type(myobject.name))
print ("age:", myobject.age, type(myobject.age)) 
print ("weight:", myobject.weight, type(myobject.weight))

```
output
```
name:   German Espinosa     string
age:    41  int
weight: 190.0   float
```
note: all members are populated with the right values using the same data type declared in the default constructor of the class

### Nested json structures:
```
from json_cpp JsonObject

class Person(JsonObject):
    def __init__(self, name="", age=0):
        self.name = name
        self.age = age

class Transaction(JsonObject)
    def __init__(self, buyer=None, seller=None, product="", ammount=0.0)
        self.buyer = buyer if buyer else Person()
        self.seller = seller if seller else Person()
        self.product = product
        self.ammount = ammount
            

mytransaction = Transaction(Person("German Espinosa", 41), Person("Benjamin Franklin", 84), "kite", 150.5) 

print (mytransaction)

```
