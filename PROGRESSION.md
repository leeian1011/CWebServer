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

- hindsight is 20/20, I realized that having to allocate memory to `HttpRequest is probably bad practice seeing as the size is known during compile time, will fix to initialize as a struct and 
pass in address of, into any functions that require to alter `HttpRequest`.

2. Minor issue with server crashing due to heap corruption error.

- used the giga virgin method of debugging by printf-ing the memory addresses of every pointer malloc'd.<br>
found out that there was a problem with the `PATH_BYTE_SIZE` global variable. It represents the number of bytes that my "path/to/file.file" would have, in this case I believe that the minimum 
path byte size is 15 Bytes, "page/index.html". I set it to be able to receive atleast double that length so it was assigned to 30. The corruption was always 20 memory places or 20 bytes away from the first byte that `path` points to, I could not for the life of me figure out why this was an issue despite being able to read up to double the byte size. I ended up increasing it to 45, or triplethe minimum byte size, the corruption issue went away. 
