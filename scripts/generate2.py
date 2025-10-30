import sqlite3
import json
import re

def acc(str):
    str = re.sub(r'[\"\[\]]', '', str)
    str = re.sub(r'\\u00e7', 'ç', str)
    str = re.sub(r'\\u00e9', 'é', str)
    str = re.sub(r'\\u00e8', 'è', str)
    str = re.sub(r'\\u00ea', 'ê', str)
    str = re.sub(r'\\u00ee', 'î', str)
    str = re.sub(r'\\u00ef', 'ï', str)
    str = re.sub(r'\\u00e2', 'â', str)
    str = re.sub(r'\\u00fb', 'û', str)
    str = re.sub(r' !', '', str)
    return str

con = sqlite3.connect("recognitions.db")
cur = con.cursor()

# CREATE TABLE recogs(
# id INTEGER PRIMARY KEY AUTOINCREMENT,
# form TEXT,
# head TEXT,
# parse TEXT
# );

cur.execute("create table if not exists recogs(id INTEGER PRIMARY KEY AUTOINCREMENT, form TEXT, head TEXT, parse TEXT);")
cur.execute("drop table recogs;")
cur.execute("create table recogs(id INTEGER PRIMARY KEY AUTOINCREMENT, form TEXT, head TEXT, parse TEXT);")

with open("conjugations.json", "r") as f:
    data = json.load(f)

for verb in data:
    if verb["infinitif"][2] == ' ': # check for reflexives
        continue
    if verb["infinitif"][1] == '\'': # elided reflexives
        continue
    #print(verb["infinitif"])
    inf = verb["infinitif"]
    inf = acc(inf)
    try:
        pres = json.dumps(verb["present"])
        pres = acc(pres)
    except KeyError:
        continue
    presents = pres.split(', ')
    
    try:
        impf = json.dumps(verb["imparfait"])
        impf = acc(impf)
    except KeyError:
        continue
    imperfects = impf.split(', ')
    
    try:
        passeSimple = json.dumps(verb["passeSimple"])
        passeSimple = acc(passeSimple)
    except KeyError:
        continue
    pasts = passeSimple.split(', ')
    
    try:
        future = json.dumps(verb["futurSimple"])
        future = acc(future)
    except KeyError:
        continue
    futures = future.split(', ')

    try:
        conditional = json.dumps(verb["conditionnelPresent"])
        conditional = acc(conditional)
    except KeyError:
        continue
    conditionals = conditional.split(', ')

    try:
        subjunctivePres = json.dumps(verb["subjonctifPresent"])
        subjunctivePres = acc(subjunctivePres)
    except KeyError:
        continue
    subjunctivePresents = subjunctivePres.split(', ')
    
    try:
        subjunctiveImpf = json.dumps(verb["subjonctifImparfait"])
        subjunctiveImpf = acc(subjunctiveImpf)
    except KeyError:
        continue
    subjunctiveImperfects = subjunctiveImpf.split(', ')

    try:
        pastParticiple = json.dumps(verb["participePasse"])
        pastParticiple = acc(pastParticiple)
    except KeyError:
        continue

    try:
        presParticiple = json.dumps(verb["participePresent"])
        presParticiple = acc(presParticiple)
    except KeyError:
        continue

    try:
        auxiliary = json.dumps(verb["auxiliaire"])
        auxiliary = acc(auxiliary)
    except KeyError:
        continue

    try:
        imperat = json.dumps(verb["imperatif"])
        imperat = acc(imperat)
    except KeyError:
        continue
    
    #for key, value in {"present": presents, "imperfect": imperfects, "passeSimple": passeSimples, "future": futures, "conditional": conditionals, "subjunctivePresent": subjunctivePresents, "subjunctiveImperfect": subjunctiveImperfects}.items():
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (presents[0], inf, "1st sg pres"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (presents[1], inf, "2nd sg pres"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (presents[2], inf, "3rd sg pres"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (presents[3], inf, "1st pl pres"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (presents[4], inf, "2nd pl pres"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (presents[5], inf, "3rd pl pres"))

    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (imperfects[0], inf, "1st sg impf"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (imperfects[1], inf, "2nd sg impf"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (imperfects[2], inf, "3rd sg impf"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (imperfects[3], inf, "1st pl impf"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (imperfects[4], inf, "2nd pl impf"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (imperfects[5], inf, "3rd pl impf"))

    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (pasts[0], inf, "1st sg past"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (pasts[1], inf, "2nd sg past"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (pasts[2], inf, "3rd sg past"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (pasts[3], inf, "1st pl past"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (pasts[4], inf, "2nd pl past"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (pasts[5], inf, "3rd pl past"))

    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (futures[0], inf, "1st sg fut"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (futures[1], inf, "2nd sg fut"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (futures[2], inf, "3rd sg fut"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (futures[3], inf, "1st pl fut"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (futures[4], inf, "2nd pl fut"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (futures[5], inf, "3rd pl fut"))

    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (conditionals[0], inf, "1st sg cond"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (conditionals[1], inf, "2nd sg cond"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (conditionals[2], inf, "3rd sg cond"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (conditionals[3], inf, "1st pl cond"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (conditionals[4], inf, "2nd pl cond"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (conditionals[5], inf, "3rd pl cond"))

    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (subjunctivePresents[0], inf, "1st sg subj pres"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (subjunctivePresents[1], inf, "2nd sg subj pres"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (subjunctivePresents[2], inf, "3rd sg subj pres"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (subjunctivePresents[3], inf, "1st pl subj pres"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (subjunctivePresents[4], inf, "2nd pl subj pres"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (subjunctivePresents[5], inf, "3rd pl subj pres"))

    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (subjunctiveImperfects[0], inf, "1st sg subj impf"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (subjunctiveImperfects[1], inf, "2nd sg subj impf"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (subjunctiveImperfects[2], inf, "3rd sg subj impf"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (subjunctiveImperfects[3], inf, "1st pl subj impf"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (subjunctiveImperfects[4], inf, "2nd pl subj impf"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (subjunctiveImperfects[5], inf, "3rd pl subj impf"))

    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (presParticiple, inf, "pres part"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (pastParticiple, inf, "past part"))
    cur.execute("insert into recogs (form, head, parse) values (?, ?, ?);", (inf, inf, "inf"))

con.commit()
con.close()