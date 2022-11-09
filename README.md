# Multi-threaded-web-proxy-cs3103
A basic web proxy capable of accepting HTTP 1.0/1.1 requests and returning responses to a client
## `Usage` 
1). Install the following version of [firefox](https://www.mozilla.org/en-US/firefox/92.0/releasenotes/)

2). Build project using clang compiler using command `make` to produce output binary proxy

3). Run the binary using command `./proxy <port> <substitution> <attack>`

#### `port` 
The port on which the proxy runs

#### `substitution` 
a binary value to specify if the proxy applies image
substitution (0 for no substitution, 1 for substitution)

#### `attack` 
a binary value to specify if the proxy is implementing an
attacker mode (0 for no attack, 1 for attack)

## `Example` 
./proxy 9989 1 0
