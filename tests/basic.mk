SIMPLE = coucou
SPACES   =    a    b   
EMPTY =
EQ = a=b
COLON = a:b

all: foo bar
	echo all
	echo second

foo: foo.c
	gcc -o foo foo.c

	echo x=y

bar:
	    echo spaces before
	echo spaces after    

no_cmd: dep1   dep2
