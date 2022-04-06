# ESG Viewer
This dashboard is built for analysis and visualisation of data relating to [ESG scores](https://money.usnews.com/investing/news/articles/what-is-an-esg-score) (Environmental, Social and Governance scores) of given companies. After selecting a company and a period of time to view, the user can view graphs reflecting Environmental, Social, Governance and overall ESG scores respectively, along with a rating for the company, calculated based on the ESG score.
## How it works
Data is stored in an SQLite database, which is populated on startup from a number of CSV files found in `./data`. Each of these files contains data on a certain topic:
* `companies.csv`: Companies viewed
* `providers.csv`: Providers (agencies which grant companies reviews on ESG scores)
* `kpis.csv`: Key Performance Indicators (factors rated by a given provider, belonging to any of the three main categories, such as corruption in the Governance category)
* `scores.csv`: Reviews made by a provider for a company in a given year

The same folder also contains two Python scripts, used to randomly generate sample data:
* `generatekpis.py`: For each company, generates a list of KPIs reviewed in `./data/kpis`
* `randomscores.py`: Randomly generates reviews by every provider for each company in every year able to be reviewed (2000-2020), based on provider's KPIs
## Notes
* This project was built in a team of 3, along with `@blwUsama` and `@r-moraru`, for the hackathon [HackITall](https://hack.lsacbucuresti.ro/). Highly educational and fun experience, would recommend!
