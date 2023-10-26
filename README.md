########################## PARSING ###########################
<--------- Accepting the user input -------->
in an infinite loop:
	1. read the line from STDIN using readline library,
	2. if its exit,  we clean what ever is allocated and exit.
	3. then lets initialize our data struct.
		-> if not successfull, we clean what ever is allocated and we terminate our program smoothly.
	4. then, we start the parsing part of this project
		-> once again, if not successfull we clean allocated memory, throw meaningful error message and exit smoothly,
	5. if everything goes well, we add the command we read to history so we can use the up/down buttons to re-run them.

<---------  initializing the data -------->
our general data struct will have;
	1, the input we read from the prompt,
	2. the command that we will construct (that goes to excution) in a double linked list format, and contains:
		a. a command that will have to find in our path or that is built-in
		b. the above command with its options,
		c. tokenized double linked list of our input, where each element is recognized for what they are.
		d. the enivironment variable, where we will get the PATH and excutable commands from.
for now we already have input, and we will initialize 2.b & 2.c as NULL, and we duplicate the ENV variable.
		-> once again, if not successfull we clean allocated memory, throw meaningful error message and exit smoothly

<---------  stating the program -------->
after we successfully initialize our general data, we will:
	1, start with basic error handling such as:
		>> opened but unclosed quotes
		>> pipe at the end
		>> redirections at the end
	2, we start lexical analysis - where we tokenize each element of the input
		* once again, if not successfull we clean allocated memory, throw meaningful error message and exit smoothly,
	3. after we have a double linked list of tokenized elements, we check for some more error checking for these conditions:
		* > | respectively is an error.
		* < | respectively is an error.
		* << | respectively is an error.
		* >> | respectively is an error.
		* double Operator back to back i.e '||', '> >', '<< >' kind of things
	4. if the input we have received has passed the above testes, we start expansion i.e:
		-> expanding any environment variable we might have in '$xxx' format -> details will be in that specific function.
	5. after that we will construct a 'complete' command that will be passed to the second part fo this project, i.e Excution.

<---------  Lexical Analysis -------->


<---------  Expansion of VAR -------->

str len - var_len + envp_len(after equal) + 1 (for null termi) -> malloc this one (free the old one first)
our final token->str == characters before $ + envp_len(after equal) + characters after var_name + '\0'

<---------  Parsing and Constructing a Command -------->


########################## Execution ###########################
...