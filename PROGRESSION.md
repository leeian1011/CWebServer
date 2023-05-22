# Progress log

> this is just a log to track my progress and problems i face from inception of project

## Problems

1. Could not for the life of me, assign the `HttpRequest` fields (requestUrl & httpMethod) to the return value of `strtok(methodlinebuffer, " ")`

- originally had a `char *tmp` that i `malloc()` and assigned the return value to `strtok(methodlinebuffer, " ")`, then, i'd have the `HttpRequest` fields assigned to tmp. <br>
the issue here was that the `HttpRequest` fields was pointing to the memory address of tmp and seeing as I had to `free()` tmp, the HttpRequest fields would end up pointing to
an unused memory location.

- that was not the only issue as when I initialized the `HttpRequest` struct, I did not initialize it as a Pointer but as a simple struct.<br>
this meant that I could not pass `HttpRequest` by reference into a called function. To remedy this, I had a few options. <br>

   1. Set all functions that required altering `HttpRequest` to accept `HttpRequest *` as a parameter. Then in the callee function, I would pass `&HttpRequest` or the memory address of it into 
      The function.
   2. Set functions to accept `HttpRequest *` and also initialized `HttpRequest` struct as a pointer.

as viewable in the repo, the remedy I chose ended up being number 2. Only after deciding to initialize `HttpRequest` as `HttpRequest *` and continued on writing more code that I realized that
there was another solution. THe justification for using method 2, is that I just got lazy to refactor and change, perhaps one of my todo(s)?
 
- hindsight is 20/20, I realized that having to allocate memory to `HttpRequest` is probably bad practice seeing as the size is known during compile time, will fix to initialize as a struct and 
pass in address of, into any functions that require to alter `HttpRequest`.

2. Minor issue with server crashing due to heap corruption error.

- used the giga virgin method of debugging by printf-ing the memory addresses of every pointer malloc'd.<br>
found out that there was a problem with the `PATH_BYTE_SIZE` global variable. It represents the number of bytes that my "path/to/file.file" would have, in this case I believe that the minimum 
path byte size is 15 Bytes, "page/index.html". I set it to be able to receive atleast double that length so it was assigned to 30. The corruption was always 20 memory places or 20 bytes away from the first byte that `path` points to, I could not for the life of me figure out why this was an issue despite being able to read up to double the byte size. I ended up increasing it to 45, or triplethe minimum byte size, the corruption issue went away. 

- A possible explanation could be that I had an off by one error as I did not take into account the terminating character byte, thus making it a minimum of 16 bytes.

## Updates

1. Made a branch that could handle icons and image requesting! Also wanted to delve into a bit of handling http request properly.

Heres some things I learned.

- Reading binary to send over images through sockets.
- the strings library functions work by defining that a string is a sequence that ends with a NUL terminating special character, this means that trying to read information like using `strlen()` on 
a character pointer that holds binary data tends to lead to whacky undefinied behaviour
- this also means that working with `strcpy()` or `strcat()` becomes kinda tough, through this I learned about `memcpy()` and copying memory directly onto memory addresses and how 
pointer arithmetic is helpful.
- trying to get the icon to load on browsers was pretty funky, had a minor issue with browser hard caching the icon image, learnt and understand more about caching and that due to caching,
a browser only sends requests for images when a new image that the browser has never seen before is needed.
- had an issue with memory heap corruption leading to undefinied behaviour where the server would be able to refresh twice or up to 20 times only. ended up finding out that compiling regex
needs to be freed with `regfree()`, however that was not the main issue, printed out the memory addresses of all pointers allocated and found out that the memory corruption occurs almost always
about 16 bytes away from HttpRequest, thought it could be an issue with the way I was hanling HttpRequest, decided to change it up to only pass the address of HttpRequest into functions that
need to alter it, didnt solve the issue but it did move the corrupted memory to a specific location very nearby the HttpResponse pointer. It ended up being a silly mistake where I forgot to
dereference the fileLength variable in the `generate_http_response()` function, that was a frustrating but oddly fun issue to have to handle.
-learned about unsigned char use cases, difference betweeen uint8_t and the rest and how unsigned char is much better suited for storing byte data.
