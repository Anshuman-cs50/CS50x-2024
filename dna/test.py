import csv

rows = []
with open("databases/small.csv") as file:
    reader = csv.DictReader(file)
    for row in reader:
        rows.append(row)
    print(reader.fieldnames)

print(rows)
print(rows[0]['name'])
