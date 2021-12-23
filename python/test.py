from src import json_object


class Point3(json_object.JsonObject):

    def __init__(self, x=0.0, y=0.0, z=0.0):
        self.x = x
        self.y = y
        self.z = z


class Point3List(json_object.JsonList):

    def __init__(self):
        json_object.JsonList.__init__(self, list_type=Point3)


p = Point3(1, 2, 3)

json_str = str(p)

p2 = Point3.parse(json_str)

point_list = Point3List()
point_list.append(Point3(1, 2, 3))
point_list.append(Point3(2, 3, 4))
point_list.append(Point3(3, 4, 5))
print(p2.x, p2.y, p2.z)
print(point_list)


point_list2 = Point3List.parse("[{\"x\":10,\"y\":10,\"z\":10},{\"x\":15,\"y\":15,\"z\":15},{\"x\":18,\"y\":18,\"z\":18}]")

print(point_list2)

