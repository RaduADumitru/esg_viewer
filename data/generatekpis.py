import csv
import random

with open('kpis.csv') as csv_kpis:
    kpi_reader = csv.reader(csv_kpis, delimiter=',')
    kpi_list = list(kpi_reader)
    with open('providers.csv') as csv_agencies:
        agencies_reader = csv.reader(csv_agencies, delimiter=',')
        agencies_list = list(agencies_reader)
        list_size = len(kpi_list)
        agencies_list.pop(0) # Remove header
        kpi_list.pop(0)
        for agency in agencies_list:
            filename = "kpis\\" + agency[0] + "_kpi.csv"
            with open(filename, mode= 'w') as kpi_file:
                file_writer = csv.writer(kpi_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
                file_writer.writerow(['KPI', 'Category'])
                random.shuffle(kpi_list)
                nr_kpis = random.randint(int(list_size / 2), list_size)
                for kpi in range(nr_kpis-1):
                    file_writer.writerow(kpi_list[kpi])





