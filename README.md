# C(had) Web Server

## What I learned building the C(had) Web Server

1. The importance of passing by reference vs by value.
-TODO:
Trying to set HttpRequest fields.
2. The importance of how pointers work
literally just points to a memory address but i swear to god that concept is so important
3. How frameworks do all the url routing for you
literally step by step parsing all the good stuff out of the http request and building the http response which
in all honestly i probably did wrong.
4. Just how much I had to remember to use the string.h library when working with string pointers because it's basically an array that is being pointed at.
5. If you have a pointer say a 'char *' for example, in a situation where you need to malloc in a called function, you can free the pointer in the callee function if the function accepts a pointer
to a pointer or a 'char **', you then pass the address of the original pointer you want to have effect taken on. and in the function you'll have to derefence the pointer to the pointer
this is because you literally pass the address of the pointer.
## Why ?
Why not get down and gritty with C to make a web server instead of just typing flask and not even knowing what happens underneath the hood, albeit theres probably more
going on underneath the hood then what i've manage to code up here.


### Extra what to do(s)
1. tidy up the readme
