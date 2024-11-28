# set_covering_instances

Instances:
  OR-Library from https://people.brunel.ac.uk/~mastjjb/jeb/orlib/scpinfo.html
  CapraraFischettiToth from https://www-or.amp.i.kyoto-u.ac.jp/~yagiura/scp/
  MiningDatasetRepository from http://fimi.uantwerpen.be/data/

Format of the instances except from those in OR-Library/rail:
  number of rows (m), number of columns (n)
  the cost of each column c(j),j=1,...,n
  for each row i (i=1,...,m): the number of columns which cover
  row i followed by a list of the columns which cover row i

Format of the instances in OR-Library/rail:
  number of rows (m), number of columns (n)
  for each column j (j=1,...,n): the cost of the column, the
  number of rows that it covers followed by a list of the rows 
  that it covers 
