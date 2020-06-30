

def variableFunction(arg1,*variableTuple):
    print("first arg");
    print(arg1);
    for i in variableTuple:
        print(i);
    return;

globalMoney = 1000

def AddMoney():
    global globalMoney;
    globalMoney = globalMoney + 1;
    print(globalMoney)

   