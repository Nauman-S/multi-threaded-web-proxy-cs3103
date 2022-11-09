Multi-threaded-web-proxy-cs3103
A basic web proxy capable of accepting HTTP requests and returning responses to a client
# PKB Design
## `WritePKBManager` class
A facade class to expose APIs to SP on writing information into the PKB 
### Methods:
- `static std::unique_ptr<WritePKBManager> GetInstance()`: returns a reference of the WritePKBManager object
#### Variable entity APIs
- `void AddVariable(Variable var)`: adds and stores a variable entity
#### Constant entity APIs
- `void AddConstant(Constant constant)`: adds and stores a constant entity
#### Procedure entity APIs
- `void AddProcedure(Procedure proc)`: adds and stores a procedure entity
