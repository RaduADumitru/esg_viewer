import csv

with open('companies.csv') as csv_companies:
    with open('providers.csv') as csv_agencies:
        companies_dict = csv.DictReader(csv_companies)
        agencies.dict = csv.DictReader(csv_agencies)
        nr_companies = csv_companies.len()
        nr_agencies = csv_agencies.len()
        nr_scores = nr_companies * nr_agencies
        