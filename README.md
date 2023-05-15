# C(had) Web Server

## Why make a web server in C?
I wanted to know just what exactly happens or how on earth does a "server" even work or how would it even "understand" http requests<br>
and how http requests/responses work. It started with <a href="https://github.com/leeian1011/LearningSockets" target="_blank">this heavily abstracted java server-client program</a>
that made taught me simple socket programming and how its like a literal two pin plug.

## What I learned while making this abomination

1. I literally had to relearn what passing by value and passing by reference meant which is why pointers exist<br>
2. Pointers are literally so much fun especially when it comes to figuring out how to free memory in a callee function from a pointer that was allocated memory in a called function<br>
3. RTFM has never worked so well until now, there was a point where I got the server to essentially serve it's purpose but it kept on reading from the socket even after the socket was
closed. Through reading through <a href="https://docs.oracle.com/cd/E19120-01/open.solaris/817-4415/6mjum5soe/index.html" target="_blank">this doc</a> that I learnt that `shutdown()` was a much
better way of handling closing a socket than `close()` when using a TCP connection that ensures that data is sent.
4. I oddly get motivated while building stuff that many people have deemed not needed to understand to learn programming.

[1. The importance of passing by reference vs by value.
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
this is because you literally pass the address of the pointer.]: #

## Why ?

While learning Harvard's CS50 there was a time when the week's topic was on HTML, CSS and Javascript where we could just use a http-server command that lets us get a simple static web server up and running in literally no time but I was much more intrigued with how on earth does "http-server" work than I was building the week's project.

### Extra what to do(s)

1. tidy up the readme
2. add some drawings
3. video ???
