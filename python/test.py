from json_cpp import JsonObject, JsonList

class Person(JsonObject):
    def __init__(self):
        self.name = ""
        self.surname = ""
        self.languages = JsonList(list_type=str)

person = Person.parse("{\"name\":\"German\",\"surname\":\"Espinosa\", \"languages\":[\"english\",\"spanish\",\"portuguese\"]}")

print(person)
