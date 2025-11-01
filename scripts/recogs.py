path = 'recs.sql'
with open(path, 'r') as file:
    for line in file:
        line = line.strip()
        if ("CREATE" in line) or ("PRAGMA" in line) or ("BEGIN" in line) or ("sqlite_sequ" in line) or ("COMMIT" in line):
            continue
        print("db.exec(\"{}\");".format(line))