import json

with open("dbs/conjugations.json", "r") as f:
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
        subjunctive = json.dumps(verb["subjonctifPresent"])
    except KeyError:
        continue
    
    print("st.bind(1, \"{0}\");".format(inf))
    print("st.bind(2, \"{0}\");".format(pres))
    print("st.bind(3, \"{0}\");".format(impf))
    print("st.bind(4, \"{0}\");".format(pc))
    print("st.bind(5, \"{0}\");".format(pastp))
    print("st.bind(6, \"{0}\");".format(presp))
    print("st.bind(7, \"{0}\");".format(passeSimple))
    print("st.bind(8, \"{0}\");".format(future))
    print("st.bind(9, \"{0}\");".format(conditional))
    print("st.bind(10, \"{0}\");st.exec();\nst.reset();\nst.clearBindings();\n".format(subjunctive))
    
    #cur.execute("""INSERT INTO frenchVerbs (infinitive, present, imperfect, passeCompose, pastParticiple, presParticiple, passeSimple, future, conditional, subjunctivePres) 
    #            VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)""", (inf, pres, impf, pc, pastp, presp, passeSimple, future, conditional, subjunctive))
# con.commit()


# con.close()

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