A simple client to read from and write to a "Dumb File Transfer Protocol" server for class ECS 152A.

### DFTP.rb
- A simple ruby script to test out the protocol.

Usage:

`./DFTP.rb <server address> <server port>`


### DFTP.c
- The same as DFTP.rb except written in C...

Usage:

```
gcc DFTP.c
./DFTP <server address> <server port>
```

### DFTP Protocol
GET <file to get>
PUT <The names of your team members>
COMMENT <your comments from stdin.>