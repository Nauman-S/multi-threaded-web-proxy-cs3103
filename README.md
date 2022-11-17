# Multi-threaded-web-proxy-cs3103
A basic web proxy capable of accepting HTTP 1.0/1.1 requests and returning responses to a client

## `Usage`
1). Use make to build

2). Run the binary using command `./proxy <port> <substitution> <attack>`

3). Use make clean to remove binary

4). requires g++ GNU C++ compiler

## `Specifications` 
1). Install the following version of [firefox](https://www.mozilla.org/en-US/firefox/92.0/releasenotes/)


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
