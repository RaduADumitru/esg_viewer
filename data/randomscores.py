import csv
import random

with open('companies.csv') as csv_companies:
    with open('providers.csv') as csv_agencies:
        companies_dict = csv.reader(csv_companies)
        agencies_dict = csv.reader(csv_agencies)
        with open('scores.csv', mode='w') as csv_scores:
            scores_writer = csv.writer(csv_scores, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
            scores_writer.writerow(['year', 'company', 'provider', 'e_score', 's_score', 'g_score'])
            ok_company = False
            ok_agency = False
            companies_list = list(companies_dict)
            agencies_list = list(agencies_dict)
            # for companies_row in companies_dict:
            #     print(companies_row)
            # for companies_row in companies_dict:
            #     for agencies_row in agencies_dict:
            #         print(companies_row[0], agencies_row[0])
            for companies_row in companies_list:
                if ok_company:
                    company_base = random.randint(20, 80)
                    for agencies_row in agencies_list:
                        if ok_agency:
                            agency_base = company_base + random.randint(-10, 10)
                            company_name = companies_row[0]
                            agency_name = agencies_row[0]
                            for year in range(2000, 2021):
                                e_score = agency_base + random.randint(-10, 10)
                                s_score = agency_base + random.randint(-10, 10)
                                g_score = agency_base + random.randint(-10, 10)
                                data = [year, company_name, agency_name, e_score / 100, s_score / 100, g_score / 100]
                                scores_writer.writerow([str(x) for x in data])
                        ok_agency = True
                ok_company = True
