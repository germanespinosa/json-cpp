from src import *
from datetime import datetime


JsonDate.date_format = "%H:%M:%S"

class c(JsonObject):
    def __init__(self):
        self.e = datetime.now()

o = c()

print (o)

a = str(o)


p = c.parse(a)

print (o,p)
#
# a = datetime.now()
#
# s = str(a)
#
# print(s)
#
#
# print(datetime.strptime(s, '%Y-%m-%d %H:%M:%S.%f'))
#
