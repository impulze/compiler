parser grammar boofar_parser;

options
{
	language = C;
}

parse : Number + EOF
	;
