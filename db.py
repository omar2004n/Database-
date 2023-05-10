import os

os.system("cls")
rela=[]
tmp=[]
decom=[]
def find_attr(relation,attr):
    attr=attr.split(',')
    for i in attr:
        if i not in relation:
            return 1
    return 0
def is_key(relation,attr):
    if func_dep[attr]==relation:
        return 1
    return 0
def calcul_closure(relation:list,func:dict):
  


    for i in range(len(relation)):
        for key in func.keys():
            for defin in func[key]:
                for j in func[defin]:
                    if j not in func[key] :
                        func[key]+=j
                        t=key.split(",")
                        if len(t)>1:
                            func[key].extend(list(set(t)-set(func[key])))
            func[key].sort()
    print('func',func)
    return func

# def elimin_old(attr,funcdep:dict):
#     for i in funcdep.keys():
#         if i not in funcdep[attr]:
#             funcdep.pop(i)
#             continue
#         for k in funcdep[i]:
#             if k not in funcdep[attr]:
#                 funcdep[i].remove(k)
#     return funcdep
def is_bcnf(relation:list,funcdep:dict):

    ext=0
    key =get_key(relation,funcdep)
    for i in relation:
        if i not in funcdep:
            print(f"{i} not in funcdep")
            continue
        if i not in key and len(funcdep[i])>1:
            print( ' not bcnf')
            tmp.append(i)
            ext=1
        if ext:
            return [0,tmp]
    
    return [1,[]]

        
    
    return [1,[]]
def decomposing(relation:list,funcdep:dict):
    
    rels=[]
    check =is_bcnf(relation,funcdep)
    if check[0]:
        return [relation]
    for i in check[1]:
        rels.append(funcdep[i])
        relation=list(set(relation)-set(funcdep[i]))
        relation.append(i)
    rels.append(relation)
    return rels


def get_key(relation: list, funcdep: dict):
   
   print('gk',func_dep)
   
   keydef = []
   func2 = funcdep
   keys = []
   
   
   while keydef != relation and len(func2.keys())>0:
       
       longk=list(func2.keys())[0]
       
       for k in func2.keys():
           
           if len(func2[k]) > len(func2[longk]):
               
               longk = k
       keys.append(longk)
       keydef.extend(func2[longk])
       func2.pop(longk)

       for i in func2.keys():
           for j in keydef:
            if j in func2[i]:
               func2[i].pop(func2[i].index(j))
   for i in keys:
       keys.pop(keys.index(i))
       keys.extend(i.split(","))
   print(keys,func_dep)
   return keys       
    
while 1:
    rela.append(input("Enter the attributes (Enter 0 if finished):"))
    if rela[-1]=='0':
        rela.pop(-1)
        break
print('\n\n',rela)

func_dep={}
for i in rela:
    func_dep[i]=[i]
print("Functional dependencies (a-->b)")
while 1:
    at=input("Enter the name of the attribute:")
    if at =='0':break
    defined=input("Enter the defined attr:")
    if find_attr(rela,at)  or find_attr(rela,defined):
        print("Undefined Attribute !!!")
        continue
    if at =='0':break
    if at not in func_dep:func_dep[at]=[]
    if defined not in func_dep[at]:
        try:
            func_dep[at]+=defined.split(',')
        except:
            func_dep[at]=defined.split(',')
  
func_dep=calcul_closure(rela,func_dep)

print('\n\nfunc_dep',func_dep)
#print('the key is : ',get_key(rela,func_dep))
print(decomposing(rela,func_dep))