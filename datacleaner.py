################################################################################################
#This part initializes new spreadsheet with specified columns
################################################################################################
'''
still need to make a part that deletes the first column and moves all the data up
such that the index will be, by default the second fow names
'''

import pandas as pd

df = pd.read_excel('ForEd/AuburnRawuse.xlsx')
newdf = df[['DOI', 'Title', 'Acknowledgements', 'PubYear', 'Publication Type', 'Authors (Raw Affiliation)', 'Corresponding Author','Research Organizations - standardized', 'Country of Research organization', 'Funder', 'Funder Group', 'Funder Country', 'Supporting Grants']]
newdf.replace({'NaN': None})

################################################################################################
#This part initializes new spreadsheet with specified columns
################################################################################################
'''
still need to make a part that deletes the first column and moves all the data up
such that the index will be, by default the second fow names
'''

import pandas as pd

df = pd.read_excel('ForEd/AuburnRawuse.xlsx')
newdf = df[['DOI', 'Title', 'Acknowledgements', 'PubYear', 'Publication Type', 'Authors (Raw Affiliation)', 'Corresponding Author','Research Organizations - standardized', 'Country of Research organization', 'Funder', 'Funder Group', 'Funder Country', 'Supporting Grants', 'Dimensions URL']]

for ind in df.index:
    DOI = df['DOI'][ind]
    newname = DOI.replace('; ','\n')
    newdf['DOI'][ind] = newname
for i in df.index:
    AuthorsRA = df['Authors (Raw Affiliation)'][i]
    newname = AuthorsRA.replace('; ','\n')
    newdf['Authors (Raw Affiliation)'][i] = newname
# for j in df.index:
#     CorrAuth = df['Corresponding Author'][j]
#     newname = CorrAuth.replace('; ','\n')
#     newdf['Corresponding Author'][j] = newname
# for k in df.index:
#     ROstd = df['Research Organizations - standardized'][k]
#     newname = ROstd.replace('; ','\n')
#     newdf['Research Organizations - standardized'][k] = newname
# for l in df.index:
#     CRO = df['Country of Research organization'][l]
#     newname = CRO.replace('; ','\n')
#     newdf['Country of Research organization'][l] = newname
# for m in df.index:
#     Funder = df['Funder'][m]
#     newname = Funder.replace('; ','\n')
#     newdf['Funder'][m] = newname
# for n in df.index:
#     Funder = df['Funder Group'][n]
#     newname = Funder.replace('; ','\n')
#     newdf['Funder Group'][n] = newname



# for ind in newdf.index:
#     Title = newdf['Title'][ind]
#     newdf = Title.replace(';','\n')
# for ind in newdf.index:
#     PubType = newdf['Publication Type'][ind]
#     newdf = Pubtype.replace(';','\n')
# for ind in newdf.index:
#     RAauthor = newdf['Authors (Raw Affiliation)'][ind]
#     newdf = RAauthor.replace(';','\n')



newdf.to_excel("refined.xlsx", sheet_name='sheetA', index=False)

    
# 'Supporting Grants'
# 'Authors (Raw Affiliation)'
# 'Corresponding Author'
# 'Research Organizations - standardized'
# 'Country of Research organization'
# 'Funder'
# 'Funder Group'
# 'Funder Country'