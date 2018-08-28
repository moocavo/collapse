# Collapse
### by Jae Chan Hwang:	hwangjc@umich.edu
### 12/01/2017

## Syntax:
	
	collapse [Options]... -i [input file] -o [output file]

## Options:

	-s,	--substr			If this flag is specified, adjacent rows will be collapsed
							if one row is a substring of the other.
							example:
								Apple
								appl
								Applee
							// These will all collapse to Applee

	-c [column], --column [column]

							Collapse by column [column] in range of [1,number of columns]
							If the -c flag is not specified, will default to 1
