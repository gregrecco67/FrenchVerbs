import json
import re

with open("conjugations.json", "r") as f:
    data = json.load(f)

for verb in data:
    if verb["infinitif"][2] == ' ': # check for reflexives
        continue
    if verb["infinitif"][1] == '\'': # elided reflexives
        continue
    #print(verb["infinitif"])
    inf = verb["infinitif"]
    try:
        pres = json.dumps(verb["present"])
    except KeyError:
        continue
    
    try:
        impf = json.dumps(verb["imparfait"])
    except KeyError:
        continue
    
    try:
        pc = json.dumps(verb["passeCompose"])
    except KeyError:
        continue

    try:
        pastp = verb["participePresent"]
    except KeyError:
        continue

    try:
        presp = verb["participePasse"]
    except KeyError:
        continue
    
    try:
        passeSimple = json.dumps(verb["passeSimple"])
    except KeyError:
        continue
    
    try:
        future = json.dumps(verb["futurSimple"])
    except KeyError:
        continue

    try:
        conditional = json.dumps(verb["conditionnelPresent"])
    except KeyError:
        continue

    try:
        subjunctivePres = json.dumps(verb["subjonctifPresent"])
    except KeyError:
        continue
    
    try:
        subjunctiveImpf = json.dumps(verb["subjonctifImparfait"])
    except KeyError:
        continue

    try:
        pastParticiple = json.dumps(verb["participePasse"])
    except KeyError:
        continue

    try:
        presParticiple = json.dumps(verb["participePresent"])
    except KeyError:
        continue

    forms = [inf, pres, impf, pc, pastParticiple, presParticiple, passeSimple, future, conditional, subjunctivePres, subjunctiveImpf]
    for i, item in enumerate(forms):
        forms[i] = re.sub(r'[\"\[\]]', '', forms[i])
        forms[i] = re.sub(r'\\u00e7', 'ç', forms[i])
        forms[i] = re.sub(r'\\u00e9', 'é', forms[i])
        forms[i] = re.sub(r'\\u00e8', 'è', forms[i])
        forms[i] = re.sub(r'\\u00ea', 'ê', forms[i])
        
        forms[i] = re.sub(r'\\u00ee', 'î', forms[i])
        forms[i] = re.sub(r'\\u00ef', 'ï', forms[i])
        forms[i] = re.sub(r'\\u00e2', 'â', forms[i])
        forms[i] = re.sub(r'\\u00fb', 'û', forms[i])
    
    print("st.bind(1, \"{0}\");".format(forms[0]))
    print("st.bind(2, \"{0}\");".format(forms[1]))
    print("st.bind(3, \"{0}\");".format(forms[2]))
    print("st.bind(4, \"{0}\");".format(forms[3]))
    print("st.bind(5, \"{0}\");".format(forms[4]))
    print("st.bind(6, \"{0}\");".format(forms[5]))
    print("st.bind(7, \"{0}\");".format(forms[6]))
    print("st.bind(8, \"{0}\");".format(forms[7]))
    print("st.bind(9, \"{0}\");".format(forms[8]))
    print("st.bind(10, \"{0}\");".format(forms[9]))
    print("st.bind(11, \"{0}\");\nst.exec();\nst.reset();\nst.clearBindings();\n".format(forms[10]))


# CREATE TABLE frenchVerbs(
# verbID INTEGER PRIMARY KEY AUTOINCREMENT,
# infinitive TEXT,
# pastParticiple TEXT,
# presParticiple TEXT,
# auxiliary TEXT,
# present TEXT,
# imperfect TEXT,
# passeCompose TEXT,
# passeSimple TEXT,
# future TEXT,
# conditional TEXT,
# subjunctivePres TEXT
# );

