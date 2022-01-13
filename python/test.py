from src import *
from datetime import datetime

print(JsonObject(a=1, b=1.2, c=True, d=JsonObject(e=1), e=datetime.now()))
